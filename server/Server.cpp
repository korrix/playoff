#include "Server.h"

#include "ChatSession.h"

namespace server {
Server::Server(boost::asio::io_context &io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    doAccept();
}

void Server::doAccept() {
    acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if(!ec) {
            std::make_shared<ChatSession>(std::move(socket), chat)->start();
        }

        doAccept();
    });
}
}  // namespace server