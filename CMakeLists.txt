cmake_minimum_required(VERSION 3.16)
project(libneko)

set(CMAKE_CXX_STANDARD 14)

set(LIBNEKO_SOURCES src/String.cpp src/String.hpp src/Vector.cpp src/Vector.hpp src/ToString.cpp src/ToString.hpp src/StringBuffer.cpp src/StringBuffer.hpp)

add_library(libneko ${LIBNEKO_SOURCES})

add_executable(libneko_tests ${LIBNEKO_SOURCES} test/main.cpp)
target_include_directories(libneko_tests PUBLIC src/)