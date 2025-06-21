#include "json_rpc_client.hpp"
#include <iostream>

int main() {
    try {
        JsonRpcClient client("localhost", "8080");
        auto result = client.call("hello", {"Remo"});
        std::cout << "Server response: " << result << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "RPC call failed: " << ex.what() << std::endl;
    }
}

