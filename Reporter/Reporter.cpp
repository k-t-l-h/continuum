#include "Reporter.h"
#include "../Queue/Queue.h"
#include <functional>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

Reporter::Reporter(std::shared_ptr<Queue<std::string>> qIn, std::shared_ptr<Queue<std::string>> qOut, std::shared_ptr<Database> db, int count)
    : queueIn(qIn), queueOut(qOut), db(db), threads(std::vector<std::thread>(count))
{}

Reporter::~Reporter(){
    std::for_each(threads.begin(), threads.end(),
                  [](std::thread& thread) { if (thread.joinable()) thread.join(); });
}

void Reporter::setWorkingState(bool status) {
    workStatus = status;
}

void Reporter::worker(std::shared_ptr<Reporter> self) {
    while (self->workStatus) {
        self->mutexR.lock();
        if (!self->queueIn->empty()) {
            std::cout << "start report"  << std::endl;
            std::string report = self->queueIn->pop();
            boost::property_tree::ptree tree;
            std::stringstream ss;
            ss << report;
            boost::property_tree::read_json(ss, tree);
            int id = tree.get("response.id", 0);
            std::string descriprion = tree.get("response.description", "");
            std::cout << id << " " << descriprion << std::endl;
            self->mutexR.unlock();
            self->db->insert(id, descriprion);
            //self->queueOut->push(report);
            //std::cout << "report: " << report << std::endl;
            std::cout << "end report"  << std::endl;
        } else {
            self->mutexR.unlock();
        }
    }
}


void Reporter::run() {
    for (auto it = threads.begin(); it != threads.end(); ++it)
        *it = std::thread(std::bind(worker, shared_from_this()));
}



