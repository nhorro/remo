cmake_minimum_required(VERSION 3.10)
project(beast_framework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- GLOBAL DEPENDENCIES ---

# Boost
find_package(Boost REQUIRED COMPONENTS system thread)
include_directories(${Boost_INCLUDE_DIRS})

# nlohmann/json (via FetchContent)
include(FetchContent)
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)
FetchContent_MakeAvailable(json)

# --- SUBDIRECTORIES ---

add_subdirectory(lib)
add_subdirectory(examples)