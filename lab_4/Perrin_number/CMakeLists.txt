cmake_minimum_required(VERSION 3.22)
project(Perrin_number C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Perrin_number
        main.c
        myMath.c
        myMath.h)
