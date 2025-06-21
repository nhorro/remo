#pragma once
#include <nlohmann/json.hpp>
#include <string>

class JsonRpcClient {
public:
    JsonRpcClient(const std::string& host, const std::string& port);
    nlohmann::json call(const std::string& method, const nlohmann::json& params);
private:
    std::string host_;
    std::string port_;
};
