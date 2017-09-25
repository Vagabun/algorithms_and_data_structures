cmake_minimum_required(VERSION 3.8)
project(radix_sort)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(radix_sort ${SOURCE_FILES})