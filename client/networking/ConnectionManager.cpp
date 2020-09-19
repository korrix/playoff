#include "ConnectionManager.h"

#include "Connection.h"

#include <boost/asio.hpp>
#include <thread>

namespace networking {
using boost::asio::ip::tcp;

struct ConnectionManager::Impl {
    Impl()
        : resolver{io_context}
        , socket{io_context} {
    }

    void runIO() {
        io_context.run();
    }

    void connect(const std::string &server, unsigned short port) {
        auto endpoints = resolver.resolve(server, std::to_string(port));
        boost::asio::connect(socket, endpoints);
    }

    std::thread thread;
    boost::asio::io_context io_context;
    tcp::resolver resolver;
    tcp::socket socket;
};

ConnectionManager::ConnectionManager() {
    impl = std::make_unique<Impl>();
}

ConnectionManager::~ConnectionManager() = default;

std::shared_ptr<Connection> ConnectionManager::connect(const std::string &server, unsigned short port) {
    impl->connect(server, port);
    return std::make_shared<Connection>(impl->socket);
}
}  // namespace networking