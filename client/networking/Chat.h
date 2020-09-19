#pragma once
#include "model/User.h"

#include <memory>
#include <string>

namespace networking {
class Connection;

class Chat {
  public:
    static std::unique_ptr<Chat> init(std::shared_ptr<Connection> connection, const std::string &username);

    void joinRoom(const std::string &name);
    void inviteUser(const std::string &roomName, const std::string &invitedUserName);
    void message(const std::string &roomName, const std::string &messageText);

  private:
    Chat(std::shared_ptr<Connection> connection, model::User current)
        : connection_(std::move(connection))
        , current_(std::move(current)) {
    }

    std::shared_ptr<Connection> connection_;
    model::User current_;
};
}  // namespace networking