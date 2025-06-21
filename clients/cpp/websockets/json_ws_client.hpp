#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <functional>
#include <thread>
#include <atomic>

class JsonWebSocketClient {
public:
    JsonWebSocketClient(const std::string& host, const std::string& port);
    ~JsonWebSocketClient();

    void start(std::function<void(const nlohmann::json&)> on_message);
    void stop();

private:
    void run(std::function<void(const nlohmann::json&)> on_message);
    void reconnect_loop(std::function<void(const nlohmann::json&)> on_message);

    std::string host_, port_;
    std::atomic_bool running_;
    std::thread client_thread_;
};

