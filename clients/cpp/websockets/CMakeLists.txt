cmake_minimum_required(VERSION 3.10)
project(json_ws_client CXX)

find_package(Boost REQUIRED COMPONENTS system thread)
find_package(nlohmann_json REQUIRED)

find_package(Boost REQUIRED COMPONENTS system thread)

add_executable(json_ws_client
    main.cpp
    json_ws_client.cpp
)

target_link_libraries(json_ws_client
    nlohmann_json::nlohmann_json
    Boost::system
    Boost::thread
)
