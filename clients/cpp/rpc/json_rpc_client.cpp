#include "json_rpc_client.hpp"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <sstream>

using namespace boost::asio;
namespace http = boost::beast::http;
using tcp = ip::tcp;
using json = nlohmann::json;

JsonRpcClient::JsonRpcClient(const std::string& host, const std::string& port)
    : host_(host), port_(port) {}

json JsonRpcClient::call(const std::string& method, const json& params) {
    io_context ioc;
    tcp::resolver resolver(ioc);
    auto const results = resolver.resolve(host_, port_);
    tcp::socket socket(ioc);
    connect(socket, results.begin(), results.end());

    static int id_counter = 1;
    json request = {
        {"jsonrpc", "2.0"},
        {"method", method},
        {"params", params},
        {"id", id_counter++}
    };

    http::request<http::string_body> req{http::verb::post, "/rpc", 11};
    req.set(http::field::host, host_);
    req.set(http::field::content_type, "application/json");
    req.body() = request.dump();
    req.prepare_payload();

    http::write(socket, req);

    boost::beast::flat_buffer buffer;
    http::response<http::string_body> res;
    http::read(socket, buffer, res);

    if (res.result() != http::status::ok) {
        throw std::runtime_error("HTTP error: " + std::to_string(res.result_int()));
    }

    auto response_json = json::parse(res.body());

    if (response_json.contains("error")) {
        std::stringstream ss;
        ss << "JSON-RPC error: code " << response_json["error"]["code"]
           << ", message: " << response_json["error"]["message"];
        throw std::runtime_error(ss.str());
    }

    return response_json["result"];
}
