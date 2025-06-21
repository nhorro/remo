#pragma once
#include "rpc_application.hpp"
#include <nlohmann/json.hpp>

inline void to_json(nlohmann::json& j, const RPCApplication::CompositeResult::Point& p) {
    j = nlohmann::json{
        {"x", p.x},
        {"y", p.y},
        {"z", p.z}
    };
}

inline void to_json(nlohmann::json& j, const RPCApplication::CompositeResult& r) {
    j = nlohmann::json{
        {"points", r.points}
    };
}
