cmake_minimum_required(VERSION 4.0)
project(bc)

set(CMAKE_CXX_STANDARD 20)

ENABLE_TESTING()

add_executable(bc
        bc.c
        common.h
        debug.h
        debug.c
        chunk.h
        chunk.c
        astWalk.h
        astWalk.c
)