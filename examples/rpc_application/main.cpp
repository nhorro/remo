/**
 * @file main.cpp
 * @author Nicolás Horro (nhorro@gmail.com)
 * @brief Example of how to adapt an existing RPC application to Remo RPC  
 */

#include "beast_rpc_server.hpp"
#include <iostream>
#include <nlohmann/json.hpp>

/**
 * @brief Example of a protocol-independent remote controlled application
 * 
 */
class RPCApplication {
public:
    
    // 1. A simple method that returns a primitive type
    std::string hello(const std::string& name) {
        return "Hello " + name + ", how are you today?";
    }

    // 2. A method that returns a custom composite object. 
    struct CompositeResult {
        struct Point {
            float x;
            float y;
            float z;
        };
        std::vector<Point> points;
    };

    CompositeResult get_points() {
        return CompositeResult{{
            { 0.1f, 0.2f, 0.3f},
            { 0.4f, 0.5f, 0.6f}
        }};
    };

    // 3. A method that intentionally fails
    float this_method_always_fails(float x) {
        throw std::runtime_error("Computation failed: something went wrong.");
    }
};


// JSON converters are required for custom types


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


void bind_methods(BeastRPCServer& server, RPCApplication& app) {

    server.register_method("hello", [&app](const nlohmann::json& params) {
        return app.hello(params.at(0));
    });

    server.register_method("hello", [&app](const nlohmann::json& params) {
        return app.hello(params.at(0));
    });

    server.register_method("get_points", [&app](const nlohmann::json& params) {
        return app.get_points();  // Automatically converted
    });

    server.register_method("fail", [&app](const nlohmann::json& params) {
        float x = params.at(0).get<float>();
        return app.this_method_always_fails(x);  // Throws exception
    });
}


constexpr int RPC_PORT = 8080;

int main() {
    RPCApplication app;
    BeastRPCServer server(RPC_PORT);

    bind_methods(server,app);

    server.start();
    std::cout << "RPC Server running on port " << RPC_PORT << "\n";
    std::cout << "Press Enter to exit...\n";
    std::getchar();

    std::cout << "Stopping...\n";
    server.stop();

    std::cout << "Gracefully returning to system.\n";
    return 0;
}
