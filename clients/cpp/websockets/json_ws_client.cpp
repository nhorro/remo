#include "json_ws_client.hpp"
#include <boost/beast.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <iostream>

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;
using json = nlohmann::json;

JsonWebSocketClient::JsonWebSocketClient(const std::string& host, const std::string& port)
    : host_(host), port_(port), running_(false) {}

JsonWebSocketClient::~JsonWebSocketClient() {
    stop();
}

void JsonWebSocketClient::start(std::function<void(const json&)> on_message) {
    if (running_) return;
    running_ = true;
    client_thread_ = std::thread([=]() {
        reconnect_loop(on_message);
    });
}

void JsonWebSocketClient::stop() {
    running_ = false;
    if (client_thread_.joinable())
        client_thread_.join();
}

void JsonWebSocketClient::reconnect_loop(std::function<void(const json&)> on_message) {
    while (running_) {
        try {
            run(on_message);
        } catch (const std::exception& e) {
            std::cerr << "[RemoWSClient] Error: " << e.what() << "\n";
        }

        if (running_) {
            std::cerr << "[RemoWSClient] Reconnecting in 2s...\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
}

void JsonWebSocketClient::run(std::function<void(const json&)> on_message) {
    boost::asio::io_context ioc;
    tcp::resolver resolver(ioc);
    auto results = resolver.resolve(host_, port_);

    websocket::stream<tcp::socket> ws(ioc);
    boost::asio::connect(ws.next_layer(), results.begin(), results.end());
    ws.handshake(host_, "/");

    std::cerr << "[RemoWSClient] Connected to " << host_ << ":" << port_ << "\n";

    while (running_) {
        boost::beast::flat_buffer buffer;
        ws.read(buffer);

        std::string message = boost::beast::buffers_to_string(buffer.data());
        try {
            json j = json::parse(message);
            on_message(j);
        } catch (...) {
            std::cerr << "[RemoWSClient] Invalid JSON received\n";
        }
    }

    ws.close(websocket::close_code::normal);
}
