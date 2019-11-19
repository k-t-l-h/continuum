#include "parser.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#define BAD_REQUEST_TYPE "NO TYPE"
#define DEF_ID "NO ID FOUND"
#define DEF "DEFAULT ANSWER"
#define CPP "CPP TEST"
#define WEB "WEB TEST"


namespace pt = boost::property_tree;
namespace str = std::string;

void Parser::workCycle() {

  while(true){
      //получаем заявку и создаем
      str request = get_request();
      pt::ptree tree;
      pt::read_json(request, tree);

      if (validateRequestTree(tree))
      {
        switch (tree.get<str>("request.request_type")) {
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
};


str Parser::get_request()
{
  return wque.pop();
};

bool Parser::validateRequestTree(const pt::ptree tree)
{
  //получаем тип заявки
  str request_type = tree.get<str>("request.request_type", BAD_REQUEST_TYPE);
  if (request_type == BAD_REQUEST_TYPE)
    return false; //нет типа заявки

  str id = tree.get<str>("request.id", DEF);

  if(id == DEF_ID)
    return false; //нет id

  switch (request_type) {
    //проверка валидности для веба
    case WEB:
      str host = tree.get<str>("request.host", DEF);
      if (validateHost(host))
        return false;
      str p = tree.get<str>("request.protocol", DEF);
      if (validateProtocol(p))
        return false;
      str m = tree.get<str>("request.method", DEF);
      if (validateMethod(m))
        return false;
      str ref = tree.get<str>("request.reference", DEF);
      if (validateReference(ref))
        return false;
      return true;

    //проверка валидности для си
    case CPP:
      str git = tree.get<str>("request.git_adress", DEF);
      if (validateAdress(git))
        return false;
      str target = tree.get<str>("request.target", DEF);
      if (validateTarget(target))
        return false;
      return true;

    default:
      return false;
  }

  return false;
};

//WEB CASE
bool Parser::validateHost(const std::string& s)
{
  static const boost::regex e("^(www\\.)?[a-z0-9]+([\\-\\.]{1}[a-z0-9]+)*\\.[a-z]{2,5}(:[0-9]{1,5})?(\\/.*)?$");
  return regex_match(s, e);
};

bool Parser::validateProtocol(const std::string& s)
{
  static const boost::regex e("[0|1]");
  return regex_match(s, e);
};

bool Parser::validateMethod(const std::string& s)
{
  static const boost::regex e("[0|1|2|3|4]");
  return regex_match(s, e);
};

bool Parser::validateReference(const std::string& s)
{
  static const boost::regex e("(10[0-3]|20[0-6]|30[0-8]|4(0[0-9)|1[0-7])|50[0-5])");
  return regex_match(s, e);
};


//CPP CASE
bool Parser::validateAdress(const std::string& s)
{
  static const boost::regex e("github\\.com\\/([a-zA-Z0-9\\_\\-]*)/([a-zA-Z0-9\\_\\-]*)");
  return regex_match(s, e);
};

bool Parser::validateTarget(const std::string& s)
{
  static const boost::regex e("([\_]*[a-zA-Z]+[a-zA-Z0-9\_]*)");
  return regex_match(s, e);
};
