class RemoRPCClient {
    constructor(host = 'localhost', port = 8080) {
      this.url = `http://${host}:${port}/rpc`;
      this._id = 0;
    }
  
    async call(method, params = []) {
      const payload = {
        jsonrpc: "2.0",
        method,
        params,
        id: ++this._id,
      };
  
      const response = await fetch(this.url, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(payload),
      });
  
      if (!response.ok) {
        throw new Error(`HTTP error: ${response.status}`);
      }
  
      const result = await response.json();
  
      if ("error" in result) {
        throw new Error(`RPC error: ${JSON.stringify(result.error)}`);
      }
  
      return result.result;
    }
  }
  
  class RemoWebSocketSubscriber {
    constructor(host = 'localhost', port = 8081) {
      this.url = `ws://${host}:${port}`;
      this.ws = null;
    }
  
    connect(callback) {
      this.ws = new WebSocket(this.url);
  
      this.ws.onopen = () => {
        console.log("[WebSocket] Connected");
      };
  
      this.ws.onmessage = (event) => {
        try {
          const data = JSON.parse(event.data);
          callback(data);
        } catch (e) {
          console.error("[WebSocket] Invalid JSON:", event.data);
        }
      };
  
      this.ws.onerror = (err) => {
        console.error("[WebSocket] Error:", err);
      };
  
      this.ws.onclose = () => {
        console.log("[WebSocket] Disconnected");
      };
    }
  
    disconnect() {
      if (this.ws) {
        this.ws.close();
      }
    }
  }
  