add_executable(pub_example_server
    main.cpp
)

target_include_directories(pub_example_server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(pub_example_server 
    remo-websockets 
    pthread
    nlohmann_json
)