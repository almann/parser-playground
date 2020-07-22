cmake_minimum_required(VERSION 3.10)
project(parser_playground)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-march=haswell")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(parser_playground src/main.cpp src/varuint.cpp src/test_varuint.cpp)
target_include_directories(parser_playground PRIVATE include)
target_link_libraries(parser_playground ${CONAN_LIBS})