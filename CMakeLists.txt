cmake_minimum_required(VERSION 3.21)
project(BACAG)

set(CMAKE_CXX_STANDARD 11)

add_executable(BACAG main.cpp Z3.cpp Z3.h Polynomial.cpp Polynomial.h)
