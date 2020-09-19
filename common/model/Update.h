#pragma once

#include "Message.h"
#include "Invitation.h"

namespace model {
class Update {
  public:
    Update() = default;

    void addMessage(const Message& message);

    void addInvitation(const Invitation& invitation);

    [[nodiscard]] const std::vector<Message>& messages() const;
    [[nodiscard]] const std::vector<Invitation>& invitations() const;

  private:
    std::vector<Message> messages_;
    std::vector<Invitation> invitations_;
};
}

namespace serialization {
template<>
[[nodiscard]] nlohmann::json toJson<model::Update>(const model::Update &obj);

template<>
[[nodiscard]] model::Update fromJson<model::Update>(const nlohmann::json &json);
}  // namespace serialization