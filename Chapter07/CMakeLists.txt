cmake_minimum_required(VERSION 3.12)
project(Chapter07)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chapter07 main.cpp
        CalculatorCh06.cpp CalculatorCh06.h
        VariousDeclarations.h
        CalculatorV1.cpp CalculatorV1.h
        HandsOn.cpp HandsOn.h
        Solution7_8_2.cpp
        Drill.cpp Drill.h
        Exercises.cpp Exercises.h)