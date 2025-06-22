add_library(remo-websockets)
add_library(Remo::remo-websockets ALIAS remo-websockets)
target_sources(remo-websockets PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/beast_websocket_publisher.cpp
    ${CMAKE_CURRENT_LIST_DIR}/beast_websocket_publisher.hpp
)
target_link_libraries(remo-websockets PRIVATE ${Boost_LIBRARIES} Boost::system nlohmann_json::nlohmann_json)
target_include_directories(remo-websockets
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/remo/websocket>
)

install(TARGETS remo-websockets
    EXPORT RemoTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(FILES ${CMAKE_CURRENT_LIST_DIR}/beast_websocket_publisher.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/remo/websocket)

