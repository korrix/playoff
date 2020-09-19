#pragma once

#include "model/Event.h"

namespace server {
class Chat {
  public:
    Chat() = default;

    model::Event handleEvent(const model::Event& ev);

  private:
    model::Event handle(const model::User& ev);
    model::Event handle(const model::Room& ev);
    model::Event handle(const model::Invitation& ev);
    model::Event handle(const model::Message& ev);
    model::Event handle(const std::runtime_error& ev);
    model::Event handle(std::monostate);
};
}