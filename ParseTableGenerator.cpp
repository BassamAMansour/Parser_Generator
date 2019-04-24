//
// Created by Bassam on 4/18/2019.
//

#include <algorithm>
#include <stack>
#include <iostream>
#include "ParseTableGenerator.h"

ParseTableGenerator::ParseTableGenerator(const CFG &cfg) : cfg(cfg) {

    parsingTable = new ParsingTable(cfg.terminals, cfg.nonTerminals);
    generateParseTable();
}

void ParseTableGenerator::generateParseTable() {
    computeFirsts();
    computeFollows();
    buildParseTable();
    // runSimulation();
}

void ParseTableGenerator::computeFirsts() {

    auto *computedFirsts = new set<string>();

    for (const auto &nonTerminal:cfg.nonTerminals) {
        computeFirsts(nonTerminal, *computedFirsts);
        computedFirsts->insert(nonTerminal);
    }
}

void ParseTableGenerator::computeFirsts(string nonTerminal, set<string> &computedFirsts) {

    if (computedFirsts.find(nonTerminal) != computedFirsts.end())
        return;

    Production productions = cfg.productions[nonTerminal];

    if (firstsMap.find(nonTerminal) == firstsMap.end()) firstsMap[nonTerminal] = new set<string>();

    for (const auto &production:productions.productions) {

        if (production.empty()) continue;

        if (production.size() == 1 && production[0] == string(1, CFG::EPSILON)) {
            firstsMap[nonTerminal]->insert(string(1, CFG::EPSILON));
        } else if (isTerminal(production[0])) {
            firstsMap[nonTerminal]->insert(production[0]);
        } else {
            bool nonEpsilonFirstFound = false;

            for (const auto &token:production) {
                computeFirsts(token, computedFirsts);
                if (!hasEpsilonFirstOnly(token)) {
                    firstsMap[nonTerminal]->insert(firstsMap[token]->begin(), firstsMap[token]->end());
                    nonEpsilonFirstFound = true;
                    break;
                }
            }

            if (!nonEpsilonFirstFound) firstsMap[nonTerminal]->insert(string(1, CFG::EPSILON));
        }
    }
}

void ParseTableGenerator::computeFollows() {

    auto *startStateFollows = new set<string>();
    startStateFollows->insert(string(1, ParsingTable::END_OF_TOKENS));

    followsMap[cfg.startState] = startStateFollows;

    for (const auto &nonTerminal:cfg.nonTerminals) {
        computeFollows(nonTerminal);
    }
}

void ParseTableGenerator::computeFollows(string targetNonTerminal) {

    if (followsMap.find(targetNonTerminal) == followsMap.end()) followsMap[targetNonTerminal] = new set<string>();

    for (const auto &nonTerminal:cfg.nonTerminals) {

        Production productions = cfg.productions[nonTerminal];

        for (const auto &production:productions.productions) {

            auto targetNonTerminalIterator = std::find(production.begin(), production.end(), targetNonTerminal);

            if (targetNonTerminalIterator == production.end()) continue;

            int maxIndex = production.size() - 1;
            int targetIndex = std::distance(production.begin(), targetNonTerminalIterator);

            string nextToken;
            if (targetIndex < maxIndex) nextToken = production[targetIndex + 1];

            if (targetIndex < maxIndex && isTerminal(nextToken)) {

                followsMap[targetNonTerminal]->insert(nextToken);

                continue;
            } else if (targetIndex < maxIndex && !hasEpsilonFirstOnly(nextToken)) {
                //next token that is non-terminal has other than epsilon in its firsts

                followsMap[targetNonTerminal]->insert(firstsMap[nextToken]->begin(), firstsMap[nextToken]->end());

                eraseEpsilonFromFollows(targetNonTerminal);
            }

            if ((targetIndex < maxIndex && hasEpsilonInFirsts(nextToken)) || targetIndex == maxIndex) {

                if (followsMap.find(nonTerminal) == followsMap.end()) computeFollows(nonTerminal);

                followsMap[targetNonTerminal]->insert(followsMap[nonTerminal]->begin(), followsMap[nonTerminal]->end());
            }
        }
    }
}

