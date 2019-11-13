//
// Created by Keenshi on 25.10.2019.
// Will use docker api.
//

#ifndef CONTINUUM_CONTAINER_H
#define CONTINUUM_CONTAINER_H

#include <string>
//docker api


class Container {
public:
    Container();
    ~Container();

    const bool IsFree();
    const std::string GetContainerHost();
    const JsonObject GetAnswer();
    int DoTest(TestCase &test);
private:
	int ValidateTest();
	int SendTestToDocker();
	int WaitForTestEnd();
	int GenerateAnswer();
	
    bool free;
    std::string host;
    JsonObject answer;
};


#endif //CONTINUUM_CONTAINER_H
