cmake_minimum_required(VERSION 3.10)
project(remo VERSION 0.1.0)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

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
add_subdirectory(clients)

install(EXPORT RemoTargets
    FILE RemoTargets.cmake
    NAMESPACE Remo::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Remo
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/RemoConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/RemoConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Remo
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/RemoConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/RemoConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/RemoConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Remo
)

include(CPack)
