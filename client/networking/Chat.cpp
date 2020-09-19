#include "Chat.h"

#include "model/Event.h"
#include "networking/Connection.h"

namespace networking {
std::unique_ptr<Chat> Chat::init(std::shared_ptr<Connection> connection, const std::string &username) {
    model::User user;
    user.setName(username);
    auto response = connection->request(model::Event::make(user));
    return std::unique_ptr<Chat>(new Chat(connection));
}

void Chat::joinRoom(const std::string &name) {
    model::Room room;
    room.setName(name);
    connection_->request(model::Event::make(room));
}
}  // namespace networking