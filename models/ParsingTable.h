//
// Created by Bassam on 4/18/2019.
//

#ifndef PARSER_GENERATOR_PARSINGTABLE_H
#define PARSER_GENERATOR_PARSINGTABLE_H

#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include "Production.h"

using namespace std;

class ParsingTable {
public:
    static const char END_OF_TOKENS = '$';

    ParsingTable(const set<string> &terminals, const set<string> &nonTerminals);

    /**
     * A table made for the transitions of a terminal on a given non-terminal.
     * The rows are for the non-terminals and the columns are for the terminals.
     * Each table entry is a vector that contains the tokens of a production. (can use a Production datatype)
     * For a table entry with empty vector, it's considered an invalid transition.
     * */
    vector<vector<vector<string>>> entriesTable;
    unordered_map<string, int> terminalsIndices;
    unordered_map<string, int> nonTerminalsIndices;

    void initTerminalsIndices(set<string> terminals);

    void initNonTerminalsIndices(set<string> nonTerminals);

    void initEntriesTable(unsigned int terminalsSize, unsigned int nonTerminalsSize);
};


#endif //PARSER_GENERATOR_PARSINGTABLE_H
