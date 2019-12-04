#ifndef CONTINUUM_GENERAl_H
#define CONTINUUM_GENERAL_H

#include "../Queue/Queue.h"
#include "../Parser/Parser.h"
#include "../Manager/Manager.h"
#include "../Reporter/Reporter.h"
#include "../TestCase/TestCase.h"
#include "../DataBase/DataBase.h"


#include <boost/thread/thread.hpp>
#include <vector>
#include <memory>
#include <string>

class General {
public:
	General();
	General(int cont_count);
	General(int p_count, int m_count, int r_count, int cont_count);
	~General();
	
	void TurnOn();
	void TurnOff();
	int GetRequest(std::string request);
private:
	std::shared_ptr<Queue<std::string>> rqueue;
	std::shared_ptr<Queue<std::string>> pqueue;
	std::shared_ptr<Queue<TestCase*>> wqueue;
    std::shared_ptr<DataBase> db;
	std::vector<Parser> parsers;
	std::vector<Manager> managers;
	std::vector<Reporter> reporters;
}

#endif //CONTINUUM_GENERAL_H