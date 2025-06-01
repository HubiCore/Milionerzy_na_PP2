
cmake_minimum_required(VERSION 3.10)
project(pp2 C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "-mwindows")

include_directories("C:/MinGW64/include")  # Change this to the actual Allegro include path
link_directories("C:/MinGW64/lib")

add_executable(pp2 main.c
        kola_ratunkowe.c
        other_functions.h
        other_functions.c
        question_loading.h
        question_loading.c
        button.h
        button.c
        main_menu.h
        main_menu.c)
target_link_libraries(pp2
        allegro
        allegro_primitives
        allegro_font
        allegro_ttf
        allegro_image
        allegro_audio
        allegro_acodec
)
