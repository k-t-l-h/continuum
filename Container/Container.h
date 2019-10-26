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

    bool Is_free();
    std::string GetContainerHost();
    JsonObject GetAnswer();
    int DoTest(TestCase);
private:
    bool free;
    std::string host;
    JsonObject answer;
};


#endif //CONTINUUM_CONTAINER_H
