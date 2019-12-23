//
// Created by Evgeny Enin on 21.12.2019.
//

#ifndef CI_SERVER_H
#define CI_SERVER_H

#include "../General/General.h"
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/beast/core/buffers_to_string.hpp>


class Session
{
public:

    Session(boost::asio::io_service& io_service, General *gen)
            : socket_(io_service), gen_(gen),timer_(io_service)
    {}

    boost::asio::ip::tcp::socket& socket()
    {
        return socket_;
    }

    void start()
    {
        started_ = true;
        last_ping = boost::posix_time::microsec_clock::local_time();
        do_read();
    }

    void stop() {
        if ( !started_) return;
        started_ = false;
        socket_.close();
    }

    bool started() const { return started_; }

    int id() const { return id_; }

private:

    void do_read() {
        async_read(socket_, boost::asio::buffer(readBuffer_, max_length),
                   boost::bind(&Session::read_complete, this,
                               boost::asio::placeholders::error,
                               boost::asio::placeholders::bytes_transferred),

                   boost::bind(&Session::handle_read, this,
                               boost::asio::placeholders::error,
                               boost::asio::placeholders::bytes_transferred));
        life_timer();
    }

    size_t read_complete(const boost::system::error_code & err, size_t bytes)
    {
        if (err) return 0;
        std::string msg(readBuffer_, readBuffer_ + bytes);
        bool found = msg.find("\r\n") < msg.size();
        return found ? 0 : 1;
    }

    void handle_read(const boost::system::error_code& error, size_t bytes_transferred)
    {
        if (error) stop();
        if ( !started() ) return;
        std::string request(readBuffer_, bytes_transferred);
        std::string answer = "";
        if (request.find("get") == 0) {
            on_report(request);
        } else if (request.find("test") == 0) {
            on_test(request);
        } else on_error();

    }

    void do_write(const std::string& msg) {
        if (!started()) return;
        std::copy(msg.begin(), msg.end(), writeBuffer_);
        socket_.async_write_some(boost::asio::buffer(writeBuffer_, msg.size()),
                                 boost::bind(&Session::handle_write, this,
                                             boost::asio::placeholders::error));
    }

    void on_error() {
        do_write("error Invalid request\r\n");
    }

    void on_report(std::string request) {
        std::stringstream ss;
        ss << request.substr(4, request.size() - 4);
        int id = -1;
        try {
            ss >> id;
        } catch (std::stringstream::failure& e) {
            std::cout << request << std::endl;
            std::cerr << "Invalid id\n";
        }
        if (id == -1) {
            do_write("error id\r\n\r\n");
            return;
        }
        auto report = gen_->sendAnswer(id);
        if (report.first) {
            if (report.second.size() == 0) {
                do_write("error Invalid test\r\n\r\n");
            } else {
                do_write("report " + report.second + "\r\n\r\n");
            }
        } else if (id_ == id) {
            do_write("wait\r\n\r\n");
        } else {
            do_write("error Non\r\n\r\n");
        }
    }

    void on_test(std::string request) {
        srand(time(NULL));
        int id = rand();
        id_ = id;
        std::string str_id = std::to_string(id);
        gen_->getRequest("{    \"request\": {    \"id\": \"" + str_id + "\",    " + request.substr(5, request.size()-5) + "    }}");
        do_write("id " + str_id + " \r\n\r\n");
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

    void on_check_life()
    {
        boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
        if ( (now - last_ping).total_milliseconds() > 50000) stop();
        last_ping = boost::posix_time::microsec_clock::local_time();
    }

    void life_timer()
    {
        timer_.expires_from_now(boost::posix_time::millisec(50000));
        timer_.async_wait( boost::bind(&Session::on_check_life, this));
    }

private:

    boost::asio::ip::tcp::socket socket_;
    General *gen_;
    boost::asio::deadline_timer timer_;
    enum { max_length = 1024 };
    char data_[max_length];
    char readBuffer_[max_length];
    char writeBuffer_[max_length];
    bool started_;
    boost::posix_time::ptime last_ping;
    int id_ = -1;
};

class server {
public:

    server(boost::asio::io_service &io_service, short port, General *gen)
            : io_service_(io_service),
              acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), gen_(gen) {
        Session *new_session = new Session(io_service_, gen_);
        acceptor_.async_accept(new_session->socket(),
                               boost::bind(&server::handle_accept, this, new_session,
                                           boost::asio::placeholders::error));
    }

    void handle_accept(Session *new_session,
                       const boost::system::error_code &error) {
        if (!error) {
            new_session->start();
            sessions.push_back(new_session);
            new_session = new Session(io_service_, gen_);
            acceptor_.async_accept(new_session->socket(),
                                   boost::bind(&server::handle_accept, this, new_session,
                                               boost::asio::placeholders::error));
        } else {
            std::cout << "error\n";
            delete new_session;
        }
    }

private:
    boost::asio::io_service &io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
    General *gen_;
    std::vector<Session *> sessions;
};

#endif //CI_SERVER_H
