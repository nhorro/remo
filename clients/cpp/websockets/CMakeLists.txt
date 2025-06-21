cmake_minimum_required(VERSION 3.10)
project(json_ws_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS system thread)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(json_ws_client
    main.cpp
    json_ws_client.cpp
)

target_link_libraries(json_ws_client
    Boost::system
    Boost::thread
)

include(FetchContent)
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)
FetchContent_MakeAvailable(json)

target_link_libraries(json_ws_client nlohmann_json::nlohmann_json)
