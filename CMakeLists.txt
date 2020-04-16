cmake_minimum_required(VERSION 3.15)
project(rcube_solver)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(src)

add_executable(rcube_solver main.cpp)

target_link_libraries(rcube_solver cubesolver)