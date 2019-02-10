cmake_minimum_required(VERSION 3.13)
project(Chapter19)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chapter19 main.cpp
                Vector.h
                GraphFiles/Graph.h
                GraphFiles/Point.h
                GraphFiles/std_lib_facilities.h)