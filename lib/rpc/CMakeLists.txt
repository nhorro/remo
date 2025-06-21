find_package(Boost REQUIRED COMPONENTS system thread)
include_directories(${Boost_INCLUDE_DIRS})

add_library(rpc
    beast_rpc_server.cpp
)

target_include_directories(rpc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rpc
    Boost::system
    Boost::thread
    pthread
)

