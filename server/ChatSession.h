#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>

namespace model {
class Event;
}

namespace server {
class Chat;

using boost::asio::ip::tcp;

class ChatSession : public std::enable_shared_from_this<ChatSession> {
  public:
    ChatSession(tcp::socket socket, Chat &chat);
    void start();

  private:
    tcp::socket socket_;
    Chat &chat_;

    std::string getRemoteIP() const;

    boost::asio::streambuf inputBuffer;
    boost::asio::streambuf outputBuffer;

    void readRequest();
    void dispatch(std::istream &stream);
    model::Event handleEvent(const model::Event &input);
    void sendResponse(const model::Event &response);
    void cleanup();
};
}  // namespace server