#include "General.h"

std::mutex m;
std::mutex pmutex;
std::condition_variable condition;
bool notified = false;

General::General(int cont_count) {
    rqueue = std::make_shared<Queue<std::string>>();
    pqueue = std::make_shared<Queue<std::string>>();
    wqueue = std::make_shared<Queue<TestCase*>>();
    oqueue = std::make_shared<Queue<std::string>>();
    db = std::make_shared<Database>();
    parser = std::make_shared<Parser>(pqueue, wqueue, rqueue);
    manager = std::make_shared<Manager>(wqueue, rqueue, cont_count);
    reporter = std::make_shared<Reporter>(rqueue, oqueue, db, cont_count);
}

void General::turnOn() {
    parser->setStatus(true);
    manager->setWorkingState(true);
    reporter->setWorkingState(true);
    manager->run();
    reporter->run();
}

void General::turnOff() {
    parser->setStatus(false);
    manager->setWorkingState(false);
    reporter->setWorkingState(false);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}

std::string General::sendAnswer(const std::string& id) {
    std::string result;
    if (!db->select(std::stoi(id), result))
        result = "Not Found";
    return result;
}

void General::getRequest(const std::string& request) {
    std::unique_lock<std::mutex> lock(m);
    pqueue->push(request);
    notified = true;
    condition.notify_one();
}

/*
int main() {
    General server = General(2);
    server.turnOn();
    std::cout << "hi"<<std::endl;
    sleep(1.1);
    //requestF obj;
    std::string input = "{\"request\":{\"id\":\"234\",\"request_type\":\"1\",\"host\":\"www.ya.ru\",\"protocol\":\"0\",\"method\":\"0\",\"reference\":\"200\"}}";//to_jsonr(obj);
    std::string input1 = "{\"request\":{\"id\":\"235\",\"request_type\":\"1\",\"host\":\"www.ya.ru\",\"protocol\":\"0\",\"method\":\"0\",\"reference\":\"200\"}}";
    std::string input2 = "{\"request\":{\"id\":\"236\",\"request_type\":\"1\",\"host\":\"www.ya.ru\",\"protocol\":\"0\",\"method\":\"0\",\"reference\":\"200\"}}";
    std::string input3 = "{\"request\":{\"id\":\"237\",\"request_type\":\"1\",\"host\":\"www.ya.ru\",\"protocol\":\"0\",\"method\":\"0\",\"reference\":\"200\"}}";
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
}*/