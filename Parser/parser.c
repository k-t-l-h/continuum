#include "parser.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#define BAD_REQUEST_TYPE "NO TYPE"
#define DEF_ID ""

namespace pt = boost::property_tree;
namespace str = std::string;

void Parser::workCycle( ) {

  while(true){
      //
      get_request();
  }

};

bool Parser::validateRequest(const str &request)
{
  //cоздаем и заполняем дерево
  pt::ptree tree;
  pt::read_json(request, tree);

  //получаем тип заявки
  str request_type = tree.get<str>("request.request_type", "null");
  if (request_type == BAD_REQUEST_TYPE)
    return false; //нет типа заявки

  str id = tree.get<str>("request.id", DEF_ID);

  if(id == DEF_ID)
    return false; //нет id


  switch (request_type) {
    //проверка валидности для веба
    case WEB:
      if (validateHost())
        return false;
      if (validateProtocol())
        return false;
      if (validateMethod())
        return false;
      if (validateReference())
        return false;
      return true;

    //проверка валидности для си
    case CPP:
      if (validateAdress())
        return false;
      if (validateTarget())
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
