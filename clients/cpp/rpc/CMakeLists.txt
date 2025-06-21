cmake_minimum_required(VERSION 3.10)
project(json_rpc_client CXX)

find_package(Boost REQUIRED COMPONENTS system thread)
find_package(nlohmann_json REQUIRED)

add_executable(json_rpc_client
    json_rpc_client.cpp
    main.cpp
)

target_link_libraries(json_rpc_client
    PRIVATE
        Boost::system
        Boost::thread
        nlohmann_json::nlohmann_json
)
