cmake_minimum_required(VERSION 3.10)
project(Server C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin/)

add_subdirectory(List)
add_executable(${PROJECT_NAME} main.c)

include_directories(List)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")
set(CMAKE_FIND_LIBRARY_PREFIXES "lib")

#find_library(LIST_LIB NAMES List PATHS .)

#message(${LIST_LIB})
#message(${CMAKE_CURRENT_BINARY_DIR})

#target_link_libraries(${PROJECT_NAME} List)

#install(TARGETS Server RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Install)