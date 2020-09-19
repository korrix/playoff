#include "Event.h"

namespace model {
Event model::Event::make(const model::User &user) {
    model::Event ev;
    ev.type_ = model::Event::Type::REGISTER_USER;
    ev.payload_ = user;
    return ev;
}

Event model::Event::make(const model::Invitation &invitation) {
    model::Event ev;
    ev.type_ = model::Event::Type::INVITE_USER;
    ev.payload_ = invitation;
    return ev;
}

Event model::Event::make(const model::Message &message) {
    model::Event ev;
    ev.type_ = model::Event::Type::MESSAGE;
    ev.payload_ = message;
    return ev;
}

Event model::Event::make(const model::Room &room) {
    model::Event ev;
    ev.type_ = model::Event::Type::CREATE_ROOM;
    ev.payload_ = room;
    return ev;
}

Event model::Event::make(const std::runtime_error &error) {
    model::Event ev;
    ev.type_ = model::Event::Type::EV_ERROR;
    ev.payload_ = error;
    return ev;
}

const Event::Type &Event::type() const {
    return type_;
}
}  // namespace model

namespace serialization {

template<>
nlohmann::json toJson<std::runtime_error>(const std::runtime_error &error) {
    nlohmann::json out;
    out["error"] = error.what();
    return out;
}

template<>
std::runtime_error fromJson<std::runtime_error>(const nlohmann::json &json) {
    return std::runtime_error(json["error"]);
}

template<>
nlohmann::json toJson<std::monostate>(const std::monostate&) {
   return {};
}

template<>
std::monostate fromJson<std::monostate>(const nlohmann::json &json) {
    return {};
}

template<>
nlohmann::json toJson<model::Event>(const model::Event &event) {
    return event.visit([](auto &type, const auto &payload) {
        nlohmann::json json;
        auto &jt = json["type"];
        switch(type) {
            case model::Event::Type::REGISTER_USER:
                jt = "register_user";
                break;
            case model::Event::Type::INVITE_USER:
                jt = "invite_user";
                break;
            case model::Event::Type::MESSAGE:
                jt = "message";
                break;
            case model::Event::Type::CREATE_ROOM:
                jt = "create_room";
                break;
            case model::Event::Type::EV_ERROR:
                jt = "error";
            default:
                break;
        }

        json["payload"] = toJson(payload);
        return json;
    });
}

template<>
model::Event fromJson<model::Event>(const nlohmann::json &json) {
    model::Event event;

    const auto &jt = json["type"];
    const auto &jp = json["payload"];

    if(jt == "register_user") {
        event.type_    = model::Event::Type::REGISTER_USER;
        event.payload_ = fromJson<model::User>(jp);
    } else if(jt == "invite_user") {
        event.type_    = model::Event::Type::INVITE_USER;
        event.payload_ = fromJson<model::Invitation>(jp);
    } else if(jt == "message") {
        event.type_    = model::Event::Type::MESSAGE;
        event.payload_ = fromJson<model::Message>(jp);
    } else if(jt == "create_room") {
        event.type_    = model::Event::Type::CREATE_ROOM;
        event.payload_ = fromJson<model::Room>(jp);
    } else if(jt == "error") {
        event.type_ = model::Event::Type::EV_ERROR;
        event.payload_ = fromJson<std::runtime_error>(jp);
    }

    return event;
}
}  // namespace serialization