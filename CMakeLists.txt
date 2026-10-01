cmake_minimum_required(VERSION 4.3)
project(RV64_Simulator)

set(CMAKE_CXX_STANDARD 26)

add_executable(RV64_Simulator main.cpp cpu.cpp)
