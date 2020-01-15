#ifndef WEB_TEST_GENERATION_H
#define WEB_TEST_GENERATION_H

#include <memory>
#include "../Queue/Queue.h"
#include "../TestCase/TestCaseClass.h"
#include "../TestGeneration/Testgen.h"
#include "../TestCase/WebTestCase.h"

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


namespace pt = boost::property_tree;

class WebTestGeneration : public AbstractTestGeneration {
public:
    WebTestGeneration() = delete;

    WebTestGeneration(const WebTestGeneration &) = delete;

    WebTestGeneration operator=(const WebTestGeneration &) = delete;

    WebTestGeneration(const std::string request, std::shared_ptr <Queue<TestCase *>> wque);

    void convertToTestCase() override;

    int sendToWorker() const override;

private:
    std::shared_ptr <Queue<TestCase *>> wque;
    WebTestCase *tcase;
    std::string request;

};

#endif //WEB_TEST_GENERATION_H
