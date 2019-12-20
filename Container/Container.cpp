//
// Created by Keenshi on 25.10.2019.
//

#include "Container.h"

int Container::doTest(TestCase *test) {
    free_state = false;
    clearAnswer();
    auto webTest = (WebTestCase *)test;
    if (webTest->rtype == 1) {
        if (collectWebDockerCommand(webTest)) {
            rqueue->push("error");
            return TEST_ERR;
        }
    }
    auto cTest = (CTestCase *)test;
    if (cTest->rtype == 0) {
        if (collectCDockerCommand(cTest)) {
            rqueue->push("error");
            return TEST_ERR;
        }
    }
    if( sendTestToDocker() ) return DOCKER_ERR;
    if( generateAnswer() ) return QUEUE_ERR;
    free_state = true;
    return DONE;
}

int Container::clearAnswer() {
    answer.clear();
    test_id.clear();
    return DONE;
}

int Container::collectWebDockerCommand(const WebTestCase *test) {
    if ( (test->host).empty() ) return TEST_ERR;
    command.clear();
    std::string image = "web";
    std::string protocol;
    std::string method;
    test_id = test->id;
    switch( test->p ) {
        case 0:
            protocol =  "http://";
            break;
        case 1:
            protocol = "https://";
            break;
        default:
            return TEST_ERR;
    }
    switch( test->m ) {
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
    command += "docker run web http -p h " + method + " " + protocol + test->host;
    return DONE;
}

int Container::collectCDockerCommand(const CTestCase *test) {
    return TEST_ERR;
}

int Container::sendTestToDocker() {
    std::string filename = test_id + "tmp.txt";
    system((command + " > " + filename).c_str());

    std::ifstream ifs(filename);
    std::string ret{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
    ifs.close();
    if (std::remove(filename.c_str()) != 0) {
        perror("Error deleting temporary file");
    }
    stringFormatter obj {test_id, ret};
    answer = to_json(obj);
    return DONE;
}

int Container::generateAnswer() {
    rqueue->push(answer);
    return DONE;
}

std::string Container::getAnswer() {
    return answer;
}

bool Container::isFree() const {
    return free_state;
}