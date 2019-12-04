//
// Created by Keenshi on 25.10.2019.
// Will use docker api.
//

#ifndef CONTINUUM_CONTAINER_H
#define CONTINUUM_CONTAINER_H

#include <string>
#include <memory>
#include "../Queue/Queue.h"

#define DONE 0
#define TEST_ERR -1
#define DOCKER_ERR -2
#define QUEUE_ERR -3
//docker api


class Container {
public:
    Container(std::shared_ptr<Queue<std:string>> rq) : rqueue(rq), answer(0), command(0), free_state(true) {};
    ~Container();

    bool IsFree() const;
    int DoTest(TestCase &test);
	
private:
	int ClearAnswer();
	int ValidateTest(const WebTestCase *test) const;
    int ValidateTest(const CTestCase *test) const;
	int SendTestToDocker(const WebTestCase *test);
	int SendTestToDocker(const CTestCase *test);
	int WaitForTestEnd();
	int GenerateAnswer();
	
private:
    bool free_state;
    std::string answer;
    std::string command;
    std::shared_ptr<Queue<std:string>> rqueue;
};


#endif //CONTINUUM_CONTAINER_H
