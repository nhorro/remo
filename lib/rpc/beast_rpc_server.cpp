#include "beast_rpc_server.hpp"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <nlohmann/json.hpp>
#include <iostream>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
using tcp = asio::ip::tcp;
using json = nlohmann::json;

BeastRPCServer::BeastRPCServer(unsigned short port)
    : port_(port) {}

BeastRPCServer::~BeastRPCServer() {
    stop();
}

void BeastRPCServer::start() {
    server_thread_ = std::thread(&BeastRPCServer::run, this);
}

void BeastRPCServer::stop() {
    stop_flag_ = true;
    
    if (acceptor_) acceptor_->close();      // 🔧 interrumpe el accept
    if (ioc_) ioc_->stop();                 // 🔧 interrumpe run()

    if (server_thread_.joinable())
        server_thread_.join();
}

void BeastRPCServer::run() {
    try {
        ioc_.emplace();
        acceptor_.emplace(*ioc_, tcp::endpoint(tcp::v4(), port_));

        do_accept();  // <- función que inicia el ciclo async

        ioc_->run();  // <- bloqueante, termina cuando hacemos stop()
    } catch (const std::exception& e) {
        std::cerr << "[RPCServer] Exception: " << e.what() << "\n";
    }
}

void BeastRPCServer::do_accept() {
    acceptor_->async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec && !stop_flag_) {
            handle_connection(std::move(socket));
        }
        if (!stop_flag_) {
            do_accept();  // <- continuar aceptando conexiones
        }
    });
}


void BeastRPCServer::handle_connection(boost::asio::ip::tcp::socket socket) {
    try {
        beast::flat_buffer buffer;
        http::request<http::string_body> req;
        http::read(socket, buffer, req);

        http::response<http::string_body> res;
        res.version(req.version());
        res.keep_alive(false);
        res.set(http::field::content_type, "application/json");
        res.set(http::field::access_control_allow_origin, "*");

        if (req.method() == http::verb::options) {
            http::response<http::string_body> res{http::status::no_content, req.version()};
            res.set(http::field::access_control_allow_origin, "*");
            res.set(http::field::access_control_allow_methods, "POST, GET, OPTIONS");
            res.set(http::field::access_control_allow_headers, "Content-Type");
            res.prepare_payload();
            http::write(socket, res);
            return;
        }
        
        if (req.method() == http::verb::post && req.target() == "/rpc") {
            auto body = json::parse(req.body(), nullptr, false);
            json reply;

            if (!body.is_discarded() && body.contains("method") && handlers_.count(body["method"])) {
                try {
                    auto method = body["method"];
                    auto params = body["params"];
                    auto result = handlers_.at(method)(params);
            
                    reply = {
                        {"jsonrpc", "2.0"},
                        {"result", result},
                        {"id", body["id"]}
                    };
                } catch (const std::exception& ex) {
                    reply = {
                        {"jsonrpc", "2.0"},
                        {"error", {
                            {"code", -32001},
                            {"message", "Application error"},
                            {"data", ex.what()}
                        }},
                        {"id", body.value("id", json(nullptr))}  
                    };
                } catch (...) {
                    reply = {
                        {"jsonrpc", "2.0"},
                        {"error", {
                            {"code", -32002},
                            {"message", "Unknown server error"}
                        }},
                        {"id", body.value("id", json(nullptr))}  
                    };
                }
            }

            res.result(http::status::ok);
            res.body() = reply.dump();
            res.prepare_payload();
        } else {
            res.result(http::status::not_found);
            res.body() = "Not Found";
            res.prepare_payload();
        }

        http::write(socket, res);
    } catch (const std::exception& e) {
        std::cerr << "[RPCServer] Connection error: " << e.what() << "\n";
    }
}

void BeastRPCServer::register_method(const std::string& name, std::function<json(const json&)> fn) {
    handlers_[name] = std::move(fn);
}