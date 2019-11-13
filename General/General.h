#ifndef CONTINUUM_GENERAl_H
#define CONTINUUM_GENERAL_H

#include "../Queue/Queue.cpp"
#include "../Parser/Parser.cpp"
#include "../Manager/Manager.cpp"
#include "../Reporter/Reporter.cpp"
#include "../TestCase/TestCase.cpp"

#include <vector>

class General {
public:
	General();
	General(int cont_count);
	General(int p_count, int m_count, int r_count, int cont_count);
	~General();
	
	int TurnOn();
	int TurnOff();
	
private:
	Queue<JsonObject> rqueue;
	Queue<JsonObject> pqueue;
	Queue<TestCase> wqueue;
	std::vector<Parser> parsers;
	std::vector<Manager> managers;
	std::vector<Reporter> reporters;
}

#endif //CONTINUUM_GENERAL_H