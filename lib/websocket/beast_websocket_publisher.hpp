#pragma once

#include <nlohmann/json.hpp>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <thread>
#include <mutex>
#include <set>
#include <memory>

class BeastWebSocketPublisher {
public:
    explicit BeastWebSocketPublisher(uint16_t port);
    void start();
    void stop();

    void publish(const nlohmann::json& j);

private:
    class WebSocketSession;
    void accept_connections();

    std::shared_ptr<boost::asio::io_context> ioc_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::thread io_thread_;

    std::set<std::shared_ptr<boost::beast::websocket::stream<boost::asio::ip::tcp::socket>>> clients_;
    std::mutex mutex_;
};
