add_executable(rpc_example_server
    main.cpp
)

target_include_directories(rpc_example_server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(rpc_example_server 
    remo-rpc 
    pthread 
    nlohmann_json
)
