#include "parser.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
namespace pt = boost::property_tree;

//парсер не должен быть владельцем базового ресурса,
//владельцем является general
Parser::Parser(shared_ptr<Queue<std::string>> _rque,
shared_ptr<Queue<TestCase*>> _wque,
shared_ptr<Queue<std::string>> _reque):
rque(_rque), wque(_wque), reque(_reque)
{};

void Parser::workCycle() const
{

  while(true){
      //получаем заявку и создаем
      if (!rque.isEmpty()){
        string request = get_request();
        //здесь будет параллельность
        workThread(request);
      }
}
};

void workThread(const std::string& request)
{
  pt::ptree tree;
  pt::read_json(request, tree);

  if (validateRequestTree(tree))
    {
      string request_type = tree.get<string>("request.request_type");
      switch (request_type) {
        case CPP:
          CTestGeneration ctg = CTestGeneration(request, wque);
          ctg.convertToTestCase();
          ctg.sendToWorker();
        break;
        case WEB:
          WebTestGeneration wtg = WebTestGeneration(request, wque);
          wtg.convertToTestCase();
          wtg.sendToWorker();
        break;
      }
    }
}

string Parser::get_request() const
{
  return rque.pop();
};

bool Parser::validateRequestTree(const pt::ptree tree) const
{
  //получаем тип заявки
  string request_type = tree.get<string>
  ("request.request_type", ResponseCode.invalidRequestStructure);

  if (request_type == ResponseCode.invalidRequestStructure){
      reque->push(ResponseCode.invalidRequestStructure);
      return false;
  }

  string id = tree.get<string>("request.id", ResponseCode.defaultId);

  if(id == ResponseCode.defaultId){
    reque->push(ResponseCode.defaultId);
    return false;
  }

  switch (request_type) {

    case ResponseCode.webRequestType:
      string host = tree.get<string>("request.host", ResponseCode.defaultHost);
      if (validateHost(host)){
        reque->push(ResponseCode.defaultHost);
        return false;
      }

      string p = tree.get<string>("request.protocol", ResponseCode.defaultProtocol);
      if (validateProtocol(p)){
        reque->push(ResponseCode.defaultProtocol);
        return false;
      }

      string m = tree.get<string>("request.method", ResponseCode.defaultMethod);
      if (validateMethod(m)){
        reque->push(ResponseCode.defaultMethod);
        return false;
      }

      string ref = tree.get<string>("request.reference", ResponseCode.defaultReference);
      if (validateReference(ref)){
        reque->push(ResponseCode.defaultReference);
        return false;
      }
      return true;

    //проверка валидности для си
    case ResponseCode.cppRequestType:
      string git = tree.get<string>("request.git_adress",  ResponseCode.defaultGit);
      if (validateAdress(git)){
        reque->push(ResponseCode.defaultGit);
        return false;
      }

      string target = tree.get<string>("request.target", DEF);
      if (validateTarget(target)){
        reque->push(ResponseCode.defaultTarget);
        return false;
      }
      return true;

    default:
      reque->push(ResponseCode.temporary);
      return false;
  }

  return false;
};

//WEB CASE
bool Parser::validateHost(const std::string& s) const
{
  static const boost::regex e("^(www\\.)?[a-z0-9]+([\\-\\.]{1}[a-z0-9]+)*\\.[a-z]{2,5}(:[0-9]{1,5})?(\\/.*)?$");
  return regex_match(s, e);
};

bool Parser::validateProtocol(const std::string& s) const
{
  static const boost::regex e("[0|1]");
  return regex_match(s, e);
};

bool Parser::validateMethod(const std::string& s) const
{
  static const boost::regex e("[0|1|2|3|4]");
  return regex_match(s, e);
};

bool Parser::validateReference(const std::string& s) const
{
  static const boost::regex e("(10[0-3]|20[0-6]|30[0-8]|4(0[0-9)|1[0-7])|50[0-5])");
  return regex_match(s, e);
};


//CPP CASE
bool Parser::validateAdress(const std::string& s) const
{
  static const boost::regex e("github\\.com\\/([a-zA-Z0-9\\_\\-]*)/([a-zA-Z0-9\\_\\-]*)");
  return regex_match(s, e);
};

bool Parser::validateTarget(const std::string& s) const
{
  static const boost::regex e("([\\_]*[a-zA-Z]+[a-zA-Z0-9\\_]*)");
  return regex_match(s, e);
};
