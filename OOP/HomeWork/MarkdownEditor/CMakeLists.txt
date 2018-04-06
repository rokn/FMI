cmake_minimum_required(VERSION 3.9)
project(MarkdownEditor)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

add_executable(MarkdownEditor ${SOURCES} ${HEADERS})