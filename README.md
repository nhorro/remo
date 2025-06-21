# Remo

![logo](./doc/logo.png)

**Remo** is a modular C++ library for building modern backend components that offer:

* Remote Procedure Calls (**RPC**) over HTTP using the **JSON-RPC 2.0** protocol.
* Real-time data and event publishing over **WebSockets**.

Designed for backend applications written in modern C++, Remo provides clear interfaces and is built on top of **Boost.Beast** for robust HTTP and WebSocket communication.

---

## ✨ Features

* 📡 **JSON-RPC 2.0 over HTTP** with support for primitive and structured types.
* 📤 **Generic WebSocket broadcasting** for JSON-serializable data.
* 🔧 Easy-to-use APIs with `std::function`-based handler registration.
* 🚦 Robust error handling and compliant JSON-RPC 2.0 responses.
* 💻 Clean example applications for both RPC and WebSocket components.

---

## 📦 Dependencies

* **C++17**
* [Boost](https://www.boost.org/) (`system`, `thread`, `asio`, `beast`)
* [nlohmann/json](https://github.com/nlohmann/json) (included via `FetchContent`)

---

## 🧪 Examples

### RPC server

```cpp
BeastRPCServer server(8080);

server.register_method("hello", [](const json& params) {
    std::string name = params.at(0);
    return "Hello " + name + "!";
});

server.start();
```

### WebSocket publisher

```cpp
BeastWebSocketPublisher publisher(8081);
publisher.start();

// In a separate thread or periodic task
publisher.publish({{"status", "ok"}, {"temperature", 42.5}});
```

---

## 📁 Project structure

```
lib/
 ├── rpc/             # JSON-RPC over HTTP server (remorpc target)
 └── websocket/       # WebSocket publisher (remowebsockets target)

examples/
 ├── rpc_application/       # Working RPC example
 └── publisher_application/ # Working WebSocket publishing example

doc/
 └── logo.png
```

---

## 🚀 Roadmap

* ✅ WebSocket broadcasting for generic JSON data
* ⏳ Topic-based subscription mechanism
* ⏳ Catch2 integration for testing
* ⏳ Packaging and installation support

---

## ⚖️ License

MIT

---

## 🙌 Acknowledgments

This project uses:

* [Boost.Beast](https://www.boost.org/doc/libs/release/libs/beast/)
* [nlohmann/json](https://github.com/nlohmann/json)