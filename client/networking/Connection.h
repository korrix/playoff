#pragma once

#include "model/Event.h"

#include <boost/asio/ip/tcp.hpp>

namespace networking {
class Connection {
  public:
    Connection(boost::asio::ip::tcp::socket &socket)
        : socket_(socket) {
    }

    model::Event request(const model::Event &event);

  private:
    boost::asio::ip::tcp::socket &socket_;
};
}  // namespace networking