#include "Webtestgen.h"


namespace pt = boost::property_tree;

WebTestGeneration::WebTestGeneration(const std::string &request, std::shared_ptr <Queue<TestCase *>> wque) :
        request(request), wque(wque) {};

void WebTestGeneration::convertToTestCase() {
    //пропарсить поля

    pt::ptree tree;
    std::stringstream ss;
    ss << request;
    pt::read_json(ss, tree);

    std::string id = tree.get<std::string>("request.id", "FEELDEAD");

    std::string host = tree.get<std::string>("request.host", "localhost");

    int p = tree.get<int>("request.protocol", 0);
    int m = tree.get<int>("request.method", 0);
    int ref = tree.get<int>("request.reference", 200);

    //вызвать конструктор тест кейса
    tcase = std::make_shared<WebTestCase>(id, host, p, m, ref);
};


void WebTestGeneration::sendToWorker() const {
    wque->push(tcase);
};
