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
//TODO:Implement
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
