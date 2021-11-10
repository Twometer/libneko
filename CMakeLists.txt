cmake_minimum_required(VERSION 3.19)
project(libneko)

set(CMAKE_CXX_STANDARD 14)

add_library(libneko src/String.cpp src/String.hpp src/Vector.cpp src/Vector.hpp)