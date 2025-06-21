# WebSocket Publisher Example

The [example publisher application](../examples/publisher_application/) shows how to broadcast structured data to multiple clients using **Remo's WebSocket publisher**.

---

## 🧩 Data Model

Any data published must be **JSON-serializable**.

If your structure contains custom types, you must define `to_json()` converters using [nlohmann::json](https://github.com/nlohmann/json):

```cpp
struct CustomDataStructure {
    struct Point {
        float x, y, z;
    };
    std::vector<Point> points;
};

inline void to_json(nlohmann::json& j, const CustomDataStructure::Point& p) {
    j = { {"x", p.x}, {"y", p.y}, {"z", p.z} };
}

inline void to_json(nlohmann::json& j, const CustomDataStructure& d) {
    j = { {"points", d.points} };
}
````

---

## 🚀 Publisher Application

The publisher can be used from any thread. Here's a minimal working example:

```cpp
#include "beast_websocket_publisher.hpp"
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

int main() {
    BeastWebSocketPublisher publisher(8081);
    publisher.start();

    std::atomic_bool running{true};
    std::thread worker([&]() {
        float i = 0.0f;
        while (running) {
            CustomDataStructure data = {
                { {i, 2.0f, 3.0f}, {4.0f, i, 6.0f} }
            };
            publisher.publish(nlohmann::json(data));
            std::this_thread::sleep_for(std::chrono::seconds(1));
            i += 1.0f;
        }
    });

    std::cout << "Press Enter to stop...\n";
    std::cin.get();

    running = false;
    worker.join();
    publisher.stop();
}
```

---

## 🌐 Testing with a Web Browser

You can test your publisher with a minimal HTML+JavaScript client.

Save this as `client.html` and open it in your browser:

```html
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Remo WebSocket Client</title>
  <style>
    body { font-family: sans-serif; padding: 1em; background: #f8f8f8; max-width: 600px; margin: auto; }
    .status { display: inline-block; width: 12px; height: 12px; border-radius: 50%; margin-left: 10px; background: gray; }
    #output { margin-top: 1em; padding: 1em; background: #fff; border: 1px solid #ccc; min-height: 100px; white-space: pre-wrap; font-family: monospace; }
  </style>
</head>
<body>

<h2>Remo WebSocket Client</h2>

<div>
  <label>Host:</label>
  <input type="text" id="host" value="localhost">
  <label>Port:</label>
  <input type="text" id="port" value="8081">
  <button id="connectBtn" onclick="toggleConnection()">Connect</button>
  <span class="status" id="statusLed"></span>
</div>

<div id="output">(no data)</div>

<script>
let ws = null;

function setStatus(connected) {
  document.getElementById("statusLed").style.background = connected ? "green" : "gray";
  document.getElementById("connectBtn").textContent = connected ? "Disconnect" : "Connect";
}

function toggleConnection() {
  if (ws && (ws.readyState === WebSocket.OPEN || ws.readyState === WebSocket.CONNECTING)) {
    ws.onclose = () => { setStatus(false); ws = null; };
    ws.close();
    setTimeout(() => { if (ws && ws.readyState !== WebSocket.OPEN) { setStatus(false); ws = null; } }, 1000);
    return;
  }

  const url = `ws://${document.getElementById("host").value}:${document.getElementById("port").value}`;
  ws = new WebSocket(url);

  ws.onopen = () => { setStatus(true); };
  ws.onmessage = (event) => {
    const output = document.getElementById("output");
    try {
      output.textContent = JSON.stringify(JSON.parse(event.data), null, 2);
    } catch {
      output.textContent = event.data;
    }
  };
  ws.onerror = (err) => console.error("WebSocket error:", err);
  ws.onclose = () => { setStatus(false); };
}

setStatus(false);
</script>

</body>
</html>
```

---

## ✅ Summary

* Data can be streamed using a single publisher object across threads.
* Clients can connect and receive live updates in JSON format.
* No polling or request handling is needed—it's push-based.

Remo's WebSocket interface is ideal for **live dashboards**, **event streams**, or **data monitoring applications**.

```