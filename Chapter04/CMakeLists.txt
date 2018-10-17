cmake_minimum_required(VERSION 3.12)
project(Chapter04)

set(CMAKE_CXX_STANDARD 17)

include_directories(Source)

add_executable(Chapter04 main.cpp
        Source/Utilities.h
        Source/Drills.h
        Source/Example.h
        Source/Exercices.h
        Source/std_lib_facilities.h
        Source/TryThis.h
         )
