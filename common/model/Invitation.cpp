#include "Invitation.h"

namespace model {
void Invitation::setSender(const User &sender) {
    if(sender != invited()) {
        Message::setSender(sender);
    } else {
        throw std::runtime_error("Sender must be different from self");
    }
}

void Invitation::setInvited(const User& invited) {
    if(invited.isValid() && (invited != sender())) {
        invited_ = invited;
    } else {
        throw std::runtime_error("Invited must be valid and different from self");
    }
}

[[nodiscard]] const User& Invitation::invited() const {
    return invited_;
}

bool Invitation::isValid() const {
    return Message::isValid() && invited_.isValid();
}
}