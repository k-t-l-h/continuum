//
// Created by Keenshi on 25.10.2019.
//

#include "Container.h"

int Container::doTest(TestCase &test) {
    free_state = false;
    clearAnswer();
    if (test->type == 1) {
        if( validateWebTest(test) )
        {
            rqueue->push("error");
            return TEST_ERR;
        }
        if ( sendWebTestToDocker(test) )
            return DOCKER_ERR;
    }
    if (test->type == 0) {
        if( validateCTest(test) )
        {
            rqueue->push("error");
            return TEST_ERR;
        }
        if ( sendCTestToDocker(test) )
            return DOCKER_ERR;
    }
    if( generateAnswer() ) return QUEUE_ERR;
    free_state = true;
    return DONE;
}

int Container::clearAnswer() {
    answer = nullptr;
}

int Container::validateWebTest(const WebTestCase *test) const {
    if ( !test->host ) return TEST_ERR;
    command = "";
    std::string image = "web";
    std::string protocol;
    std::string method;
    switch( test->protocol ) {
        case 0:
            protocol =  "http://";
            break;
        case 1:
            protocol = "https://";
            break;
        default:
            return TEST_ERR;
    }
    switch( test->method ) {
        case 0:
            method = "OPTIONS";
            break;
        case 1:
            method = "GET";
            break;
        case 2:
            method = "POST";
            break;
        case 3:
            method = "PUT";
            break;
        case 4:
            method = "DELETE";
            break;
        default:
            return TEST_ERR;
    }
    command = "docker run web http -p h " + method + " " + protocol + host;
    return DONE;
}

int Container::validateCTest(const CTestCase *test) const {
    return TEST_ERR;
}

int Container::sendWebTestToDocker(const WebTestCase *test) {
    std::array<char, 128> buffer;
    answer = "";
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        answer += buffer.data();
    }
}

int Container::sendCTestToDocker(const CTestCase *test) {
    return DOCKER_ERR;
}

int Container::generateAnswer() {
    rqueue->push(answer);
    return Done;
}
