add_library(remo-rpc)
target_sources(remo-rpc PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/beast_rpc_server.cpp
    ${CMAKE_CURRENT_LIST_DIR}/beast_rpc_server.hpp
)
target_link_libraries(remo-rpc PRIVATE Boost::system nlohmann_json)
target_include_directories(remo-rpc PUBLIC ${CMAKE_CURRENT_LIST_DIR})

