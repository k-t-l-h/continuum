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

    Client(std::string& msg)
    : socket_(service), started_(true), timer_(service), message(msg) {}

    void start(boost::asio::ip::tcp::endpoint ep)
    {
        socket_.async_connect(ep, boost::bind(&Client::on_connect, shared_from_this(), boost::asio::placeholders::error));
    }

public:

    static boost::shared_ptr<Client> start(boost::asio::ip::tcp::endpoint ep, std::string message)
    {
        boost::shared_ptr<Client> new_(new Client(message));
        new_->start(ep);
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
        std::string msg(readBuffer_, readBuffer_ + bytes);
        bool found = msg.find("\r\n\r\n") < msg.size();
        return found ? 0 : 1;
    }

    void on_connect(const boost::system::error_code & err)
    {
        if (err) {
            std::cout << "Connection refused\n";
        }
        else {
            if (message.find("test") == 0) {
                do_write(message + "\r\n");
            } else if (message.find("get") == 0) {
                std::stringstream ss(message.substr(4, message.size() - 1));
                ss >> id;
                do_write(message + "\r\n");
            } else {
                std::cout << "Invalid request" << std::endl;
                stop();
            }
        }


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
        std::string msg(readBuffer_, readBuffer_ + bytes_transferred);
        if (msg.find("report") == 0) on_report(msg);
        else if (msg.find("wait") == 0) on_wait(msg);
        else if (msg.find("error") == 0) on_error(msg);
        else if (msg.find("id") == 0) on_id(msg);
    }

    void handle_write(const boost::system::error_code& error)
    {
        if (!error)       {
            do_read();
        }
        else {
            stop();
        }
    }

    void on_report(std::string msg) {
        std::cout << "Id: " << id << "\n" << "Success!"/*msg.substr(7, msg.size() - 1)*/ << std::endl;
        stop();
    }

    void on_wait(std::string msg) {
        timer_.expires_from_now(boost::posix_time::millisec(1000));
        timer_.async_wait( boost::bind(&Client::do_write, shared_from_this(), "get " +std::to_string(id) + "\r\n"));
    }

    void on_id(std::string msg) {
        std::stringstream ss(msg.substr(3, msg.size() - 1));
        ss >> id;
        timer_.expires_from_now(boost::posix_time::millisec(1000));
        timer_.async_wait( boost::bind(&Client::do_write, shared_from_this(), "get " +std::to_string(id) + "\r\n"));
    }

    void on_error(std::string msg) {
        if (msg.find("Non") < msg.size()) {
            std::cout << "Id: " << id << "\nError! Test is not found!\n";
        } else
            std::cout << "Id: " << id << "\nError! Invalid test!\n";
        stop();
    }

private:

boost::asio::ip::tcp::socket socket_;
bool started_;
boost::asio::deadline_timer timer_;
std::string message;
int id;
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
        while (getline(fin, line)) {
            auto rt = line.find("web");
            auto pr1 = line.find("HTTP");
            auto pr2 = line.find("HTTPS");
            auto mo = line.find("OPTIONS");
            auto mg = line.find("GET");
            auto mp = line.find("POST");
            auto md = line.find("DELETE");
            auto mpt = line.find("PUT");
            if (rt < line.size()) {
                line.erase(rt, rt + 3);
                line.insert(rt, "1\",");
            }
            if (pr1 < line.size()) {
                line.erase(pr1, pr1 + 4);
                line.insert(pr1, "0\",");
            }
            if (pr2 < line.size()) {
                line.erase(pr2, pr2 + 5);
                line.insert(pr2, "1\",");
            }
            if (mo < line.size()) {
                line.erase(mo, mo + 7);
                line.insert(mo, "0\",");
            }
            if (mg < line.size()) {
                line.erase(mg, mg + 3);
                line.insert(mg, "1\",");
            }
            if (mp < line.size()) {
                line.erase(mp, mp + 4);
                line.insert(mp, "2\",");
            }
            if (mpt < line.size()) {
                line.erase(mpt, mpt + 3);
                line.insert(mpt, "3\",");
            }
            if (md < line.size()) {
                line.erase(md, md + 6);
                line.insert(md, "4\",");
            }
            buf += line;
        }
        fin.close();
        srand(time(NULL));
        /*int id = rand();
        std::ofstream fout(".ci_id", std::ios_base::app);
        if (fout.is_open()){
            fout << id;
            fout.close();
        }*/
        result = buf;
    } else
        std::cout << "file is not open" << std::endl;
    return result;
}

void input(std::string &message) {
    std::string buffer;
    while (std::cin >> buffer) {
        if (buffer.find("test") == 0) {
            std::cin >> buffer;
            message = "test " + createTest(buffer);
        }
        if (buffer.find("get") == 0) {
            int id;
            std::cin >> id;
            message = "get " + std::to_string(id);
        }
        if (buffer.find("exit") == 0) {
        break;
        }
    }
}

void loop(boost::asio::deadline_timer &timer_, std::vector<boost::shared_ptr<Client>>& clients, boost::asio::ip::tcp::endpoint ep, std::string& message) {
    if (message.size() > 0) {
        clients.push_back(Client::start(ep, message));
        message = "";
    }
    timer_.expires_from_now(boost::posix_time::millisec(50));
    timer_.async_wait( boost::bind(loop, std::ref(timer_), std::ref(clients), ep, std::ref(message)));
}

void worker_thread()
{
    service.run();
}

int main() {
    boost::asio::deadline_timer timer_(service);
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("0.0.0.0"), 8082);
    std::string message;
    std::vector<boost::shared_ptr<Client>> clients;
    loop(timer_, clients, ep, message);
    service.post(boost::bind(input, std::ref(message)));
    service.post(boost::bind(loop, std::ref(timer_), std::ref(clients), ep, std::ref(message)));
    boost::thread_group threads;
    threads.create_thread(worker_thread);
    threads.create_thread(worker_thread);
    threads.join_all();
    return 0;
}