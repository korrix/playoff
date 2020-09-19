#pragma once

#include "Serialization.h"

#include <string>

namespace model {
class User {
  public:
    User() = default;

    [[nodiscard]] const std::string &name() const;
    void setName(const std::string &name);

    [[nodiscard]] bool isValid() const;
    bool operator==(const User& other) const;
    bool operator!=(const User& other) const;

  private:
    std::string name_;
    static bool isNameValid(const std::string& name);
};
}  // namespace model

namespace serialization {
template<>
[[nodiscard]] nlohmann::json toJson<model::User>(const model::User& obj);

template<>
[[nodiscard]] model::User fromJson<model::User>(const nlohmann::json& json);
}