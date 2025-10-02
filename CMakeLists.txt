    cmake_minimum_required(VERSION 3.29)
    project(2 C)

    set(CMAKE_C_STANDARD 11)

    add_compile_options(-Wno-implicit-function-declaration)

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lm")

    add_executable(2 main.cpp)