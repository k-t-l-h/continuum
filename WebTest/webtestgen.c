#include "webtestgen.h"

using namespace std;
namespace pt = boost::property_tree;

void WebTestGeneration::convertToTestCase(){
  //пропарсить поля
  pt::ptree tree;
  pt::read_json(request, tree);

  string id = tree.get<string>("request.id", "FEELDEAD");
  string host = tree.get<string>("request.host", "localhost");
  int p = tree.get<int>("request.protocol", 0);
  int m = tree.get<int>("request.method", 0);
  int ref = tree.get<int>("request.reference", 200);

  //вызвать конструктор тест кейса
  tcase = CTestCase(id, host, p, m, ref);
};


int WebTestGeneration::sendToWorker() const{
  wque.push(tcase);
  return 0;
};
