# Remo

![logo](./doc/logo.png)

**Remo** is a C++ library for building backends that provide:

- Remote Procedure Calls (RPC) over HTTP using the **JSON-RPC 2.0** standard.
- Data and event publishing via **WebSockets**.

It is designed to be simple to integrate into C++ backend applications, with a clear and flexible interface. Remo uses **Boost.Beast** as the foundation for HTTP/WebSocket communication.

---

## ✨ Features

- 📡 **HTTP RPC** with support for primitive types and composite objects.
- 📤 **WebSocket publishing** for subscribed clients.
- 🔧 Flexible API based on `std::function` for handler registration.
- 🚦 Full support for errors and valid JSON-RPC 2.0 responses.
- 💻 Usage examples included.

---

## 📦 Dependencies

- C++17
- [Boost](https://www.boost.org/) (`system`, `thread`, `asio`, `beast` components)
- [nlohmann/json](https://github.com/nlohmann/json) (included via `FetchContent`)

---

## 🧪 Usage example

```cpp
BeastRPCServer server(8080);

server.register_method("hello", [](const json& params) {
    std::string name = params.at(0);
    return "Hello " + name + "!";
});

server.start();
````

---

## 📁 Project structure

```
lib/
 ├── rpc/              # RPC server using Boost.Beast
 └── websocket/        # WebSocket publisher (in development)

examples/
 ├── rpc_application/  # Full example using JSON-RPC
 └── websocket_example/ (planned)
```

---

## 🚀 Roadmap

* [ ] WebSocket publisher (in progress)
* [ ] Subscription system
* [ ] Catch2 integration for automated testing
* [ ] Installation via `make install`

---

## ⚖️ License

MIT

---

## 🙌 Acknowledgments

This project uses:

* [Boost.Beast](https://www.boost.org/doc/libs/release/libs/beast/)
* [nlohmann/json](https://github.com/nlohmann/json)