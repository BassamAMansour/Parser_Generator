//
// Created by Bassam on 4/18/2019.
//

#include "CFG_Generator.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <map>

CFG_Generator::CFG_Generator(string x): cfg(){
    string line;
    ifstream myfile;
    myfile.open(x);
    if (myfile.is_open()) {
        while (!myfile.eof()) {
            getline(myfile, line);
            fileLines.push_back(line);
        }
        startCFGBuilding();
    } else {
        cout << "Was unable to open the file" << endl;
    }
}

void CFG_Generator::startCFGBuilding() {

    rules = getRules();
    cfg = produceCFG();
    if(rules.size() == 0){
        return;
    } else if(rules[0].size() < 3){
        cout << "error in first line formatting" << endl;
        return;
    }
    cfg.startState = rules[0][1];
}

const CFG &CFG_Generator::getCfg() const {
    return cfg;
}

vector<vector<string>> CFG_Generator::getRules() {
    vector<vector<string>> rules;
    char lookAhead;
    vector<string> tmp;
    for(int i = 0; i < fileLines.size(); i++){
        if(i < fileLines.size() - 1){
            lookAhead = fileLines[i + 1][0];
        } else{
            lookAhead = '#';
        }
        vector<string> tokens;
        tokens = split (fileLines[i]);
        for(int i = 0; i < tokens.size(); i ++){
            tmp.push_back(tokens[i]);
        }
        if(lookAhead == '#'){
            rules.push_back(tmp);
            tmp = *new vector<string>;
        }
    }
    return rules;
}

CFG CFG_Generator::produceCFG() {
    unordered_map<string, Production> productions;
    unordered_set<string> terminals;
    unordered_set<string> nonTerminals;

    for(int i = 0; i < rules.size(); i++){
        string keyNonTerminal = rules[i][1];
        nonTerminals.insert(keyNonTerminal);
        vector<vector<string>> rhsProduction;
        vector<string> accVector;
        for(int j = 3; j < rules[i].size(); j++){
            string element = rules[i][j];
            if(element[0] == *"‘" || element[0] == *"'"){
                element.erase(0, 1);
                element.erase(element.size() - 1);
                terminals.insert(element);
            } else if(element == "|"){
                rhsProduction.push_back(accVector);
                accVector = *new vector<string>;
                continue;
            } else if(element == "\L" || element == "\\L"){
//                string test = string(1, CFG::EPSILON);
                accVector.push_back("\0");
                continue;
            } else{
                nonTerminals.insert(element);
            }
            accVector.push_back(element);
        }
        rhsProduction.push_back(accVector);
        accVector = *new vector<string>;
        Production production(rhsProduction);
        productions.insert({keyNonTerminal, production});
    }
    return CFG(terminals, nonTerminals, productions);
}

vector<string> CFG_Generator::split(string line) {
    vector<string> result;
    string accumlator = "";
    for(int i = 0; i < line.size() ; i++){
        if(line[i] == ' '){
            result.push_back(accumlator);
            accumlator = "";
        }else{
            accumlator += line[i];
        }
    }
    result.push_back(accumlator);
    return result;
}
