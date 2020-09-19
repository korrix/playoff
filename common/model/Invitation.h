#pragma once

#include "Message.h"
#include "Serialization.h"

#include <string>

namespace model {
class Invitation;
}

namespace serialization {
template<>
[[nodiscard]] nlohmann::json toJson<model::Invitation>(const model::Invitation &obj);

template<>
[[nodiscard]] model::Invitation fromJson<model::Invitation>(const nlohmann::json &json);
}  // namespace serialization

namespace model {
class Invitation : public Message {
  public:
    Invitation() = default;

    void setSender(const User &sender) final;

    void setInvited(const User &invited);
    [[nodiscard]] const User &invited() const;

    [[nodiscard]] bool isValid() const final;

    bool operator==(const Invitation& other) const;
  private:
    Invitation(const Message &other)
        : Message(other) {
    }

    friend Invitation serialization::fromJson<Invitation>(const nlohmann::json &json);

    User invited_;
};
}  // namespace model