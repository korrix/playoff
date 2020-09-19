#pragma once

#include <nlohmann/json.hpp>

namespace serialization {
    template<typename T>
    nlohmann::json toJson(const T& object);

    template<typename T>
    T fromJson(const nlohmann::json& json);
}