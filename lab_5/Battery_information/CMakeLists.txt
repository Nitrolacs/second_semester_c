cmake_minimum_required(VERSION 3.22)
project(Battery_information C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Battery_information
        functions.c
        functions.h
        main.c
        structure.h)
