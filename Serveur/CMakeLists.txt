cmake_minimum_required(VERSION 3.18)
project(Server)

set(CMAKE_CXX_STANDARD 11)

add_executable(Server main.cpp)

target_link_libraries(Server PUBLIC wsock32 ws2_32)