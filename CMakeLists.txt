cmake_minimum_required(VERSION 3.0.0)
project(ssh-client VERSION 0.1.0)
set(CMAKE_TOOLCHAIN_FILE "F:/develop/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "" FORCE)
set(VCPKG_TARGET_TRIPLET "x64-windows-static")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

include_directories(include)
find_package(libssh CONFIG REQUIRED)

add_executable(ssh-client src/main.cpp src/ssh.cpp)
target_link_libraries(ssh-client PRIVATE ssh)
