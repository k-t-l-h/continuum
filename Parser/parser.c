#include "parser.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#define BAD_REQUEST_TYPE "NO TYPE"
#define DEF_ID "NO ID FOUND"
#define DEF "DEFAULT ANSWER"
#define CPP "CPP TEST"
#define WEB "WEB TEST"

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
  string request_type = tree.get<string>("request.request_type", BAD_REQUEST_TYPE);
  if (request_type == BAD_REQUEST_TYPE)
    return false; //нет типа заявки

  string id = tree.get<string>("request.id", DEF);

  if(id == DEF_ID)
    return false; //нет id

  switch (request_type) {
    //проверка валидности для веба
    case WEB:
      string host = tree.get<string>("request.host", DEF);
      if (validateHost(host))
        return false;
      string p = tree.get<string>("request.protocol", DEF);
      if (validateProtocol(p))
        return false;
      string m = tree.get<string>("request.method", DEF);
      if (validateMethod(m))
        return false;
      string ref = tree.get<string>("request.reference", DEF);
      if (validateReference(ref))
        return false;
      return true;

    //проверка валидности для си
    case CPP:
      string git = tree.get<string>("request.git_adress", DEF);
      if (validateAdress(git))
        return false;
      string target = tree.get<string>("request.target", DEF);
      if (validateTarget(target))
        return false;
      return true;

    default:
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
