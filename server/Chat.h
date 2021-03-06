#pragma once

#include "model/Event.h"
#include "model/Update.h"

#include <mutex>
#include <unordered_map>

namespace server {
class Chat {
  public:
    Chat() = default;

    using session = const void *;

    model::Event handleEvent(session id, const model::Event &ev);
    void cleanup(session id);

  private:
    std::mutex mutex_;

    model::Event handle(session id, const model::User &ev);
    model::Event handle(session id, const model::Room &ev);
    model::Event handle(session id, const model::Invitation &ev);
    model::Event handle(session id, const model::Message &ev);
    model::Event handle(session id, const model::Update &ev);
    model::Event handle(session id, const model::UpdateRequest &ev);
    model::Event handle(session id, const std::runtime_error &ev);
    model::Event handle(session id, std::monostate);

    std::unordered_map<session, std::string> sessionNicknameAssociations;
    std::unordered_map<std::string, session> nicknameSessionAssociations;

    std::unordered_map<std::string, std::vector<session>> rooms;
    std::unordered_map<session, model::Update> updates;
};
}  // namespace server