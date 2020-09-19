#pragma once
#include <memory>
#include <string>

namespace networking {
class Connection;

class Chat {
  public:
    static std::unique_ptr<Chat> init(std::shared_ptr<Connection> connection, const std::string &username);

    void joinRoom(const std::string& name);
  private:
    Chat(std::shared_ptr<Connection> connection)
        : connection_(std::move(connection)) {
    }

    std::shared_ptr<Connection> connection_;
};
}  // namespace networking