#include "Invitation.h"

namespace model {
void Invitation::setSender(const User &sender) {
    if(sender != invited()) {
        Message::setSender(sender);
    } else {
        throw std::runtime_error("Sender must be different from self");
    }
}

void Invitation::setInvited(const User &invited) {
    if(invited.isValid() && (invited != sender())) {
        invited_ = invited;
    } else {
        throw std::runtime_error("Invited must be valid and different from self");
    }
}

[[nodiscard]] const User &Invitation::invited() const {
    return invited_;
}

bool Invitation::isValid() const {
    return Message::isValid() && invited_.isValid();
}

bool Invitation::operator==(const Invitation &other) const {
    return Message::operator==(other) && (invited_ == other.invited());
}
}  // namespace model

namespace serialization {
template<>
nlohmann::json toJson<model::Invitation>(const model::Invitation &invitation) {
    auto out = toJson<model::Message>(invitation);
    out["invited"] = toJson(invitation.invited());
    return out;
}

template<>
model::Invitation fromJson<model::Invitation>(const nlohmann::json &json) {
    model::Invitation invitation = fromJson<model::Message>(json);
    invitation.setInvited(fromJson<model::User>(json["invited"]));

    return invitation;
}
}