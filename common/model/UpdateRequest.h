#pragma once
#include "Serialization.h"

namespace model {
struct UpdateRequest {};
}  // namespace model

namespace serialization {
template<>
[[nodiscard]] nlohmann::json toJson<model::UpdateRequest>(const model::UpdateRequest &obj);

template<>
[[nodiscard]] model::UpdateRequest fromJson<model::UpdateRequest>(const nlohmann::json &json);
}  // namespace serialization