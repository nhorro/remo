curl -X POST http://localhost:8080/rpc -H 'Content-Type: application/json' -d '{"jsonrpc":"2.0", "method":"hello", "params":["bob"], "id":1}'
curl -X POST http://localhost:8080/rpc -H 'Content-Type: application/json' -d '{"jsonrpc":"2.0", "method":"get_points", "params":[], "id":1}'
curl -X POST http://localhost:8080/rpc -H 'Content-Type: application/json' -d '{"jsonrpc":"2.0", "method":"fail", "params":[3.14], "id":99}'
