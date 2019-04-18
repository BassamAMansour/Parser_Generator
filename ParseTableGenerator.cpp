//
// Created by Bassam on 4/18/2019.
//

#include "ParseTableGenerator.h"

ParseTableGenerator::ParseTableGenerator(const CFG &cfg) : cfg(cfg) {

    parsingTable = new ParsingTable(cfg.terminals, cfg.nonTerminals);
    generateParseTable();
}

void ParseTableGenerator::generateParseTable() {

    computeFirsts();
    computeFollows();
    buildParseTable();
}

void ParseTableGenerator::computeFirsts() {

    for (const auto &nonTerminal:cfg.nonTerminals) {
        computeFirsts(nonTerminal);
    }
}

void ParseTableGenerator::computeFirsts(string nonTerminal) {

    Production productions = cfg.productions[nonTerminal];

    for (const auto &production:productions.productions) {

        if (production.empty()) continue;

        if (production.size() == 1 && production[0] == string(1, CFG::EPSILON)) {
            firstsMap[nonTerminal]->insert(string(1, CFG::EPSILON));
        } else if (isTerminal(production[0])) {
            firstsMap[nonTerminal]->insert(production[0]);
        } else {
            for (const auto &token:production) {
                //TODO:Implement
            }
        }
    }
}

void ParseTableGenerator::computeFollows() {
//TODO:Implement
}

void ParseTableGenerator::buildParseTable() {
//TODO:Implement
}

ParsingTable *ParseTableGenerator::getParsingTable() const {
    return parsingTable;
}

bool ParseTableGenerator::isTerminal(const basic_string<char> &token) {
    return cfg.terminals.find(token) != cfg.terminals.end();
}


