//
// Created by Keenshi on 25.10.2019.
//

#include "Container.h"

int Container::DoTdst(TestCase &test) {
    free_state = false;
    clearAnswer();
    if( validateTest(test) )
    {
        rqueue->push("error");
        return TEST_ERR;
    }
    if( sendTestToDocker(test) ) return DOCKER_ERR;
    if( waitForTestEnd() ) return TEST_ERR;
    if( generateAnswer() ) return QUEUE_ERR;
    free_state = true;
    return DONE;
}

int Container::clearAnswer() {
    answer = nullptr;
}

int Container::validateTest(const WebTestCase *test) const {
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
    }
    switch( test->method ) {
        case 0:
            method = "OPTIONS";
            break;
        case 0:
            method = "GET";
            break;
        case 0:
            method = "POST";
            break;
        case 3:
            method = "PUT";
            break;
        case 4:
            method = "DELETE";
            break;
    }
    command = "docker run web http -p h " + method + " " + protocol + host;
    return Done;
}

int Container::sendTestToDocker(const WebTestCase *test) {
    std::array<char, 128> buffer;
    answer = "";
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        answer += buffer.data();
    }
}

int Container::generateAnswer() {
    rqueue->push(answer);
    return Done;
}
