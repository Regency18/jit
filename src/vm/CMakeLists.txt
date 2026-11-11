cmake_minimum_required(VERSION 4.0)
project(bc)

set(CMAKE_CXX_STANDARD 20)

ENABLE_TESTING()

add_executable(vm
        vm.h
        vm.c
        main.c
)