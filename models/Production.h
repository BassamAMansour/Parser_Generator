//
// Created by Bassam on 4/18/2019.
//

#ifndef PARSER_GENERATOR_PRODUCTION_H
#define PARSER_GENERATOR_PRODUCTION_H

#include <string>
#include <vector>

using namespace std;

class Production {

public:
    Production(vector<vector<string>> vector);

    Production();

    string name;
    /**
     * Each non-terminal produces a vector of productions.
     * Each production is a vector of concatenated terminals and non-terminals.
     * The outer vector is for the productions and the inner vector is for the terminals/non-terminals inside each production.
     * */
    vector<vector<string>> productions;

};


#endif //PARSER_GENERATOR_PRODUCTION_H
