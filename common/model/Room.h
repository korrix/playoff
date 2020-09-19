#pragma once
#include <string>

namespace model {
class Room {
  public:
    Room() = default;

    const std::string &name() const;
    void setName(const std::string &name);

  private:
    std::string name_;
    static bool isNameValid(const std::string& name);
};
}