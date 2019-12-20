//
// Created by Evgeny Enin on 21.12.2019.
//

#ifndef CI_SERVER_H
#define CI_SERVER_H

#include "../General.h"
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/beast/core/buffers_to_string.hpp>

using boost::asio::ip::tcp;

class session
{
public:
    session(boost::asio::io_service& io_service, General* backend)
            : socket_(io_service), backend_(backend)
    {
    }

    tcp::socket& socket()
    {
        return socket_;
    }

    void start()
    {
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                boost::bind(&session::handle_read, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
    }

    void handle_read(const boost::system::error_code& error,
                     size_t bytes_transferred)
    {
        if (!error)
        {
            std::string request = boost::beast::buffers_to_string( boost::asio::buffer(data_, bytes_transferred));
            std::string answer = "";
            if (request.find("GET ") == 0) {
                answer = backend_->sendAnswer(request.substr(4, request.size() - 4));

            }
            if (request.find("TEST ") == 0) {
                backend_->getRequest(request.substr(5, request.size()-5), this);
            }
            boost::asio::async_write(socket_,
                                     boost::asio::buffer(answer, answer.size()),
                                     boost::bind(&session::handle_write, this,
                                                 boost::asio::placeholders::error));
        }
        else
        {
            delete this;
        }
    }

    void handle_write(const boost::system::error_code& error)
    {
        if (!error)
        {
            socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                    boost::bind(&session::handle_read, this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
        }
        else
        {
            delete this;
        }
    }

private:
    tcp::socket socket_;
    General* backend_;
    enum { max_length = 1024 };
    char data_[max_length];
};

class server {
public:
    server(boost::asio::io_service &io_service, short port, General* backend)
            : io_service_(io_service),
              acceptor_(io_service, tcp::endpoint(tcp::v4(), port)), backend_(backend) {
        session *new_session = new session(io_service_);
        acceptor_.async_accept(new_session->socket(),
                               boost::bind(&server::handle_accept, this, new_session,
                                           boost::asio::placeholders::error));
    }

    void handle_accept(session *new_session,
                       const boost::system::error_code &error) {
        if (!error) {
            new_session->start();
            new_session = new session(io_service_);
            acceptor_.async_accept(new_session->socket(),
                                   boost::bind(&server::handle_accept, this, new_session,
                                               boost::asio::placeholders::error));
        } else {
            delete new_session;
        }
    }

private:
    boost::asio::io_service &io_service_;
    tcp::acceptor acceptor_;
    General* backend_;
}

#endif //CI_SERVER_H
