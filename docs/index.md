Perfecto. Para integrar ambas guías en la documentación de GitHub Pages con estilo claro y navegable, actualizá tu `index.md` con una sección “Getting Started” y enlaces a las guías. Aquí tenés el contenido sugerido para `index.md`:
![logo](logo.png)

Remo is a lightweight C++ library for building backend applications with:

- 📡 Remote Procedure Calls (RPC) over HTTP using [JSON-RPC 2.0](https://www.jsonrpc.org/specification)
- 🔄 Real-time data publishing over **WebSockets**

Built on top of **Boost.Beast** and **nlohmann/json**, Remo aims for simplicity, modularity, and ease of integration in embedded or desktop applications.

---

## 🚀 Getting Started

Here are minimal working examples to get you started with Remo:

- 👉 [RPC Server Example](./guides/rpc.md): bind existing C++ methods and expose them over JSON-RPC 2.0.
- 👉 [WebSocket Publisher Example](./guides/websocket.md): stream custom data to connected clients in real time.

---

## 🧱 Project Structure

```

remo/
├── lib/                # Library code
│   ├── rpc/            # RPC backend (HTTP + JSON-RPC 2.0)
│   └── websocket/      # WebSocket publisher
├── examples/           # Usage examples
└── guides/             # Documentation in Markdown

```

---

## 📦 Dependencies

- C++17
- [Boost](https://www.boost.org/) (`system`, `thread`, `asio`, `beast`)
- [nlohmann/json](https://github.com/nlohmann/json) (fetched automatically)

---

## 📝 License

MIT

---

## 🙌 Acknowledgments

- [Boost.Beast](https://www.boost.org/doc/libs/release/libs/beast/)
- [nlohmann/json](https://github.com/nlohmann/json)
