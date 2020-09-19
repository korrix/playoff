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

void Chat::inviteUser(const std::string &currentUserName, const std::string &roomName, const std::string &invitedUserName) {
    model::User current, invited;
    current.setName(currentUserName);
    invited.setName(invitedUserName);

    model::Room room;
    room.setName(roomName);

    model::Invitation invitation;
    invitation.setSender(current);
    invitation.setInvited(invited);
    invitation.setRoom(room);
    invitation.setText("You've just got invited!");

    connection_->request(model::Event::make(invitation));
}

}  // namespace networking