//
// Created by Bassam on 4/18/2019.
//

#include <iostream>
#include "ParsingTable.h"

ParsingTable::ParsingTable(const set<string> &terminals, const set<string> &nonTerminals) {
    initTerminalsIndices(terminals);
    initNonTerminalsIndices(nonTerminals);
    initEntriesTable(terminals.size(), nonTerminals.size());
}

void ParsingTable::initTerminalsIndices(set<string> terminals) {
    int i = 0;
    for (const auto &terminal:terminals) {
        terminalsIndices[terminal] = i++;
    }
    terminalsIndices[string(1, END_OF_TOKENS)] = i;
}

void ParsingTable::initNonTerminalsIndices(set<string> nonTerminals) {
    int i = 0;
    for (const auto &nonTerminal:nonTerminals) {
        nonTerminalsIndices[nonTerminal] = i++;
    }
}

void ParsingTable::initEntriesTable(unsigned int terminalsSize, unsigned int nonTerminalsSize) {
    /*entriesTable.reserve(nonTerminalsSize);
    for (int i = 0; i < nonTerminalsSize; i++) {
        entriesTable[i].reserve(terminalsSize);
    }*/
    for(int i = 0; i < nonTerminalsSize; i++) {
        vector <vector<string>> w;
        entriesTable.push_back( w );
        for(int j = 0; j < (terminalsSize+1); j++){
            vector <string> v;
            entriesTable[i].push_back( v );
        }
    }
}



