cmake_minimum_required(VERSION 3.16)
project(parser_playground)

set(CMAKE_CXX_STANDARD 14)

find_package(ZLIB)

add_executable(parser_playground src/main.cpp)