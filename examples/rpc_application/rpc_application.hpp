#pragma once
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

/**
 * @brief Example of a protocol-independent remote controlled application
 * 
 */
class RPCApplication {
public:
    
    // 1. A simple method that returns a primitive type
    std::string hello(const std::string& name) {
        return "Hello " + name + ", how are you today?";
    }

    // 2. A method that returns a custom composite object. 
    struct CompositeResult {
        struct Point {
            float x;
            float y;
            float z;
        };
        std::vector<Point> points;
    };

    CompositeResult get_points() {
        return CompositeResult{{
            { 0.1f, 0.2f, 0.3f},
            { 0.4f, 0.5f, 0.6f}
        }};
    };

    // 3. A method that intentionally fails
    float this_method_always_fails(float x) {
        throw std::runtime_error("Computation failed: something went wrong.");
    }
};