//
// Created by Bassam on 4/18/2019.
//

#ifndef PARSER_GENERATOR_PARSETABLEGENERATOR_H
#define PARSER_GENERATOR_PARSETABLEGENERATOR_H


#include "models/CFG.h"
#include "models/ParsingTable.h"
#include <set>

using namespace std;

class ParseTableGenerator {
public:
    explicit ParseTableGenerator(const CFG &cfg);

    ParsingTable *getParsingTable() const;

private:
    CFG cfg;
    ParsingTable *parsingTable;
    unordered_map<string, set<string> *> firstsMap;
    unordered_map<string, set<string> *> followsMap;

    void generateParseTable();

    void computeFirsts();

    void computeFollows();

    void computeFirsts(string nonTerminal, set<string> &computedFirsts);

    void computeFollows(string targetNonTerminal);

    void buildParseTable();

    bool isTerminal(const string &token);

    bool isNonTerminal(const string &token);

    bool hasEpsilonFirstOnly(const string &token);

    void runSimulation(string input);

    bool isFirst(const string &token);

    bool isFollow(const string &token);

    bool hasEpsilonInFirsts(const basic_string<char> &nonTerminal);

    void eraseEpsilonFromFollows(const string &nonTerminal);
};


#endif //PARSER_GENERATOR_PARSETABLEGENERATOR_H
