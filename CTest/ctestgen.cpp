#include "ctestgen.h"

#include <memory>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
namespace pt = boost::property_tree;

CTestGeneration::CTestGeneration(const string _request, shared_ptr<Queue<TestCase*>> _wque):
request(_request), wque(_wque)
{};

void CTestGeneration::convertToTestCase(){
  //взять реквест
  //пропарсить поля
  pt::ptree tree;
  pt::read_json(request, tree);

  string id = tree.get<string>("request.id", "C0FFEE");
  string git = tree.get<string>("request.git_adress", "github.com/continuum");
  string target = tree.get<string>("request.target", "all");
  //вызвать конструктор тест кейса
  tcase = new CTestCase(id, git, target);
};


int CTestGeneration::sendToWorker() const{
  wque->push(tcase);
  return 0;
};
