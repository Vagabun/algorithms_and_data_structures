cmake_minimum_required(VERSION 3.9)
project(7_eulerian_cycle C)

set(CMAKE_C_STANDARD 99)
MATH(EXPR stack_size "256 * 1024 * 1024") #256 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

add_executable(7_eulerian_cycle main.c)