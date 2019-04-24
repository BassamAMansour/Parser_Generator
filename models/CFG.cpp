//
// Created by Bassam on 4/18/2019.
//

#include "CFG.h"

CFG::CFG(set<string> terminalsSet, set<string> nonTerminalsSet, map<string, Production> productionsSet) {
    productions = productionsSet;
    terminals = terminalsSet;
    nonTerminals = nonTerminalsSet;
}

CFG::CFG() {}

