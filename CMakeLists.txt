    cmake_minimum_required(VERSION 3.29)
project(2 C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wno-implicit-function-declaration)

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lm")

    add_executable(2 main.c
        SelectSort.c
        SelectSort.h
        BubbleSort.c
        BubbleSort.h
        Utils.c
        Utils.h
        ShakerSort.c
        ShakerSort.h
        InsertSort.c
        InsertSort.h
        ShellSort.c
        ShellSort.h
        BinarySearch.c
        BinarySearch.h
        StructSort.c
        StructSort.h
        Phonebook.c
        Phonebook.h
        HeapSort.c
        HeapSort.h
        QuickSort.c
        QuickSort.h
        ListProcessing.c
        ListProcessing.h
        MergeProcessing.c
        MergeProcessing.h
            DigitalSort.c
            DigitalSort.h
            hesh1.c
            hesh1.h
            hesh2.c
            hesh2.h)