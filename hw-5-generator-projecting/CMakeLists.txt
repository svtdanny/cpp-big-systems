cmake_minimum_required(VERSION 3.0)
project(main)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER clang++)


#include_directories(src/Generators)
file(GLOB_RECURSE GENERATORS RELATIVE ${CMAKE_SOURCE_DIR} "src/Generators/*.cpp" "src/Generators/*.h")
file(GLOB_RECURSE CREATORS RELATIVE ${CMAKE_SOURCE_DIR} "src/Creators/*.cpp" "src/Creators/*.h")
file(GLOB_RECURSE FABRIC RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp" "src/*.h")

add_executable(main src/Test/main.cpp ${GENERATORS} ${CREATORS} ${FABRIC})
