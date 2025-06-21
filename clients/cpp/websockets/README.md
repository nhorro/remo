# Remo C++ WebSocket Client

This is a lightweight WebSocket client in C++ that connects to a Remo WebSocket publisher and receives JSON messages.

## ✅ Features

- Automatic reconnection on failure
- Runs in background thread
- Receives and parses JSON messages
- Minimal interface

## 🔧 Example usage

```cpp
#include "json_ws_client.hpp"
#include <iostream>

int main() {
    JsonWebSocketClient client("localhost", "8081");

    client.start([](const nlohmann::json& j) {
        std::cout << "Received: " << j.dump(2) << "\n";
    });

    std::cout << "Press Enter to exit...\n";
    std::cin.get();
    client.stop();
}
````

## 📦 Build

```bash
mkdir build && cd build
cmake ..
make
./json_ws_client
```

## 📝 Dependencies

* C++17
* Boost (system, thread, asio, beast)
* nlohmann::json (fetched automatically)