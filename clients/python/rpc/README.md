### 📄 `json_rpc_client.py`

```python
import requests
import json

class JsonRpcClient:
    def __init__(self, host="localhost", port=8080):
        self.url = f"http://{host}:{port}/rpc"
        self._id = 1

    def call(self, method, params=None):
        if params is None:
            params = []

        request = {
            "jsonrpc": "2.0",
            "method": method,
            "params": params,
            "id": self._id,
        }

        self._id += 1

        response = requests.post(self.url, json=request)
        response.raise_for_status()

        result = response.json()
        if "error" in result:
            raise Exception(f"RPC Error: {result['error']}")
        return result["result"]

# Example usage
if __name__ == "__main__":
    client = JsonRpcClient()
    try:
        result = client.call("hello", ["Python"])
        print("Response:", json.dumps(result, indent=2))
    except Exception as e:
        print("RPC call failed:", str(e))
```

---

### 📄 `README.md`

````markdown
# Remo Python JSON-RPC Client

This is a minimal **Python** client for calling Remo's JSON-RPC 2.0 HTTP server.

## ✅ Features

- Simple to use
- No external dependencies beyond `requests`
- Automatically handles RPC request IDs
- Raises exceptions for server-side errors

## 🔧 Example

```python
from json_rpc_client import JsonRpcClient

client = JsonRpcClient()
response = client.call("hello", ["Alice"])
print(response)
````

## 📦 Install

Install required package:

```bash
pip install requests
```

## 🚀 Run

```bash
python json_rpc_client.py
```

## 📝 Dependencies

* Python ≥ 3.6
* `requests`