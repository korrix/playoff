#include "Room.h"

#include <stdexcept>

namespace model {
const std::string &Room::name() const {
    return name_;
}

void Room::setName(const std::string &name) {
    if(isNameValid(name)) {
        name_ = name;
    } else {
        throw std::runtime_error("Invalid name: Name cannot be empty.");
    }
}

bool Room::isNameValid(const std::string &name) {
    return !name.empty();
}

bool Room::isValid() const {
    return isNameValid(name_);
}

bool Room::operator==(const Room &other) const {
    return name_ == other.name();
}
}  // namespace model