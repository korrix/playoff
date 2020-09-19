#include "User.h"

#include <algorithm>
#include <stdexcept>

namespace model {
const std::string &User::name() const {
    return name_;
}

void User::setName(const std::string &name) {
    if(isNameValid(name)) {
        name_ = name;
    } else {
        throw std::runtime_error("Invalid name. Name must be nonempty and alphanumeric only");
    }
}

bool User::isNameValid(const std::string &name) {
    return !name.empty() && std::all_of(name.begin(), name.end(), [](auto ch) { return std::isalnum(ch); });
}

bool User::isValid() const {
    return isNameValid(name_);
}

bool User::operator==(const User &other) const {
    return name_ == other.name();
}

bool User::operator!=(const User &other) const {
    return !(*this == other);
}
}  // namespace model

namespace serialization {
template<>
nlohmann::json toJson<model::User>(const model::User &user) {
    nlohmann::json out;
    out["name"] = user.name();
    return out;
}

template<>
model::User fromJson<model::User>(const nlohmann::json &json) {
    model::User user;
    user.setName(json["name"]);
    return user;
}
}