#include "Event.h"

namespace model {
const Event::Type &Event::type() const {
    return type_;
}
}  // namespace model

namespace serialization {
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
            case model::Event::Type::ERROR:
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
    } else if(jt == "exception") {
        event.type_ = model::Event::Type::ERROR;
        event.payload_ = fromJson<std::runtime_error>(jp);
    }

    return event;
}
}  // namespace serialization