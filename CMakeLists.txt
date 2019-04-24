cmake_minimum_required(VERSION 3.10)
project(Parser_Generator)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(models)

add_executable(Parser_Generator
        models/CFG.cpp
        models/CFG.h
        models/ParsingTable.cpp
        models/ParsingTable.h
        models/Production.cpp
        models/Production.h
        testFiles/test.txt
        testFiles/test2.txt
        .gitignore
        CFG_Generator.cpp
        CFG_Generator.h
        main.cpp
        ParseTableGenerator.cpp
        ParseTableGenerator.h Simulator.cpp Simulator.h)
