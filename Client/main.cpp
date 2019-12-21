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


class Client : public boost::enable_shared_from_this<Client> {

    boost::asio::ip::tcp::socket socket;
    boost::asio::ip::address adress;
    int port;
    bool status = false;
    char readBuffer[1024];

public:

    Client(boost::asio::io_service& io, const std::string& adress, int port) : socket(io), adress(boost::asio::ip::address::from_string(adress)), port(port)
    {}

    void start() {
        try {
            //socket.async_connect(boost::asio::ip::tcp::endpoint(adress, port),boost::bind(&Client::on_connect, shared_from_this(),\
                                                                                          boost::asio::placeholders::error));
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

    void on_connect(const boost::system::error_code & err)
    {
        if ( err)
            std::cout << "error\n";

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
/*
    void readd() {
        socket.async_read_some(
                boost::asio::buffer(readBuffer),
                boost::bind(&Client::handleRead, shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    }

    void handleRead(const boost::system::error_code& e, std::size_t bytes_transferred) {
        if (e == boost::asio::error::eof) {
            std::cerr << "-client: " << socket.remote_endpoint().address().to_string()
                      << std::endl;
        }
        if (e)
            return;
        std::cout << "Answer: " << std::string(readBuffer, readBuffer + bytes_transferred);
    }

    void sendd(const std::string& message) {

        socket.async_write_some(
                boost::asio::buffer(message, message.size()),
                [self = shared_from_this()](const boost::system::error_code& e,
                                            std::size_t bytes_transferred) -> void {
                    self->readd();
                });
    }*/

    std::string read() {
        std::string result;
        int bytes = 0;
        try {
            bytes = socket.read_some(boost::asio::buffer(readBuffer, 1024)/*,
                                          [this](const boost::system::error_code &err, size_t byte) {
                                              if (err) return false;
                                              std::string tmp(this->buffer, this->buffer + byte);
                                              if (tmp.find("OK") == 0)
                                                  return true;
                                              if (std::string::npos != tmp.find("\r\n"))
                                                  return true;
                                              if (byte > 0) {
                                                  std::cout << "read" << std::endl;
                                                  return true;
                                              }
                                          }*/);
        }
        catch(boost::system::system_error& e) {
            status = false;
            std::cout << "Connection refused" << std::endl;
            std::cout << e.code() << std::endl;
            return result;
        }
        result.append(readBuffer, readBuffer + bytes);
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
        std::cout << "Your id is " << id << std::endl;
        result = "TEST {    \"request\": {    \"id\": \"" + std::to_string(id) + "\",    " + buf + "    }}";
    } else
        std::cout << "file is not open" << std::endl;
    return result;
}

int main() {
    boost::asio::io_service service;
    Client client(service, "0.0.0.0", 8082);
    client.start();
    std::string buffer;
    bool getFlag = false;
    bool testFlag = false;
    while (client.getStatus() && std::cin >> buffer) {
        std::string message;
        if (buffer.find("test") == 0) {
            std::cin >> buffer;
            message = createTest(buffer);
        }
        if (buffer.find("get") == 0) {
            int id;
            std::cin >> id;
            message = "GET " + std::to_string(id);
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