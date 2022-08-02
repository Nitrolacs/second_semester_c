cmake_minimum_required(VERSION 3.22)
project(medical_history C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(medical_history
        functions.c
        functions.h
        main.c
        structure.h)
