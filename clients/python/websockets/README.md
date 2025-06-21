### 📄 `websocket_client.py`

```python
import websocket
import threading
import time
import json

class WebSocketClient:
    def __init__(self, host="localhost", port=8081):
        self.url = f"ws://{host}:{port}"
        self.ws = None
        self._running = False

    def on_message(self, ws, message):
        try:
            data = json.loads(message)
            print("[Received]", json.dumps(data, indent=2))
        except Exception as e:
            print("[Invalid JSON]", message)

    def on_error(self, ws, error):
        print("[Error]", error)

    def on_close(self, ws, close_status_code, close_msg):
        print("[Closed]", close_status_code, close_msg)
        self._running = False

    def on_open(self, ws):
        print("[Connected]")
        self._running = True

    def run_forever(self):
        self.ws = websocket.WebSocketApp(
            self.url,
            on_open=self.on_open,
            on_message=self.on_message,
            on_error=self.on_error,
            on_close=self.on_close,
        )
        self.ws.run_forever()

    def start(self):
        thread = threading.Thread(target=self.run_forever, daemon=True)
        thread.start()
        return thread

    def stop(self):
        if self.ws:
            self.ws.close()

if __name__ == "__main__":
    client = WebSocketClient()
    t = client.start()

    try:
        while client._running:
            time.sleep(1)
    except KeyboardInterrupt:
        client.stop()
```

---

### 📄 `README.md`

````markdown
# Remo Python WebSocket Client

This is a simple **Python WebSocket client** for receiving data published by a Remo server.

## ✅ Features

- Connects to Remo WebSocket publisher
- Receives and prints JSON data
- Automatically parses and formats incoming messages
- Clean shutdown via `Ctrl+C`

## 🔧 Example

```bash
python websocket_client.py
````

## 🧪 Output Example

```
[Connected]
[Received] {
  "points": [
    { "x": 0.0, "y": 2.0, "z": 3.0 },
    { "x": 4.0, "y": 0.0, "z": 6.0 }
  ]
}
```

## 📦 Install

```bash
pip install websocket-client
```

## 📝 Dependencies

* Python ≥ 3.6
* `websocket-client` library