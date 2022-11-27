cmake_minimum_required(VERSION 3.22)
project(p4)

set(CMAKE_CXX_STANDARD 14)

add_executable(p4 main.cpp JumpPrime.h JumpPrime.cpp DuelingJP.h DuelingJP.cpp)
