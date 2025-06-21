Simple RPC application example
==============================

The [RPC Application example](../examples/rpc_application/) shows how to adapt to Remo an existing RPC application like the following:

~~~c++
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
~~~

Note that:

1. It might have simple RPC methods that return primitive types.
2. It might also have methods that use custom data types.
3. It might have methods that throw exceptions.

The three cases are supported by Remo.

Custom types are handled with the addition of JSON converters:

~~~c++
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
~~~

And exceptions are handled internally and returned as a JSON RPC error.

So, binding existing RPC methods to Remo is quite straightforward:

~~~c++
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
~~~

The server runs in a separate thread, and can be started and stopped at any time:

~~~c++
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
~~~