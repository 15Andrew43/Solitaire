# cmake_minimum_required(VERSION <specify CMake version here>)
project(Solitaire)

set(CMAKE_CXX_STANDARD 14)

add_executable(Solitaire main.cpp Position.cpp Position.h)