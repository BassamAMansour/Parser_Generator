//
// Created by Bassam on 4/18/2019.
//

#include "CFG.h"

CFG::CFG(unordered_set<string> t, unordered_set<string> nonT, unordered_map<string, Production> prod) {
    productions = prod;
    terminals = t;
    nonTerminals = nonT;
}

CFG::CFG() {}

