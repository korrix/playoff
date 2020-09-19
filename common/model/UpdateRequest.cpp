#include "UpdateRequest.h"

namespace serialization {
template<>
nlohmann::json toJson<model::UpdateRequest>(const model::UpdateRequest &obj) {
    return {};
}

template<>
model::UpdateRequest fromJson<model::UpdateRequest>(const nlohmann::json &json) {
    return {};
}
}