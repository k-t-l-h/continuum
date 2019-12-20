#include "General.h"

std::mutex m;
std::mutex pmutex;
std::condition_variable condition;
bool notified = false;

General::General(int cont_count, int p_count, int m_count, int r_count) {
    rqueue = std::make_shared<Queue<std::string>>();
    pqueue = std::make_shared<Queue<std::string>>();
    wqueue = std::make_shared<Queue<TestCase*>>();
    oqueue = std::make_shared<Queue<std::string>>();
    db = std::make_shared<Database>();
    parser = std::make_shared<Parser>(pqueue, wqueue, rqueue);
    manager = std::make_shared<Manager>(wqueue, rqueue, cont_count);
    reporter = std::make_shared<Reporter>(rqueue, oqueue, db, 2);
}

void General::turnOn() {
    /*for (auto ptr = parsers.begin(); ptr < parsers.end(); ptr++)
    {
        (*ptr)->setStatus(true);
        std::thread thr(std::bind(&Parser::workCycle, std::ref(*ptr)));
        threads.emplace_back(std::move(thr));
    }*/
    parser->setStatus(true);
    //parser->workCycle();
    manager->setWorkingState(true);
    reporter->setWorkingState(true);
    manager->run();
    reporter->run();
    /*for (auto ptr = managers.begin(); ptr < managers.end(); ptr++)
    {
        (*ptr)->setWorkingState(true);
        std::thread thr(std::bind(&Manager::run, std::ref(*ptr)));
        threads.emplace_back(std::move(thr));
    }*/
    /*for (auto ptr = reporters.begin(); ptr < reporters.end(); ptr++)
    {
        (*ptr)->setWorkingState(true);
        std::thread thr(std::bind(&Reporter::run, std::ref(*ptr)));
        threads.emplace_back(std::move(thr));
    }*/
}

void General::turnOff() {
    /*for (auto ptr = parsers.begin(); ptr < parsers.end(); ptr++)
    {
        (*ptr)->setStatus(false);
    }*/
    parser->setStatus(false);
    /*for (auto ptr = managers.begin(); ptr < managers.end(); ptr++)
    {
        (*ptr)->setWorkingState(false);
    }
    for (auto ptr = reporters.begin(); ptr < reporters.end(); ptr++)
    {
        (*ptr)->setWorkingState(false);
    }*/
    //parser->setWorkingState(false);
    manager->setWorkingState(false);
    reporter->setWorkingState(false);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}

void General::getRequest(std::string request) {
    std::unique_lock<std::mutex> lock(m);
    pqueue->push(request);
    notified = true;
    condition.notify_one();
}

struct requestF{
    std::string id = "234";
    int request_type = 2;
    std::string host = "www.ya.ru";
    int protocol = 0;
    int method = 0;
    int reference = 200;

};

std::string to_jsonr(requestF const& obj) {
    pt::ptree out;
    out.put("request.id",          obj.id);
    out.put("request.request_type",    obj.request_type);
    out.put("request.host",    obj.host);
    out.put("request.protocol",    obj.protocol);
    out.put("request.method",    obj.method);
    out.put("request.reference",    obj.reference);


    std::ostringstream oss;

    pt::write_json(oss, out);
    return oss.str();
}

int main() {
    General server = General();
    server.turnOn();
    std::cout << "hi"<<std::endl;
    sleep(1.1);
    //requestF obj;
    std::string input = "{\"request\":{\"id\":\"234\",\"request_type\":\"1\",\"host\":\"www.ya.ru\",\"protocol\":\"0\",\"method\":\"0\",\"reference\":\"200\"}}";//to_jsonr(obj);
    std::string input1 = "{\"request\":{\"id\":\"235\",\"request_type\":\"1\",\"host\":\"www.ya.ru\",\"protocol\":\"0\",\"method\":\"0\",\"reference\":\"200\"}}";
    std::string input2 = "{\"request\":{\"id\":\"236\",\"request_type\":\"2\",\"host\":\"www.ya.ru\",\"protocol\":\"0\",\"method\":\"0\",\"reference\":\"200\"}}";
    std::string input3 = "{\"request\":{\"id\":\"237\",\"request_type\":\"2\",\"host\":\"www.ya.ru\",\"protocol\":\"0\",\"method\":\"0\",\"reference\":\"200\"}}";
    std::string input4 = "{\"request\":{\"id\":\"238\",\"request_type\":\"1\",\"host\":\"www.ya.ru\",\"protocol\":\"0\",\"method\":\"0\",\"reference\":\"200\"}}";
    server.getRequest(input1);
    std::cout << "line 111" <<std::endl;
    server.getRequest(input2);
    std::cout << "line 113" <<std::endl;
    server.getRequest(input3);
    std::cout << "line 115" <<std::endl;
    server.getRequest(input);
    std::cout << "line 117" <<std::endl;
    server.getRequest(input4);
    std::cout << "line 119" <<std::endl;
    while (true) {}
        //sleep(1);
    server.turnOff();
    return 0;
}