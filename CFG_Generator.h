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
    explicit CFG_Generator(string language);
    const CFG &getCfg() const;

private:
    string language;
    vector<string> fileLines;
    CFG cfg;
    vector<vector<string>> rules;

    void startCFGBuilding();
    void startCFGBuildingssss();

    vector<vector<string>> getRules();

    CFG produceCFG();

    vector<string> split(string line);
};


#endif //PARSER_GENERATOR_CFG_GENERATOR_H
