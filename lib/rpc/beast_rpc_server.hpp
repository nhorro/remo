#pragma once

#include <thread>
#include <atomic>
#include <unordered_map>
#include <optional>
#include <nlohmann/json.hpp>
#include <boost/asio.hpp>       // ← necesario para io_context y tcp


class BeastRPCServer {
public:
    BeastRPCServer(unsigned short port = 8080);
    ~BeastRPCServer();

    void start();
    void stop();

    void register_method(const std::string& name, std::function<nlohmann::json(const nlohmann::json&)> fn);

private:
    void run();

    unsigned short port_;
    std::thread server_thread_;

    std::optional<boost::asio::io_context> ioc_;
    std::optional<boost::asio::ip::tcp::acceptor> acceptor_;
    std::atomic<bool> stop_flag_{false};

    std::unordered_map<std::string, std::function<nlohmann::json(const nlohmann::json&)>> handlers_;

    void do_accept();
    void handle_connection(boost::asio::ip::tcp::socket  socket);
};
