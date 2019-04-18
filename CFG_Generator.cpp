//
// Created by Bassam on 4/18/2019.
//

#include "CFG_Generator.h"

CFG_Generator::CFG_Generator(const string &language) : language(language) { startCFGBuilding(); }

void CFG_Generator::startCFGBuilding() {
//TODO:Implement
}

const CFG &CFG_Generator::getCfg() const {
    return cfg;
}