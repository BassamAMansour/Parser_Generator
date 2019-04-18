//
// Created by Bassam on 4/18/2019.
//

#ifndef PARSER_GENERATOR_CFG_GENERATOR_H
#define PARSER_GENERATOR_CFG_GENERATOR_H

#include <string>
#include "models/CFG.h"

using namespace std;

class CFG_Generator {

public:
    explicit CFG_Generator(const string &language);
    const CFG &getCfg() const;

private:
    string language;
    CFG cfg;

    void startCFGBuilding();
};


#endif //PARSER_GENERATOR_CFG_GENERATOR_H
