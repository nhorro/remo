#include "rpc_application.hpp"
#include "rpc_json_adapters.hpp"  // activa serialización JSON
#include "beast_rpc_server.hpp"
#include <iostream>
#include <nlohmann/json.hpp>


int main() {
    RPCApplication app;
    BeastRPCServer server(8080);


    server.register_method("hello", [&app](const nlohmann::json& params) {
        return app.hello(params.at(0));
    });

    server.register_method("hello", [&app](const nlohmann::json& params) {
        return app.hello(params.at(0));
    });

    server.register_method("get_points", [&app](const nlohmann::json& params) {
        return app.get_points();  // Se convierte automáticamente a json
    });

    server.register_method("fail", [&app](const nlohmann::json& params) {
        float x = params.at(0).get<float>();
        return app.this_method_always_fails(x);  // lanza excepción
    });


    server.start();
    std::cout << "RPC Server running on port 8080.\n";
    std::cout << "Press Enter to exit...\n";
    std::getchar();

    std::cout << "Stopping...\n";
    server.stop();

    std::cout << "Shutdown complete.\n";
    return 0;
}
