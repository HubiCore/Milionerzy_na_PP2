cmake_minimum_required(VERSION 3.30)
project(test C)

set(CMAKE_C_STANDARD 11)
include_directories()
add_executable(test main.c
        kola_ratunkowe.c
        other_functions.h
        other_functions.c
        question_loading.h
        question_loading.c
)
