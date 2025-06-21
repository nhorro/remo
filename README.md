# Remo

![logo](./doc/logo.png)

**Remo** es una biblioteca en C++ para construir backends que ofrecen:

- Llamadas a procedimientos remotos (RPC) sobre HTTP utilizando el estándar **JSON-RPC 2.0**.
- Publicación de datos y eventos a través de **WebSockets**.

Está diseñada para ser simple de integrar en aplicaciones backend escritas en C++, con una interfaz flexible y clara. Remo utiliza **Boost.Beast** como base para la comunicación HTTP/WebSocket.

---

## ✨ Características

- 📡 **RPC HTTP** con soporte para tipos primitivos y objetos compuestos.
- 📤 **Publicación WebSocket** para clientes suscritos.
- 🔧 API flexible basada en `std::function` para registrar handlers.
- 🚦 Soporte para errores y respuestas JSON-RPC 2.0 válidas.
- 💻 Ejemplos de uso incluidos.

---

## 📦 Dependencias

- C++17
- [Boost](https://www.boost.org/) (componentes `system`, `thread`, `asio`, `beast`)
- [nlohmann/json](https://github.com/nlohmann/json) (incluido vía `FetchContent`)

---

## 🧪 Ejemplo de uso

```cpp
BeastRPCServer server(8080);

server.register_method("hello", [](const json& params) {
    std::string name = params.at(0);
    return "Hello " + name + "!";
});

server.start();
````

---

## 📁 Estructura del proyecto

```
lib/
 ├── rpc/           # Servidor RPC con Boost.Beast
 └── websocket/     # Publicador WebSocket (en desarrollo)

examples/
 ├── rpc_application/  # Ejemplo completo de uso con JSON-RPC
 └── websocket_example/ (pendiente)
```

---

## 🚀 Próximos pasos

* [ ] WebSocket publisher (en progreso)
* [ ] Sistema de suscripciones
* [ ] Integración con Catch2 para tests automatizados
* [ ] Instalación vía `make install`

---

## ⚖️ Licencia

MIT

---

## 🙌 Agradecimientos

Este proyecto utiliza:

* [Boost.Beast](https://www.boost.org/doc/libs/release/libs/beast/)
* [nlohmann/json](https://github.com/nlohmann/json)