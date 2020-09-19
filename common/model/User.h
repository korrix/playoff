#pragma once

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