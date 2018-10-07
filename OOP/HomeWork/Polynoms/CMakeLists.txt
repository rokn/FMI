cmake_minimum_required(VERSION 3.10)
project(Polynoms)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

add_executable(Polynoms ${SOURCES} ${HEADERS})