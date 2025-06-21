# Remo C++ JSON-RPC Client

This is a minimal C++ client for making **JSON-RPC 2.0** calls to a Remo HTTP server.

## ✅ Features

- Simple synchronous API
- Uses `Boost.Beast` and `nlohmann::json`
- Returns `json` response or throws on error

## 🔧 Example usage

```cpp
#include "json_rpc_client.hpp"
#include <iostream>

int main() {
    JsonRpcClient client("localhost", "8080");

    try {
        auto response = client.call("hello", {"Alice"});
        std::cout << "Response: " << response.dump(2) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "RPC Error: " << e.what() << std::endl;
    }

    return 0;
}
````

## 📦 Build

```bash
mkdir build && cd build
cmake ..
make
./json_rpc_client
```

## 📝 Dependencies

* C++17
* Boost (system, thread, asio, beast)
* nlohmann::json (fetched automatically)