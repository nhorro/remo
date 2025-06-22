add_library(remo-rpc)
target_sources(remo-rpc PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/beast_rpc_server.cpp
    ${CMAKE_CURRENT_LIST_DIR}/beast_rpc_server.hpp
)
target_link_libraries(remo-rpc PRIVATE Boost::system nlohmann_json::nlohmann_json)
target_include_directories(remo-rpc
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/remo/rpc>
)

install(TARGETS remo-rpc
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(FILES ${CMAKE_CURRENT_LIST_DIR}/beast_rpc_server.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/remo/rpc)


