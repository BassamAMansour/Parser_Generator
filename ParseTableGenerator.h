//
// Created by Bassam on 4/18/2019.
//

#ifndef PARSER_GENERATOR_PARSETABLEGENERATOR_H
#define PARSER_GENERATOR_PARSETABLEGENERATOR_H


#include "models/CFG.h"
#include "models/ParsingTable.h"
#include <unordered_set>

using namespace std;

class ParseTableGenerator {
public:
    explicit ParseTableGenerator(const CFG &cfg);

    ParsingTable *getParsingTable() const;

private:
    CFG cfg;
    ParsingTable *parsingTable;
    unordered_map<string, vector<string> *> firstsMap;
    unordered_map<string, vector<string> *> followsMap;

    void generateParseTable();

    void computeFirsts();

    void computeFollows();

    void buildParseTable();

};


#endif //PARSER_GENERATOR_PARSETABLEGENERATOR_H
