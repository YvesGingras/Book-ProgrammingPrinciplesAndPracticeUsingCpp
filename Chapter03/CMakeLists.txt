cmake_minimum_required(VERSION 3.12)
project(Chapter03)

set(CMAKE_CXX_STANDARD 14)

include_directories(Source)

add_executable(Chapter03 main.cpp
        Source/Drills.h
        Source/Exercices.h
        Source/std_lib_facilities.h
        Source/TryThis.h
        Source/Example.h Source/Utilities.h)
