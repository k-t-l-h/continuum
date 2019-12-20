//#define BOOST_ASIO_HAS_STD_STRING_VIEW

#include <boost/asio.hpp>
#include <functional>
#include <iostream>
#include <fstream>
#include <thread>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <ctime>
#include <memory>
#include <string>


class Client : public std::enable_shared_from_this<Client> {

    boost::asio::ip::tcp::socket socket;
    boost::asio::ip::address adress;
    int port;
    bool status = false;
    char buffer[25];

public:

    Client(boost::asio::io_context& io, const std::string& adress, int port) : socket(io), adress(boost::asio::ip::address::from_string(adress)), port(port)
    {}

    void start() {
        try {
            socket.connect(boost::asio::ip::tcp::endpoint(adress, port));
            status = true;
            std::cout << "Connection with " << adress.to_string() << ":" << port << std::endl;
        }
        catch(boost::system::system_error& e)
        {
            std::cout << "Connection refused" << std::endl;
            std::cout << e.code() << std::endl;
        }
    }

    void close() {
        try {
            socket.close();
            status = false;
        }
        catch(boost::system::system_error& e)
        {
            std::cout << "Connection refused" << std::endl;
            std::cout << e.code() << std::endl;
        }
    }

    bool getStatus() {
        return status;
    }

    void send(const std::string& message) {
        boost::asio::streambuf request;
        try {
            boost::asio::write(socket, boost::asio::buffer(message.data(), message.size()));
        }
        catch(boost::system::system_error& e) {
            status = false;
            std::cout << "Connection refused" << std::endl;
            std::cout << e.code() << std::endl;
        }
    }

    std::string read() {
        std::string result;
        int bytes = 0;
        try {
            bytes = boost::asio::read(socket, boost::asio::buffer(buffer, 25),
                                          [this](const boost::system::error_code &err, size_t byte) {
                                              if (err) return false;
                                              std::string tmp(this->buffer, this->buffer + byte);
                                              int count = std::count(tmp.begin(), tmp.end(), ' ');
                                              return count > 1;
                                          });
        }
        catch(boost::system::system_error& e) {
            status = false;
            std::cout << "Connection refused" << std::endl;
            std::cout << e.code() << std::endl;
            return result;
        }
        std::stringstream s;
        int it = sizeof("report");
        for (; buffer[it] != ' '; ++it) {
            s << buffer[it];
        }
        int size = 0;
        s >> size;
        result.append(buffer + ++it, buffer + bytes);
        if (size == (bytes - it)) {
            return result;
        }
        size -= (bytes - it);
        char *data = new char[size];
        try {
            boost::asio::read(socket, boost::asio::buffer(data, size));
            result.append(data, size);
        }
        catch(boost::system::system_error& e) {
            status = false;
            std::cout << "Connection refused" << std::endl;
            std::cout << e.code() << std::endl;
        }
        delete[] data;
        return result;
    }
};

std::string createTest(const std::string& buffer) {
    std::string result;
    std::ifstream fin(buffer);
    if (fin.is_open()) {
        std::string line;
        std::string buf;
        while (getline(fin, line))
            buf += line;
        fin.close();
        srand(time(NULL));
        int id = rand();
        std::ofstream fout(".ci_id", std::ios_base::app);
        if (fout.is_open()){
            fout << id;
            fout.close();
        }
        std::cout << "Your id" << id << std::endl;
        result = "test {    \"request\": {    \"id\": \"" + std::to_string(id) + "\",    " + buf + "    }}";
    } else
        std::cout << "file is not open" << std::endl;
    return result;
}

int main() {
    boost::asio::io_context context;
    Client client(context, "0.0.0.0", 8082);
    client.start();
    std::string buffer;
    bool getFlag = false;
    bool testFlag = false;
    while (client.getStatus() && std::cin >> buffer) {
        std::string message;
        if (testFlag) {
            message = createTest(buffer);
            testFlag = false;
        }
        if (getFlag) {
            message = buffer;
            if (buffer.find("last") == 0) {
                std::ifstream fin(".ci_id", std::ios_base::in);
                if (fin.is_open()) {
                    std::string line;
                    while (getline(fin, line))
                        buffer = line;
                } else {
                    buffer = "";
                    std::cout << "Enter your id" << std::endl;
                }
            }
            message = "get " + buffer;
            getFlag = false;
        }
        if (buffer.find("test") == 0 && !testFlag) {
            testFlag = true;
        }
        if (buffer.find("get") == 0 && !getFlag) {
            getFlag = true;
        }
        if (buffer.find("exit") == 0 && !getFlag) {
            break;
        }
        if (message.size() > 0) {
            client.send(message);
            std::cout << "answer: " << client.read() << std::endl;
        }

    }
    client.close();

    return 0;
}