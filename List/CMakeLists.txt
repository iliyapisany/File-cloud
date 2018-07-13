cmake_minimum_required(VERSION 3.10)
project(List C)

set(SOURCE_FILES List.c)

add_library(${PROJECT_NAME} MODULE ${SOURCE_FILES})

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../Install/Lib)