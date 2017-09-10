cmake_minimum_required(VERSION 3.8)
project(rand_generator)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(rand_generator ${SOURCE_FILES})