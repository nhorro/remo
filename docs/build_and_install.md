# Building and Installing Remo

This guide describes how to build the library and examples on Linux using **CMake** and how to create a distribution package.

---

## Build

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

## Install

Install the headers and libraries to the default prefix (`/usr/local`):

```bash
sudo cmake --install .
```

You can change the install location with `-DCMAKE_INSTALL_PREFIX=path` when invoking `cmake`.

## Package

A compressed tarball of the install tree can be generated with **CPack**:

```bash
cpack -G TGZ
```

This produces a `remo-<version>.tar.gz` archive that can be redistributed and extracted on other machines.

## Using the package

After installing Remo you can find and link the libraries from another CMake project:

```cmake
find_package(Remo REQUIRED)

add_executable(my_app main.cpp)
# Link the components you need
target_link_libraries(my_app PRIVATE Remo::remo-rpc Remo::remo-websockets)
```

If you installed Remo to a custom prefix, remember to add the install location to
`CMAKE_PREFIX_PATH` or set the `Remo_DIR` variable when configuring your project.

