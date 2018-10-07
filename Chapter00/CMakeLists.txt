cmake_minimum_required(VERSION 3.12)
project(Chapter00)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chapter00 main.cpp
                Source/TryThis.h
                Source/Drills.h
                Source/Exercices.h
                Source/std_lib_facilities.h)