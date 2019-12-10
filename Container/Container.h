//
// Created by Keenshi on 25.10.2019.
// Will use docker api.
//

#ifndef CONTINUUM_CONTAINER_H
#define CONTINUUM_CONTAINER_H

#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include "../Queue/Queue.h"
#include "../TestCase/TestCaseClass.h"
#include "../TestCase/CTestCase.h"
#include "../TestCase/WebTestCase.h"

#define DONE 0
#define TEST_ERR -1
#define DOCKER_ERR -2
#define QUEUE_ERR -3
//docker api


class Container {
public:
    explicit Container(std::shared_ptr<Queue<std::string>> &rq) : rqueue(rq), answer(""), command(""), free_state(true) {};
    Container() = delete;
    Container(Container &cont) = delete;


    bool isFree() const;
    int doTest(TestCase *test);
	
private:
	int clearAnswer();
	int collectWebDockerCommand(const WebTestCase *test);
    int collectCDockerCommand(const CTestCase *test);
	int sendTestToDocker();
	int generateAnswer();
	
private:
    bool free_state;
    std::string answer;
    std::string command;
    std::shared_ptr<Queue<std::string>> rqueue;
};


#endif //CONTINUUM_CONTAINER_H
