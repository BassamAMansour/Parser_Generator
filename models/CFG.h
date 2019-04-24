//
// Created by Bassam on 4/18/2019.
//

#ifndef PARSER_GENERATOR_CFG_H
#define PARSER_GENERATOR_CFG_H

#include <string>
#include <set>
#include <vector>
#include <map>
#include "Production.h"

using namespace std;

class CFG {


public:
    CFG(set<string> terminalsSet, set <string> nonTerminalsSet, map<string, Production> productionsSet);

    CFG();

    //The name of the production mapped to the productions
    map<string, Production> productions;
    set<string> terminals;
    set<string> nonTerminals;
    string startState;

    static const char EPSILON = '&';
};


#endif //PARSER_GENERATOR_CFG_H
