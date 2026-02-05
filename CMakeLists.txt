cmake_minimum_required(VERSION 3.31)

project(testServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(/MaximEngine/)

add_subdirectory(Cookbook)
add_subdirectory(MaximEngine)
