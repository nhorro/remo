add_executable(example_app
    main.cpp
)

target_include_directories(example_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(example_app rpc)
