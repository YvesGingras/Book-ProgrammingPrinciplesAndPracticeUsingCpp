cmake_minimum_required(VERSION 3.12)
project(Chapter10)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chapter10 main.cpp
        FinalExample.cpp FinalExample.h
        Invalid.h
        Drill/Point.h
        Drill/Drill.cpp Drill/Drill.h)