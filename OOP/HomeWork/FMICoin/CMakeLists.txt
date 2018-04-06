cmake_minimum_required(VERSION 3.9)
project(FMICoin)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS src/*.h)

add_executable(FMICoin ${SOURCES} ${HEADERS})
