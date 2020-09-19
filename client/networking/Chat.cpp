#include "Chat.h"

#include "model/Event.h"
#include "networking/Connection.h"

namespace networking {
std::unique_ptr<Chat> Chat::init(std::shared_ptr<Connection> connection, const std::string &username) {
    model::User user;
    user.setName(username);
    auto response = connection->request(model::Event::make(user));
    response.visit([](auto, auto &error) {
        if constexpr(std::is_base_of_v<std::exception, std::decay_t<decltype(error)>>) {
            throw error;
        }
    });

    return std::unique_ptr<Chat>(new Chat(connection));
}
}  // namespace networking