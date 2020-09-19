#include "ChatSession.h"

#include "Chat.h"

#include <boost/asio.hpp>
#include <spdlog/spdlog.h>

namespace server {
ChatSession::ChatSession(tcp::socket socket, Chat &chat)
    : socket_(std::move(socket))
    , chat_(chat) {
    spdlog::info("Client connected: {}", getRemoteIP());
}

void ChatSession::start() {
    readRequest();
}

void ChatSession::readRequest() {
    boost::asio::async_read_until(socket_, inputBuffer, '\n',
                                  [self = shared_from_this()](const boost::system::error_code &e, std::size_t) {
                                      if(!e) {
                                          std::istream is(&self->inputBuffer);
                                          self->dispatch(is);
                                      } else {
                                          self->cleanup();
                                      }
                                  });
}

void ChatSession::dispatch(std::istream &stream) {
    try {
        nlohmann::json json;
        stream >> json;

        auto event    = serialization::fromJson<model::Event>(json);
        auto response = chat_.handleEvent(this, event);
        sendResponse(response);

    } catch(std::exception ex) {
        sendResponse(model::Event::make(std::runtime_error{ex.what()}));
    }
}

void ChatSession::sendResponse(const model::Event &response) {
    std::ostream responseStream(&outputBuffer);
    responseStream << serialization::toJson(response) << std::endl;

    boost::asio::async_write(socket_, outputBuffer,
                             [self = shared_from_this()](boost::system::error_code ec, std::size_t) {
                                 if(!ec) {
                                     self->readRequest();
                                 } else {
                                     self->cleanup();
                                 }
                             });
}

std::string ChatSession::getRemoteIP() const {
    return socket_.remote_endpoint().address().to_string();
}

void ChatSession::cleanup() {
    spdlog::info("Client disconnected: {}", getRemoteIP());
    chat_.cleanup(this);
}
}  // namespace server