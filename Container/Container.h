//
// Created by Keenshi on 25.10.2019.
// Will use docker api.
//

#ifndef CONTINUUM_CONTAINER_H
#define CONTINUUM_CONTAINER_H

#include <string>
#include "../Queue/Queue.cpp"
//docker api


class Container {
public:
    Container(Queue<JsonObject> *rq);
    ~Container();

    const bool IsFree();
    const std::string GetContainerHost();
    const JsonObject GetAnswer();
    int DoTest(TestCase &test);
	
private:
	int ClearAnswer();
	int ValidateTest(const TestCase &test) const;
	int SendTestToDocker(const TestCase &test);
	int WaitForTestEnd();
	int GenerateAnswer();
	
private:
    bool free_state;
    std::string host;
    JsonObject answer;
	Queue<JsonObject> *rqueue;
};


#endif //CONTINUUM_CONTAINER_H
