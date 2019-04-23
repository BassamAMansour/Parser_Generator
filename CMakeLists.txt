cmake_minimum_required(VERSION 3.12)
project(Parser_Generator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(models)

add_executable(Parser_Generator
        models/CFG.cpp
        models/CFG.h
        models/ParsingTable.cpp
        models/ParsingTable.h
        models/Production.cpp
        models/Production.h
        CFG_Generator.cpp
        CFG_Generator.h
        main.cpp
        ParseTableGenerator.cpp
        ParseTableGenerator.h)
