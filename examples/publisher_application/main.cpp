#include "beast_websocket_publisher.hpp"
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

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

int main() {
    BeastWebSocketPublisher publisher(8081);
    publisher.start();

    std::atomic_bool running{true};
    std::thread worker([&]() {
        float i = 0.0f;
        while (running) {
            
            CustomDataStructure data = {
                { 
                    {i, 2.0f, 3.0f}, 
                    {4.0f, i, 6.0f} }
            };
            publisher.publish(nlohmann::json(data));
            std::this_thread::sleep_for(std::chrono::seconds(1));
            i = i + 1.0f;
        }
    });

    std::cout << "Press Enter to stop..." << std::endl;
    std::cin.get();

    running = false;
    worker.join();
    publisher.stop();
}
