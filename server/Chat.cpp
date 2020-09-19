#include "Chat.h"

#include <spdlog/spdlog.h>

namespace server {
model::Event Chat::handleEvent(const model::Event &ev) {
    return ev.visit([this](auto, auto &payload) { return handle(payload); });
}

model::Event Chat::handle(const model::User &ev) {
    spdlog::info("Registration for user \"{}\" requested", ev.name());
    return model::Event();
}

model::Event Chat::handle(const model::Room &ev) {
    spdlog::info("Registration for room \"{}\" requested", ev.name());
    return model::Event();
}

model::Event Chat::handle(const model::Invitation &ev) {
    spdlog::info("Invitation of \"{}\" to room \"{}\" requested by \"{}\"", ev.invited().name(), ev.room().name(),
                 ev.sender().name());
    return model::Event();
}

model::Event Chat::handle(const model::Message &ev) {
    spdlog::info("Message from \"{}\" to room \"{}\"", ev.sender().name(), ev.room().name());
    return model::Event();
}

model::Event Chat::handle(const std::runtime_error &ev) {
    spdlog::error("Some error occurred: ", ev.what());
    return model::Event();
}

model::Event Chat::handle(std::monostate) {
    spdlog::error("Invalid message, this should not happen");
    return model::Event();
}

}  // namespace server