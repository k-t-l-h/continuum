#include <boost/asio/io_service.hpp>
#include "General/General.h"
#include "Server/Server.h"

int main() {
    General gen = General(2);
    gen.turnOn();
    try
    {
        boost::asio::io_service io_service;
        server s(io_service, 8082, &gen);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    gen.turnOff();
    return 0;
}
