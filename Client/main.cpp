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

boost::asio::io_service service;

class Client : public boost::enable_shared_from_this<Client>, boost::noncopyable {

    Client()
    : socket_(service), started_(true), timer_(service) {}

    void start(boost::asio::ip::tcp::endpoint ep)
    {
        socket_.async_connect(ep, boost::bind(&Client::on_connect, shared_from_this(), boost::asio::placeholders::error));
    }

public:

    static boost::shared_ptr<Client> start(const std::string& adress, int port)
    {
        boost::shared_ptr<Client> new_(new Client());
        new_->start(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(adress), port));
        return new_;
    }

    void stop()
    {
        if ( !started_) return;
        started_ = false;
        socket_.close();
    }

    bool started() { return started_; }

private:

    size_t read_complete(const boost::system::error_code & err, size_t bytes)
    {
        if ( err) return 0;
        bool found = std::find(readBuffer_, readBuffer_ + bytes, '\n') < readBuffer_ + bytes;
        return found ? 0 : 1;
    }

    void on_connect(const boost::system::error_code & err)
    {
        if ( err)
            std::cout << "error\n";

    }

    void do_read() {
        async_read(socket_, boost::asio::buffer(readBuffer_, max_length),
                   boost::bind(&Client::read_complete, shared_from_this(),
                               boost::asio::placeholders::error,
                               boost::asio::placeholders::bytes_transferred),
                   boost::bind(&Client::handle_read, shared_from_this(),
                               boost::asio::placeholders::error,
                               boost::asio::placeholders::bytes_transferred));
    }



    void do_write(const std::string& msg) {
        if (!started()) return;
        std::copy(msg.begin(), msg.end(), writeBuffer_);
        socket_.async_write_some(boost::asio::buffer(writeBuffer_, msg.size()),
                                 boost::bind(&Client::handle_write, shared_from_this(),
                                             boost::asio::placeholders::error));
    }

    void handle_read(const boost::system::error_code& e, std::size_t bytes_transferred) {
        if (e) stop();
        if ( !started() ) return;
        // process the msg
        std::string msg(readBuffer_, bytes_transferred);
        if ( msg.find("login ") == 0) on_login();
        else if ( msg.find("ping") == 0) on_ping(msg);
        else if ( msg.find("clients ") == 0) on_clients(msg);
    }

    void handle_write(const boost::system::error_code& error)
    {
        if (!error)       {
            do_read();
        }
        else
        {
            stop();
        }
    }

private:

boost::asio::ip::tcp::socket socket_;
bool started_;
boost::asio::deadline_timer timer_;
enum { max_length = 1024 };
char readBuffer_[max_length];
char writeBuffer_[max_length];

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