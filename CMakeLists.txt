cmake_minimum_required(VERSION 3.10)
project(Server C)

set(CMAKE_C_STANDARD 99)

add_executable(Server main.c)

include_directories(List)
add_subdirectory(List)

install(TARGETS Server RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Install)