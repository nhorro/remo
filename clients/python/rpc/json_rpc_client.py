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
