#include "../Parser/Parser.h"

#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>


extern std::mutex m;
extern std::mutex pmutex;
extern std::condition_variable condition;
extern bool notified;

//парсер не должен быть владельцем базового ресурса,
//владельцем является general
Parser::Parser(std::shared_ptr <Queue<std::string>> rque,
               std::shared_ptr <Queue<TestCase *>> wque,
               std::shared_ptr <Queue<std::string>> reque) :
        rque(rque), wque(wque), reque(reque), workStatus(false) {
    maxPool = std::thread::hardware_concurrency();
    for (int i = 0; i < maxPool; i++) {
        threadPool.push_back(std::thread(std::bind(&Parser::workCycle, this)));
    }
};

Parser::~Parser() {
    std::for_each(threadPool.begin(), threadPool.end(), mem_fn(&std::thread::join));
};

void Parser::setStatus(bool newStatus) {
    workStatus = newStatus;
};

void Parser::workCycle() {
    std::unique_lock <std::mutex> lock(m);
    //bool состояния
    while (workStatus) {
        //избавляемся от внезапных пробуждений
        while (!notified) {
            condition.wait(lock);
        }

        if (!rque->empty()) {
            std::string request = get_request();
            workThread(request);
        }
        notified = false;
    }
};

void Parser::workThread(const std::string &request) {

    pt::ptree tree;
    std::stringstream ss;
    ss << request;
    pt::read_json(ss, tree);

    stringFormatter obj{codes.defaultId, codes.defaultAnswer};
    bool parseStatus = false;

    validateRequest(tree, parseStatus, obj);

    if (parseStatus) {
        int request_type = tree.get<int>("request.request_type");
        switch (request_type) {
            case codes.cppRequestType: {
                CTestGeneration *ctg = new CTestGeneration(request, wque);
                ctg->convertToTestCase();
                ctg->sendToWorker();
                break;
            }
            case codes.webRequestType: {
                WebTestGeneration *wtg = new WebTestGeneration(request, wque);
                wtg->convertToTestCase();
                wtg->sendToWorker();
                break;
            }
        }
    } else {
        std::string response = to_json(obj);
        reque->push(response);
    }
}

std::string Parser::get_request() const {
    return rque->pop();
};

void Parser::validateRequest(const pt::ptree &tree, bool &parseStatus, stringFormatter &obj) const {
    //получаем тип заявки
    int request_type = tree.get("request.request_type", codes.invalidRequestType);

    std::string id = tree.get("request.id", codes.defaultId);

    if (request_type == codes.invalidRequestType) {
        obj.description = codes.invalidRequestStructure;
        return;
    }

    if (id == codes.defaultId) {
        obj.description = codes.defaultId;
        return;
    }

    switch (request_type) {

        case codes.webRequestType: {
            std::string host = tree.get("request.host", codes.defaultHost);
            if (!validateHost(host)) {
                obj.description = codes.defaultHost;
                return;
            }

            std::string p = tree.get("request.protocol", codes.defaultProtocol);
            if (!validateProtocol(p)) {
                obj.description = codes.defaultProtocol;
                return;
            }

            std::string m = tree.get("request.method", codes.defaultMethod);
            if (!validateMethod(m)) {
                obj.description = codes.defaultMethod;
                return;
            }

            std::string ref = tree.get("request.reference", codes.defaultReference);
            if (!validateReference(ref)) {
                obj.description = codes.defaultReference;
                return;
            }
            parseStatus = true;
            return;
        }

        case codes.cppRequestType: {
            std::string git = tree.get("request.git_adress", codes.defaultGit);
            if (!validateAdress(git)) {
                obj.description = codes.defaultGit;
                return;
            }

            std::string target = tree.get("request.target", codes.defaultTarget);
            if (!validateTarget(target)) {
                obj.description = codes.defaultTarget;
                return;
            }
            parseStatus = true;
            return;
        }

        default: {
            if (reque) {

                obj.description = codes.temporary;
                return;
            }
            return;
        }
    }

};

//WEB CASE
bool Parser::validateHost(const std::string &s) const {
    static const boost::regex e("^(www\\.)?[a-z0-9]+([\\-\\.]{1}[a-z0-9]+)*\\.[a-z]{2,5}(:[0-9]{1,5})?(\\/.*)?$");
    return regex_match(s, e);
};

bool Parser::validateProtocol(const std::string &s) const {
    static const boost::regex e("[0|1]");
    return regex_match(s, e);
};

bool Parser::validateMethod(const std::string &s) const {
    static const boost::regex e("[0|1|2|3|4]");
    return regex_match(s, e);
};

bool Parser::validateReference(const std::string &s) const {
    static const boost::regex e("(10[0-3]|20[0-6]|30[0-8]|4(0[0-9)|1[0-7])|50[0-5])");
    return regex_match(s, e);
};


//CPP CASE
bool Parser::validateAddress(const std::string &s) const {
    static const boost::regex e("github\\.com\\/([a-zA-Z0-9\\_\\-]*)/([a-zA-Z0-9\\_\\-]*)");
    return regex_match(s, e);
};

bool Parser::validateTarget(const std::string &s) const {
    static const boost::regex e("([\\_]*[a-zA-Z]+[a-zA-Z0-9\\_]*)");
    return regex_match(s, e);
};
