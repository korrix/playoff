#pragma once

#include "Room.h"
#include "User.h"
#include <stdexcept>

namespace model {
class Message {
  public:
    Message() = default;
    virtual ~Message() = default;

    virtual void setSender(const User& sender);
    [[nodiscard]] const User& sender() const;

    void setRoom(const Room& room);
    [[nodiscard]] const Room& room() const;

    void setText(const std::string& text);
    [[nodiscard]] const std::string& text() const;

    [[nodiscard]] virtual bool isValid() const;
  private:
    User sender_;
    Room room_;
    std::string text_;

    static bool isTextValid(const std::string& text);
};
}  // namespace model
