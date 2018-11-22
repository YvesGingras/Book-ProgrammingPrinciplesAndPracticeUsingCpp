cmake_minimum_required(VERSION 3.12)
project(Chapter09)

set(CMAKE_CXX_STANDARD 17)


add_executable(Chapter09 main.cpp
        Drill.cpp Drill.h
        Chrono.cpp Chrono.h
        NamePairs.cpp NamePairs.h
        Library/Book.cpp Library/Book.h
        Library/Patron.cpp Library/Patron.h
        Library/Library.cpp Library/Library.h)