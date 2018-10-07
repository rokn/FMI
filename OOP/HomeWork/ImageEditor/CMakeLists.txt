cmake_minimum_required(VERSION 3.10)
project(ImageEditor)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE HEADERS include/*.h)
file(GLOB_RECURSE SOURCES src/*.cpp)
include_directories(include/ src/)

add_executable(ImageEditor ${SOURCES} ${HEADERS})
