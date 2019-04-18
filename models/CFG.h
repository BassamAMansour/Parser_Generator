//
// Created by Bassam on 4/18/2019.
//

#ifndef PARSER_GENERATOR_CFG_H
#define PARSER_GENERATOR_CFG_H

#include <string>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include "Production.h"

using namespace std;

class CFG {


public:
    //The name of the production mapped to the productions
    unordered_map<string, Production> productions;
    unordered_set<string> terminals;
    unordered_set<string> nonTerminals;
    string startState;

    static const char EPSILON = 0;
};


#endif //PARSER_GENERATOR_CFG_H
