//
// Created by Ahmednasser on 4/24/2019.
//

#ifndef PARSER_GENERATOR_SIMULATOR_H
#define PARSER_GENERATOR_SIMULATOR_H
#include <iostream>
#include <algorithm>
#include <models/ParsingTable.h>


class Simulator {
public:
    Simulator(const string &in, const ParsingTable &table);

private:
    string in;
    string test;
    ParsingTable table;
    void parsefile();
    void run();
    void splitInput (string input, vector<string> &splitedInput);



};


#endif //PARSER_GENERATOR_SIMULATOR_H
