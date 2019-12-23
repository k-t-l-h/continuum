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


class Session : public boost::enable_shared_from_this<Session>
{
public:

    Session(boost::asio::io_service& io_service, General* backend)
            : socket_(io_service), backend_(backend), timer_(io_service)
    {}

    boost::asio::ip::tcp::socket& socket()
    {
        return socket_;
    }

    void start()
    {
        started_ = true;
        backend_->addSession(shared_from_this());
        last_ping = boost::posix_time::microsec_clock::local_time();
        do_read();
    }

    void stop() {
        if ( !started_) return;
        started_ = false;
        socket_.close();
        auto self = shared_from_this();
        backend_->removeSession(self);
    }

    bool started() const { return started_; }

    std::vector<int> id() const { return id_; }

private:

    void do_read() {
        async_read(socket_, boost::asio::buffer(readBuffer_, max_length),
                boost::bind(&Session::read_complete, shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred),
                                boost::bind(&Session::handle_read, shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
        life_timer();
    }

    size_t read_complete(const boost::system::error_code & err, size_t bytes)
    {
        if ( err) return 0;
        std::string msg(readBuffer_, readBuffer_ + bytes);
        bool found = std::find(readBuffer_, readBuffer_ + bytes, '\n') < readBuffer_ + bytes;
        return found ? 0 : 1;
    }

    void handle_read(const boost::system::error_code& error, size_t bytes_transferred)
    {
        if (!error)
        {
            if (error) stop();
            if ( !started() ) return;
            std::string request(readBuffer_, bytes_transferred);
            std::string answer = "";
            if (request.find("get") == 0) {
                on_report(bytes_transferred);
            }
            if (request.find("bye") == 0) {
                stop();
            }
            if (request.find("test") == 0) {
                on_test(bytes_transferred);
            } else on_error();
        }
        else
        {
            stop();
        }
    }

    void do_write(const std::string& msg) {
        if (!started()) return;
        std::copy(msg.begin(), msg.end(), writeBuffer_);
        socket_.async_write_some(boost::asio::buffer(writeBuffer_, msg.size()),
                                 boost::bind(&Session::handle_write, shared_from_this(),
                                             boost::asio::placeholders::error));
    }

    void on_error() {
        do_write("error Invalid request");
    }

    void on_report(size_t bytes_transferred) {
        std::string request = boost::beast::buffers_to_string( boost::asio::buffer(readBuffer_, bytes_transferred));
        std::stringstream ss;
        ss << request.substr(4, request.size() - 4);
        int id = -1;
        try {
            ss >> id;
        } catch (std::stringstream::failure& e) {
            std::cerr << "Invalid id\n";
        }
        if (id == -1) {
            do_write("error Nonexistent");
            return;
        }
        auto session = backend_->findSession(shared_from_this());
        auto report = backend_->sendAnswer(id);
        if (report.first) {
            if (report.second.size() == 0) {
                do_write("error Invalid test");
            } else
                do_write("report " + report.second);
        }
        if (session.first) {
            do_write("wait");
        } else {
            do_write("error Nonexistent");
        }
    }

    void on_test(size_t bytes_transferred) {
        std::string request = boost::beast::buffers_to_string( boost::asio::buffer(readBuffer_, bytes_transferred));
        srand(time(NULL));
        int id = rand();
        id_.push_back(id);
        std::string str_id = std::to_string(id);
        backend_->getRequest("{    \"request\": {    \"id\": \"" + str_id + "\",    " + request.substr(5, request.size()-5) + "    }}");
        do_write("id " + str_id);
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
        timer_.async_wait( boost::bind(&Session::on_check_life, shared_from_this()));
    }

private:

    boost::asio::ip::tcp::socket socket_;
    General* backend_;
    boost::asio::deadline_timer timer_;
    enum { max_length = 1024 };
    char data_[max_length];
    char readBuffer_[max_length];
    char writeBuffer_[max_length];
    bool started_;
    boost::posix_time::ptime last_ping;
    std::vector<int> id_;
};

class server {
public:

    server(boost::asio::io_service &io_service, short port, General* backend)
            : io_service_(io_service),
              acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), backend_(backend) {
        Session *new_session = new Session(io_service_, backend_);
        acceptor_.async_accept(new_session->socket(),
                               boost::bind(&server::handle_accept, this, new_session,
                                           boost::asio::placeholders::error));
    }

    void handle_accept(Session *new_session,
                       const boost::system::error_code &error) {
        if (!error) {
            new_session->start();
            new_session = new Session(io_service_, backend_);
            acceptor_.async_accept(new_session->socket(),
                                   boost::bind(&server::handle_accept, this, new_session,
                                               boost::asio::placeholders::error));
        } else {
            new_session->stop();
        }
    }

private:
    boost::asio::io_service &io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
    General* backend_;
};

#endif //CI_SERVER_H
