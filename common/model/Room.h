#pragma once
#include "Serialization.h"

#include <string>

namespace model {
class Room {
  public:
    Room() = default;

    [[nodiscard]] const std::string &name() const;
    void setName(const std::string &name);

    [[nodiscard]] bool isValid() const;

    bool operator==(const Room &other) const;

  private:
    std::string name_;
    static bool isNameValid(const std::string &name);
};
}  // namespace model

namespace serialization {
template<>
[[nodiscard]] nlohmann::json toJson<model::Room>(const model::Room &obj);

template<>
[[nodiscard]] model::Room fromJson<model::Room>(const nlohmann::json &json);
}  // namespace serialization