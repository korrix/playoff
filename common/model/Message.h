#pragma once

#include "Room.h"
#include "Serialization.h"
#include "User.h"

namespace model {
class Message {
  public:
    Message()          = default;
    virtual ~Message() = default;

    virtual void setSender(const User &sender);
    [[nodiscard]] const User &sender() const;

    void setRoom(const Room &room);
    [[nodiscard]] const Room &room() const;

    void setText(const std::string &text);
    [[nodiscard]] const std::string &text() const;

    [[nodiscard]] virtual bool isValid() const;

    bool operator==(const Message& other) const;

  private:
    User sender_;
    Room room_;
    std::string text_;

    static bool isTextValid(const std::string &text);
};
}  // namespace model

namespace serialization {
template<>
[[nodiscard]] nlohmann::json toJson<model::Message>(const model::Message &obj);

template<>
[[nodiscard]] model::Message fromJson<model::Message>(const nlohmann::json &json);
}  // namespace serialization