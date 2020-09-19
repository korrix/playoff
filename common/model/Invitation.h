#pragma once

#include <string>

#include "Message.h"

namespace model {
class Invitation : public Message {
  public:
    Invitation() = default;

    void setSender(const User& sender) final;

    void setInvited(const User& invited);
    [[nodiscard]] const User& invited() const;

    bool isValid() const final;

  private:
    User invited_;
};
}