cmake_minimum_required(VERSION 4.3)
project(RV64_Simulator)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(RV64_Simulator main.cpp cpu.cpp)
