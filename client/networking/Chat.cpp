#include "Chat.h"

#include "model/Event.h"
#include "networking/Connection.h"

namespace networking {
std::unique_ptr<Chat> Chat::init(std::shared_ptr<Connection> connection, const std::string &username) {
    model::User user;
    user.setName(username);
    auto response = connection->request(model::Event::make(user));
    return std::unique_ptr<Chat>(new Chat(connection, user));
}

void Chat::joinRoom(const std::string &name) {
    model::Room room;
    room.setName(name);
    connection_->request(model::Event::make(room));
}

void Chat::inviteUser(const std::string &roomName, const std::string &invitedUserName) {
    model::User invited;
    invited.setName(invitedUserName);

    model::Room room;
    room.setName(roomName);

    model::Invitation invitation;
    invitation.setSender(current_);
    invitation.setInvited(invited);
    invitation.setRoom(room);
    invitation.setText("You've just got invited!");

    connection_->request(model::Event::make(invitation));
}

void Chat::message(const std::string &roomName, const std::string &messageText) {
    model::Room room;
    room.setName(roomName);

    model::Message message;
    message.setSender(current_);
    message.setRoom(room);
    message.setText(messageText);

    connection_->request(model::Event::make(message));
}

model::Update Chat::requestUpdate() {
    model::UpdateRequest updateRequest;

    auto response = connection_->request(model::Event::make(updateRequest));
    return response.visit([](auto, auto &update) -> model::Update {
        if constexpr(std::is_same_v<std::decay_t<decltype(update)>, model::Update>) {
            return update;
        } else {
            throw std::runtime_error("Got invalid update response from server");
        }
    });
}

}  // namespace networking