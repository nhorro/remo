#include "json_ws_client.hpp"
#include <iostream>

int main() {
    JsonWebSocketClient client("localhost", "8081");

    client.start([](const nlohmann::json& j) {
        std::cout << "Received: " << j.dump(2) << "\n";
    });

    std::cout << "Press Enter to exit...\n";
    std::cin.get();
    client.stop();
}
