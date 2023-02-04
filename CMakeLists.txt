cmake_minimum_required(VERSION 3.21)
project(SmartCalc C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(SmartCalc
        src/stack.c
        src/main.c
        src/stack.h)
