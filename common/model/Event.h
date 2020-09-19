#pragma once

#include "Invitation.h"
#include "Message.h"
#include "Room.h"
#include "User.h"

#include <variant>

namespace model {
class Event;
}

namespace serialization {
template<>
[[nodiscard]] nlohmann::json toJson<model::Event>(const model::Event &obj);

template<>
[[nodiscard]] model::Event fromJson<model::Event>(const nlohmann::json &json);
}  // namespace serialization

namespace model {
class Event {
  public:
    Event() = default;
    enum class Type { INVALID_EVENT, REGISTER_USER, INVITE_USER, MESSAGE, CREATE_ROOM, EV_ERROR };

    [[nodiscard]] const Type &type() const;

    template<typename F>
    constexpr auto visit(F &&visitor) const {
        return std::visit([visitor, this](auto &&payload) { return visitor(type_, payload); }, payload_);
    }

    static Event make(const User &user);
    static Event make(const Invitation &invitation);
    static Event make(const Message &message);
    static Event make(const Room &message);
    static Event make(const std::runtime_error &error);

  private:

    friend model::Event serialization::fromJson<model::Event>(const nlohmann::json &json);

    Type type_ = Type::INVALID_EVENT;
    std::variant<std::monostate, User, Invitation, Message, Room, std::runtime_error> payload_;
};
}  // namespace model