#include "Webtestgen.h"


namespace pt = boost::property_tree;

WebTestGeneration::WebTestGeneration(const std::string _request, shared_ptr<Queue<TestCase*>> _wque):
request(_request), wque(_wque)
{};

void WebTestGeneration::convertToTestCase(){
  //пропарсить поля
  pt::ptree tree;
  pt::read_json(request, tree);

  std::string id = tree.get<std::string>("request.id", "FEELDEAD");
  std::string host = tree.get<string>("request.host", "localhost");
  int p = tree.get<int>("request.protocol", 0);
  int m = tree.get<int>("request.method", 0);
  int ref = tree.get<int>("request.reference", 200);

  //вызвать конструктор тест кейса
  tcase = new WebTestCase(id, host, p, m, ref);
};


int WebTestGeneration::sendToWorker() const{
  wque->push(tcase);
  return 0;
};
