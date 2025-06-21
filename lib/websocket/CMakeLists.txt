add_library(remo-websockets)
target_sources(remo-websockets PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/beast_websocket_publisher.cpp
    ${CMAKE_CURRENT_LIST_DIR}/beast_websocket_publisher.hpp
)
target_link_libraries(remo-websockets PRIVATE ${Boost_LIBRARIES}  Boost::system nlohmann_json)
target_include_directories(remo-websockets PUBLIC ${CMAKE_CURRENT_LIST_DIR})
