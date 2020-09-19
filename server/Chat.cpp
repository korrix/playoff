#include "Chat.h"

#include <spdlog/spdlog.h>

namespace server {
model::Event Chat::handleEvent(session id, const model::Event &ev) {
    return ev.visit([this, id](auto, auto &payload) {
        std::lock_guard<std::mutex> lock(mutex_);
        return handle(id, payload);
    });
}

model::Event Chat::handle(session id, const model::User &ev) {
    spdlog::info("Registration for user \"{}\" requested (sesionid: {})", ev.name(), (size_t)id);

    auto it = nicknameSessionAssociations.find(ev.name());
    if(it != nicknameSessionAssociations.end()) {
        if(it->second == id) {
            spdlog::info("User \"{}\" already registered for same session", ev.name());
        } else {
            spdlog::error("Username \"{}\" is in use", ev.name());
            throw std::runtime_error("Please choose different username!");
        }
    } else {
        spdlog::info("User \"{}\" not registered. Performing registration", ev.name());
        sessionNicknameAssociations[id] = ev.name();
        nicknameSessionAssociations[ev.name()] = id;
    }

    return model::Event();
}

model::Event Chat::handle(session id, const model::Room &ev) {
    spdlog::info("Registration for room \"{}\" requested", ev.name());

    auto it = rooms.find(ev.name());
    if(it != rooms.end()) {
        spdlog::info("Creating new room \"{}\"", ev.name());
        rooms.emplace(ev.name(), std::vector{id});
    } else {
        spdlog::info("Joining to existing room \"{}\"", ev.name());
        it->second.push_back(id);
    }

    return model::Event();
}

model::Event Chat::handle(session id, const model::Invitation &ev) {
    spdlog::info("Invitation of \"{}\" to room \"{}\" requested by \"{}\"", ev.invited().name(), ev.room().name(),
                 ev.sender().name());

    auto roomIt = rooms.find(ev.room().name());
    if(roomIt != rooms.end()) {
        auto userIt = nicknameSessionAssociations.find(ev.invited().name());
        if(userIt != nicknameSessionAssociations.end()) {
            roomIt->second.push_back(userIt->second);
            // TODO Direct message to invited user
        } else {
            throw std::runtime_error("Unable to invite non-existing user");
        }

    } else {
        throw std::runtime_error("Unable to invite user to non-existing room");
    }

    return model::Event();
}

model::Event Chat::handle(session id, const model::Message &ev) {
    spdlog::info("Message from \"{}\" to room \"{}\"", ev.sender().name(), ev.room().name());
    return model::Event();
}

model::Event Chat::handle(session id, const std::runtime_error &ev) {
    spdlog::error("Some error occurred: ", ev.what());
    return model::Event();
}

model::Event Chat::handle(session id, std::monostate) {
    spdlog::error("Invalid message, this should not happen");
    return model::Event();
}

void Chat::cleanup(Chat::session id) {
    auto it = sessionNicknameAssociations.find(id);
    if(it != sessionNicknameAssociations.end()) {
        nicknameSessionAssociations.erase(it->second);
        sessionNicknameAssociations.erase(id);
    }
}

}  // namespace server