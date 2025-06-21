# RPC Application Example

The [RPC Application example](../examples/rpc_application/) shows how to expose methods from an existing C++ application using **Remo** and the JSON-RPC 2.0 protocol.

---

## 🧩 The Base Application

Suppose we have an application like this:

```cpp
class RPCApplication {
public:
    // 1. Simple method with primitive return type
    std::string hello(const std::string& name) {
        return "Hello " + name + ", how are you today?";
    }

    // 2. Composite return type
    struct CompositeResult {
        struct Point {
            float x, y, z;
        };
        std::vector<Point> points;
    };

    CompositeResult get_points() {
        return {
            {
                {0.1f, 0.2f, 0.3f},
                {0.4f, 0.5f, 0.6f}
            }
        };
    }

    // 3. Method that fails intentionally
    float this_method_always_fails(float x) {
        throw std::runtime_error("Computation failed: something went wrong.");
    }
};
````

Remo supports:

* ✅ Primitive return types
* ✅ Composite custom types (with `to_json` converters)
* ✅ Exception handling (mapped to JSON-RPC errors)

---

## 🔁 Serializing Custom Types

Custom return types must be converted to JSON:

```cpp
inline void to_json(nlohmann::json& j, const RPCApplication::CompositeResult::Point& p) {
    j = { {"x", p.x}, {"y", p.y}, {"z", p.z} };
}

inline void to_json(nlohmann::json& j, const RPCApplication::CompositeResult& r) {
    j = { {"points", r.points} };
}
```

---

## 🔌 Binding Methods

We bind methods to the RPC server using lambda expressions:

```cpp
void bind_methods(BeastRPCServer& server, RPCApplication& app) {
    server.register_method("hello", [&app](const json& params) {
        return app.hello(params.at(0));
    });

    server.register_method("get_points", [&app](const json&) {
        return app.get_points();
    });

    server.register_method("fail", [&app](const json& params) {
        float x = params.at(0).get<float>();
        return app.this_method_always_fails(x);
    });
}
```

---

## 🚀 Running the Server

```cpp
constexpr int RPC_PORT = 8080;

int main() {
    RPCApplication app;
    BeastRPCServer server(RPC_PORT);

    bind_methods(server, app);

    server.start();
    std::cout << "RPC Server running on port " << RPC_PORT << "\n";
    std::cout << "Press Enter to exit...\n";
    std::getchar();

    std::cout << "Stopping...\n";
    server.stop();
    return 0;
}
```

---

## 🔍 Quick Test with `curl`

```bash
# Test string return
curl -X POST http://localhost:8080/rpc \
     -H 'Content-Type: application/json' \
     -d '{"jsonrpc":"2.0", "method":"hello", "params":["bob"], "id":1}'

# Test composite object
curl -X POST http://localhost:8080/rpc \
     -H 'Content-Type: application/json' \
     -d '{"jsonrpc":"2.0", "method":"get_points", "params":[], "id":2}'

# Test failure case
curl -X POST http://localhost:8080/rpc \
     -H 'Content-Type: application/json' \
     -d '{"jsonrpc":"2.0", "method":"fail", "params":[3.14], "id":3}'
```

---

## ✅ Summary

Remo allows you to:

* Wrap existing C++ logic without modifying internal application code
* Return complex types with minimal boilerplate
* Handle exceptions automatically via structured JSON-RPC errors