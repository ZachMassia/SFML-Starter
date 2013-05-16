cmake_minimum_required(VERSION 2.8)

project(sfml_starter)

# Chose a compiler:
# set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

add_definitions(-std=c++0x)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

add_subdirectory(src)

add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} src)

install(TARGETS ${CMAKE_PROJECT_NAME}
        RUNTIME DESTINATION bin)
