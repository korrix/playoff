#include "Update.h"

namespace model {
void Update::addMessage(const Message &message) {
    if(message.isValid()) {
        messages_.push_back(message);
    } else {
        throw std::runtime_error("Unable to add invalid message");
    }
}

void Update::addInvitation(const Invitation &invitation) {
    if(invitation.isValid()) {
        invitations_.push_back(invitation);
    } else {
        throw std::runtime_error("Unable to add invalid invitation");
    }
}

const std::vector<Message> &Update::messages() const {
    return messages_;
}

const std::vector<Invitation> &Update::invitations() const {
    return invitations_;
}
}

namespace serialization {
template<>
[[nodiscard]] nlohmann::json toJson<model::Update>(const model::Update &obj) {
    nlohmann::json json;
    auto &messages = json["messages"];
    for(auto &message : obj.messages()) {
        messages.push_back(toJson(message));
    }
    auto &invitations = json["invitations"];
    for(auto &invitation : obj.invitations()) {
        invitations.push_back(toJson(invitation));
    }
    return json;
}

template<>
[[nodiscard]] model::Update fromJson<model::Update>(const nlohmann::json &json) {
    model::Update update;
    for(auto &message : json["messages"]) {
        update.addMessage(fromJson<model::Message>(message));
    }
    for(auto &invitation : json["invitations"]) {
        update.addInvitation(fromJson<model::Invitation>(invitation));
    }
    return update;
}
}  // namespace serialization