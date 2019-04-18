cmake_minimum_required(VERSION 3.13)
project(Parser_Generator)

set(CMAKE_CXX_STANDARD 17)

add_executable(Parser_Generator main.cpp models/CFG.cpp models/CFG.h models/ParsingTable.cpp models/ParsingTable.h ParseTableGenerator.cpp ParseTableGenerator.h CFG_Generator.cpp CFG_Generator.h models/Production.cpp models/Production.h)