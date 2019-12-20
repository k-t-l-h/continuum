

#include "Ctestgen.h"

#include <string>
#include <memory>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


namespace pt = boost::property_tree;

CTestGeneration::CTestGeneration(const std::string _request, std::shared_ptr<Queue<TestCase*>> _wque):
request(_request), wque(_wque)
{};

void CTestGeneration::convertToTestCase(){
  //взять реквест
  //пропарсить поля
  pt::ptree tree;

  std::stringstream ss;
  ss << request;
  pt::read_json(ss, tree);

  std::string id = tree.get<std::string>("request.id", "C0FFEE");
  std::string git = tree.get<std::string>("request.git_adress", "github.com/continuum");
  std::string target = tree.get<std::string>("request.target", "all");
  //вызвать конструктор тест кейса
  tcase = new CTestCase(id, git, target);
};


int CTestGeneration::sendToWorker() const{
  wque->push(tcase);
  return 0;
};