void ParseTableGenerator::buildParseTable() {
    int tableEntry=0;
    int counter = 0;
    for (auto &nonTerminal:cfg.nonTerminals) {
            set<string> *firsts = firstsMap[nonTerminal];
            set<string> *follows = followsMap[nonTerminal];
            vector<string> vecfirst;
            vector<string> vecfollow;
        for (set<string>::iterator it = firsts->begin(); it != firsts->end(); ++it) {
            vecfirst.push_back(*it);
        }
        for (set<string>::iterator it = follows->begin(); it != follows->end(); ++it) {
            vecfollow.push_back(*it);
        }
            int nonIndex = parsingTable->nonTerminalsIndices.at(nonTerminal);

            if(isFirst(nonTerminal)){
               // counter=0;
                vector<vector<string>> p1 = cfg.productions.at(nonTerminal).productions;
                for (set<string>::iterator it = firsts->begin(); it != firsts->end(); ++it) {
                    if(*it!=string(1,CFG::EPSILON)){
                        int terminalIndexFirst = parsingTable->terminalsIndices.at(*it);
                        tableEntry =getIndexofProduction(p1,*it);
                        parsingTable->entriesTable[nonIndex][terminalIndexFirst] = p1[tableEntry];
                      //  counter++;
                    }else{
                        for (set<string>::iterator it = follows->begin(); it != follows->end(); ++it) {
                            int terminalIndexFollow = parsingTable->terminalsIndices.at(*it);
                            tableEntry=getIndexofProduction(p1,string(1,CFG::EPSILON));
                            parsingTable->entriesTable[nonIndex][terminalIndexFollow] =p1[tableEntry];
                           // counter++;
                        }
                    }
                }

                }else{
                vector<vector<string>> p = cfg.productions.at(nonTerminal).productions;
                if(p.size()==firsts->size()){
                  //  counter=0;
                    for (set<string>::iterator it = firsts->begin(); it != firsts->end(); ++it) {
                        int terminalIndexFirst = parsingTable->terminalsIndices.at(*it);
                         tableEntry=getIndexofProduction(p,*it);
                        parsingTable->entriesTable[nonIndex][terminalIndexFirst] = p[tableEntry];
                      //  counter++;
                    }
                }else{
                    for (set<string>::iterator it = firsts->begin(); it != firsts->end(); ++it) {
                        int terminalIndexFirst = parsingTable->terminalsIndices.at(*it);
                        for(int i=0;i<p[0].size();i++){
                            // tableEntry=getIndexofProduction(p,*it);
                            parsingTable->entriesTable[nonIndex][terminalIndexFirst].push_back(p[0].at(i));
                        }// kanet 0
                    }
                }


            }
    }

}

ParsingTable *ParseTableGenerator::getParsingTable() const {
    return parsingTable;
}

bool ParseTableGenerator::isTerminal(const string &token) {
    return cfg.terminals.find(token) != cfg.terminals.end();
}

bool ParseTableGenerator::isNonTerminal(const string &token) {
    return cfg.nonTerminals.find(token) != cfg.nonTerminals.end();
}

bool ParseTableGenerator::hasEpsilonFirstOnly(const string &token) {
    return (firstsMap[token]->size() == 1 &&
            firstsMap[token]->find(string(1, CFG::EPSILON)) != firstsMap[token]->end());
}

void ParseTableGenerator::runSimulation(string input) {
    stack<string> stack1;
    vector<string> splits;
    splitInput(input, splits);
    string eps = string(1,ParsingTable::END_OF_TOKENS);
    splits.push_back(eps);

    //TODO stack1->push(first non terminal);
    stack1.push(eps);

    do {
        if(stack1.top() == eps && splits[0] == eps){
            cout<<"Successful the input is accepted"<<endl;
            break;
        }

        if(stack1.empty() && splits[0] != eps){
            cout<<" ERROR Found compilation error at element : "<< splits[0] << endl;
            break;
        }

        if(splits[0] == eps &&(!stack1.empty())){
            cout<<"string accepted and all Non-Terminals go to Epsilon"<<endl;
            break;
        }

        if (stack1.top() == splits[0]){
            stack1.pop();
            splits.erase(splits.begin());
            continue;
        } else {
            int i = parsingTable->nonTerminalsIndices.at(stack1.top());
            stack1.pop();
            int j = parsingTable->nonTerminalsIndices.at(splits[0]);
            vector<string> newTerminals = parsingTable->entriesTable[i][j];
            for (int k = 0; k == newTerminals.size(); i++)
                stack1.push(newTerminals[i]);
        }
    } while (true);
}

void ParseTableGenerator::splitInput (string input, vector<string> &splitedInput){
    int i = input.length() - 1, s;
    while (i < input.length() && input.at(i) == ' ') i--;
    string tmp = input.substr(0, i + 1);
    i = 0;
    while (i < tmp.length() && tmp.at(i) == ' ') i++;
    s = i;
    i = tmp.find(' ', i + 1);
    while (i != string::npos) {
        splitedInput.push_back(tmp.substr(s, i - s));
        while (i < tmp.length() && tmp.at(i) == ' ') i++;
        s = i;
        i = tmp.find(' ', i + 1);
    }
    if(s < tmp.length())
        splitedInput.push_back(input.substr(s, tmp.length() - s));
}

bool ParseTableGenerator::isFirst(const string &token) {
    return firstsMap[token]->find(string(1, CFG::EPSILON)) != firstsMap[token]->end();
}

bool ParseTableGenerator::isFollow(const string &token) {
    return followsMap[token]->find(string(1,ParsingTable::END_OF_TOKENS)) != followsMap[token]->end();
}

bool ParseTableGenerator::hasEpsilonInFirsts(const basic_string<char> &nonTerminal) {
    return firstsMap[nonTerminal]->find(string(1, CFG::EPSILON)) != firstsMap[nonTerminal]->end();
}

void ParseTableGenerator::eraseEpsilonFromFollows(const string &nonTerminal) {
    if (followsMap[nonTerminal]->find(string(1, CFG::EPSILON)) != followsMap[nonTerminal]->end())
        followsMap[nonTerminal]->erase(followsMap[nonTerminal]->find(string(1, CFG::EPSILON)));
}

int ParseTableGenerator::getIndexofProduction(vector<vector<string>> p,string token) {
    for(int i=0;i<p.size();i++){
        for(int j=0;j<p[i].size();j++){
            string temp =p[i][j];
            if(token.compare(temp)==0){
                return i;
            }
        }
    }
}
