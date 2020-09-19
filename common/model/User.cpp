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
}  // namespace model