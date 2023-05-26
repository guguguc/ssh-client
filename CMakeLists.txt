cmake_minimum_required(VERSION 3.0.0)
project(ssh-client VERSION 0.1.0)

find_package(libssh CONFIG REQUIRED)
add_executable(ssh-client main.cpp ssh.cpp)
target_link_libraries(ssh-client PRIVATE ssh)
