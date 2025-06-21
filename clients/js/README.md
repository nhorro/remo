# Remo JavaScript Client

This folder contains a simple JavaScript client for interacting with a [Remo](https://github.com/nhorro/remo) server.

It provides:

- A class for making JSON-RPC 2.0 calls over HTTP.
- A class for receiving real-time updates via WebSocket and handling them via a callback.

---

## 📦 Contents

- `remo_client.js`: Contains the `RemoRPCClient` and `RemoWebSocketSubscriber` classes.
- `example.html`: Minimal HTML page demonstrating how to use both classes.

---

## 🔧 Usage

### 1. JSON-RPC client

```javascript
import { RemoRPCClient } from './remo_client.js';

const rpc = new RemoRPCClient("localhost", 8080);

rpc.call("hello", ["Alice"])
   .then(result => console.log("Result:", result))
   .catch(err => console.error("RPC Error:", err));
````

### 2. WebSocket subscriber

```javascript
import { RemoWebSocketSubscriber } from './remo_client.js';

const ws = new RemoWebSocketSubscriber("localhost", 8081);

ws.connect((data) => {
  console.log("Received WebSocket message:", data);
});
```

---

## 🚀 Running the example

1. Make sure the Remo RPC and WebSocket servers are running on ports 8080 and 8081.
2. Open `example.html` in a modern browser with dev tools open to view console output.
3. You should see:

* A result from the RPC method `hello`.
* Any incoming WebSocket messages printed in the console.

---

## ✅ Requirements

* A modern browser (Chrome, Firefox, etc.).
* No server setup is required; everything runs in-browser.
* If serving from disk fails (due to CORS or module loading), use a minimal web server:

```bash
python3 -m http.server
```

Then visit `http://localhost:8000/clients/js_client/example.html`.

---

## 📚 See Also

* [Remo main repository](https://github.com/nhorro/remo)
* [Python client](../python_client)
* [C++ clients](../cpp_client_rpc), (../cpp\_client\_ws)

---

## ⚖️ License

MIT