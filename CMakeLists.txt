cmake_minimum_required(VERSION 3.16)
project(libneko)

set(CMAKE_CXX_STANDARD 14)

set(LIBNEKO_SOURCES src/String.cpp src/String.hpp src/Vector.hpp src/ToString.cpp src/ToString.hpp src/StringBuffer.cpp src/StringBuffer.hpp src/Path.cpp src/Path.hpp src/Hash.cpp src/Hash.hpp src/HashMap.hpp src/Optional.hpp src/Function.hpp src/HashSet.hpp src/ByteBuffer.cpp src/ByteBuffer.hpp src/BitField.hpp)

add_library(libneko ${LIBNEKO_SOURCES})

add_executable(libneko_tests ${LIBNEKO_SOURCES} test/main.cpp)
target_include_directories(libneko_tests PUBLIC src/)