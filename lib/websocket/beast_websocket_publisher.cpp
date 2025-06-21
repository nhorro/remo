#include "beast_websocket_publisher.hpp"
#include <boost/beast.hpp>

using json = nlohmann::json;
namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

// WebSocketSession definition
class BeastWebSocketPublisher::WebSocketSession : public std::enable_shared_from_this<WebSocketSession> {
public:
    WebSocketSession(tcp::socket socket,
                     std::set<std::shared_ptr<websocket::stream<tcp::socket>>>& clients,
                     std::mutex& mutex)
        : ws_(std::make_shared<websocket::stream<tcp::socket>>(std::move(socket))),
          clients_(clients), mutex_(mutex) {}

    void start() {
        ws_->accept();
        std::lock_guard<std::mutex> lock(mutex_);
        clients_.insert(ws_);
    }

private:
    std::shared_ptr<websocket::stream<tcp::socket>> ws_;
    std::set<std::shared_ptr<websocket::stream<tcp::socket>>>& clients_;
    std::mutex& mutex_;
};

// Publisher implementation

BeastWebSocketPublisher::BeastWebSocketPublisher(uint16_t port)
    : ioc_(std::make_shared<net::io_context>()),
      acceptor_(*ioc_, tcp::endpoint(tcp::v4(), port)) {}

void BeastWebSocketPublisher::start() {
    accept_connections();
    io_thread_ = std::thread([this] { ioc_->run(); });
}

void BeastWebSocketPublisher::stop() {
    ioc_->stop();
    if (io_thread_.joinable())
        io_thread_.join();
}

void BeastWebSocketPublisher::publish(const json& j) {
    std::string msg = j.dump();
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto& ws : clients_) {
        if (ws->is_open()) {
            ws->text(true);
            ws->async_write(net::buffer(msg), [](beast::error_code, std::size_t) {});
        }
    }
}

void BeastWebSocketPublisher::accept_connections() {
    auto socket = std::make_shared<tcp::socket>(*ioc_);
    acceptor_.async_accept(*socket, [this, socket](beast::error_code ec) {
        if (!ec) {
            auto session = std::make_shared<WebSocketSession>(std::move(*socket), clients_, mutex_);
            session->start();
        }
        accept_connections();
    });
}
