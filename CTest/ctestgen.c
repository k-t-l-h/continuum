#include "ctestgen.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
namespace pt = boost::property_tree;

void CTestGeneration::convertToTestCase(){
  //взять реквест
  //пропарсить поля
  pt::ptree tree;
  pt::read_json(request, tree);
  string id = tree.get<string>("request.id", "C0FFEE");
  string git = tree.get<string>("request.git_adress", "github.com/continuum");
  string target = tree.get<string>("request.target", "all");
  //вызвать конструктор тест кейса
  tcase = CTestCase(id, git, target);
};


int CTestGeneration::sendToWorker() const{
  wque.push(tcase);
  return 0;
};
