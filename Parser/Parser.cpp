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

    if (validateRequest(tree)) {
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
    }
}

std::string Parser::get_request() const {
    return rque->pop();
};

bool Parser::validateRequest(const pt::ptree &tree) const {
    //получаем тип заявки
    int request_type = tree.get("request.request_type", codes.invalidRequestType);

    std::string id = tree.get("request.id", codes.defaultId);

    if (request_type == codes.invalidRequestType) {

        stringFormatter obj{id, codes.invalidRequestStructure};
        std::string response = to_json(obj);
        reque->push(response);
        return false;
    }

    if (id == codes.defaultId) {
        stringFormatter obj{id, codes.defaultId};
        std::string response = to_json(obj);
        reque->push(response);
        return false;
    }

    switch (request_type) {

        case codes.webRequestType: {
            std::string host = tree.get("request.host", codes.defaultHost);
            if (!validateHost(host)) {
                stringFormatter obj{id, codes.defaultHost};
                std::string response = to_json(obj);
                reque->push(response);

                return false;
            }

            std::string p = tree.get("request.protocol", codes.defaultProtocol);
            if (!validateProtocol(p)) {
                stringFormatter obj{id, codes.defaultProtocol};
                std::string response = to_json(obj);
                reque->push(response);
                return false;
            }

            std::string m = tree.get("request.method", codes.defaultMethod);
            if (!validateMethod(m)) {
                stringFormatter obj{id, codes.defaultMethod};
                std::string response = to_json(obj);
                reque->push(response);
                return false;
            }

            std::string ref = tree.get("request.reference", codes.defaultReference);
            if (!validateReference(ref)) {
                stringFormatter obj{id, codes.defaultReference};
                std::string response = to_json(obj);
                reque->push(response);
                return false;
            }
            return true;
        }
            //проверка валидности для си
        case codes.cppRequestType: {
            std::string git = tree.get("request.git_adress", codes.defaultGit);
            if (!validateAdress(git)) {
                stringFormatter obj{id, codes.defaultGit};
                std::string response = to_json(obj);
                reque->push(response);
                return false;
            }

            std::string target = tree.get("request.target", codes.defaultTarget);
            if (!validateTarget(target)) {
                stringFormatter obj{id, codes.defaultTarget};
                std::string response = to_json(obj);
                reque->push(response);
                return false;
            }
            return true;
        }

        default: {
            if (reque) {
                stringFormatter obj{id, codes.temporary};
                std::string response = to_json(obj);
                reque->push(response);
            }
            return false;
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
