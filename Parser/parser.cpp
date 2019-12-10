#include "../Parser/parser.h"

#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>

using namespace std;
namespace pt = boost::property_tree;

struct dbFormatter{
	string id;
	string status;
};

string to_json(dbFormatter const& obj) {
      pt::ptree out;
      out.put("dbFormatter.id",          obj.id);
      out.put("dbFormatter.status",    obj.status);
      ostringstream oss;
      pt::write_json(oss, out);
      return oss.str();
}


//парсер не должен быть владельцем базового ресурса,
//владельцем является general
Parser::Parser(shared_ptr<Queue<std::string>> _rque,
shared_ptr<Queue<TestCase*>> _wque,
shared_ptr<Queue<std::string>> _reque):
rque(_rque), wque(_wque), reque(_reque), workStatus(false),
{
    maxPool = thread::hardware_concurrency();
    for(int i = 0; i < maxPool; i++){
    threadPool.push_back(std::thread(std::bind(&Parser::workCycle, this)));
  }
};

Parser::~Parser(){
  for_each(threadPool.begin(), threadPool.end(), mem_fn(&thread::join));
};

void Parser::setStatus(bool newStatus){
  workStatus = newStatus;
};

void Parser::workCycle() const
{
  unique_lock<std::mutex> lock(m);
  //bool состояния
  while(workStatus){
      //избавляемся от внезапных пробуждений
      while (!notified) {
        condition.wait(lock);
      }

      if (!rque->empty()){
        string request = get_request();
        workThread(request);
      }
      notified = false;
    }
};

void workThread(const std::string& request)
{
  pt::ptree tree;
  pt::read_json(request, tree);

  if (validateRequestTree(tree))
    {
      int request_type = tree.get<int>("request.request_type");
      switch (request_type) {
        case codes.cppRequestType:
          CTestGeneration* ctg = new CTestGeneration(request, wque);
          ctg->convertToTestCase();
          ctg->sendToWorker();
        break;
        case codes.webRequestType:
          WebTestGeneration* wtg = new WebTestGeneration(request, wque);
          wtg->convertToTestCase();
          wtg->sendToWorker();
        break;
      }
    }
}

string Parser::get_request() const
{
  return rque->pop();
};

bool Parser::validateRequestTree(const pt::ptree tree) const
{
  //получаем тип заявки
  int request_type = tree.get<int>
  ("request.request_type", codes.invalidRequestStructure);

  string id = tree.get<string>("request.id", codes.defaultId);

  if (request_type == codes.invalidRequestStructure){

      dbFormatter obj {id, codes.invalidRequestStructure};
      string response = to_json(obj);
      reque->push(response);
      return false;
  }

  if(id == codes.defaultId){
    dbFormatter obj {id, codes.defaultId};
    string response = to_json(obj);
    reque->push(response);
    return false;
  }

  switch (request_type) {

    case codes.webRequestType:
      string host = tree.get<string>("request.host", ResponseCode.defaultHost);
      if (validateHost(host)){
        dbFormatter obj {id, codes.defaultHost};
        string response = to_json(obj);
        reque->push(response);

        return false;
      }

      string p = tree.get<string>("request.protocol", codes.defaultProtocol);
      if (validateProtocol(p)){
        dbFormatter obj {id, codes.defaultProtocol};
        string response = to_json(obj);
        reque->push(response);
        return false;
      }

      string m = tree.get<string>("request.method", codes.defaultMethod);
      if (validateMethod(m)){
        dbFormatter obj {id, codes.defaultMethod};
        string response = to_json(obj);
        reque->push(response);
        return false;
      }

      string ref = tree.get<string>("request.reference", codes.defaultReference);
      if (validateReference(ref)){
        dbFormatter obj {id, codes.defaultReference};
        string response = to_json(obj);
        reque->push(response);
        return false;
      }
      return true;

    //проверка валидности для си
    case codes.cppRequestType:
      string git = tree.get<string>("request.git_adress",  codes.defaultGit);
      if (validateAdress(git)){
        dbFormatter obj {id, codes.defaultGit};
        string response = to_json(obj);
        reque->push(response);
        return false;
      }

      string target = tree.get<string>("request.target", codes.defaultTarget);
      if (validateTarget(target)){
        dbFormatter obj {id, codes.defaultTarget};
        string response = to_json(obj);
        reque->push(response);
        return false;
      }
      return true;

    default:
    if(reque){
      dbFormatter obj {id, codes.temporary};
      string response = to_json(obj);
      reque->push(response);
    }
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
