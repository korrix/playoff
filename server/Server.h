#pragma once
// Based on https://think-async.com/Asio/boost_asio_1_18_0/doc/html/boost_asio/example/cpp11/chat/chat_server.cpp

#include "Chat.h"

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace server {
using boost::asio::ip::tcp;

class Server {
  public:
    Server(boost::asio::io_context &io_context, short port);

  private:
    void doAccept();

    tcp::acceptor acceptor_;
    Chat chat;
};
}  // namespace server