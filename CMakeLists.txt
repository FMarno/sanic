cmake_minimum_required(VERSION 3.9)

project(sanic)

set(CMAKE_CXX_STANDARD 17)

add_executable(sanic main.cpp tokeniser.hpp)
