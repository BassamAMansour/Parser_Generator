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

    for (const auto &nonTerminal:cfg.nonTerminals) {
        computeFirsts(nonTerminal);
    }
}

void ParseTableGenerator::computeFirsts(string nonTerminal) {

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
                computeFirsts(token);
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

            int targetNonTerminalIndex = std::distance(production.begin(), targetNonTerminalIterator);

            if (targetNonTerminalIndex < production.size() - 1 &&
                isTerminal(production[targetNonTerminalIndex + 1])) {

                followsMap[targetNonTerminal]->insert(production[targetNonTerminalIndex + 1]);

            } else if ((targetNonTerminalIndex < production.size() - 1 &&
                        hasEpsilonFirstOnly(production[targetNonTerminalIndex + 1]))
                       || targetNonTerminalIndex == production.size() - 1) {

                if (followsMap.find(nonTerminal) != followsMap.end())
                    followsMap[targetNonTerminal]->insert(followsMap[nonTerminal]->begin(),
                                                          followsMap[nonTerminal]->end());

                followsMap[nonTerminal] = followsMap[targetNonTerminal];

            } else { //next token that is non-terminal has other than epsilon in its firsts
                followsMap[targetNonTerminal]->insert(firstsMap[production[targetNonTerminalIndex + 1]]->begin(),
                                                      firstsMap[production[targetNonTerminalIndex + 1]]->end());
            }
        }
    }

    followsMap[targetNonTerminal]->erase(followsMap[targetNonTerminal]->find(string(1, CFG::EPSILON)));

}

void ParseTableGenerator::buildParseTable() {
    int counter=0;

    for (auto &nonTerminal:cfg.nonTerminals) {
        set<string> *firsts = firstsMap[nonTerminal];
        set<string> *follows = followsMap[nonTerminal];
        int nonIndex=parsingTable->nonTerminalsIndices.at(nonTerminal);
        if(isFirst(string(1,CFG::EPSILON))){
                if(isFollow(string(1,ParsingTable::END_OF_TOKENS))){
                    //CASE 3
                    int endSign = parsingTable->terminalsIndices.at(string(1,ParsingTable::END_OF_TOKENS));
                    parsingTable->entriesTable[nonIndex][endSign]=cfg.productions.at(nonTerminal).productions[counter];


                }else{
                    //CASE 2
                    for (const auto &follow:followsMap[nonTerminal]) {
                        int terminalIndexFollow = parsingTable->terminalsIndices.at(follow);
                        parsingTable->entriesTable[nonIndex][terminalIndexFollow]=cfg.productions.at(nonTerminal).productions[counter];
                        counter++;
                    }
                }

            }else{
                //CASE 1
                for (const auto &first:firstsMap[nonTerminal]) {
                    int terminalIndexFirst = parsingTable->terminalsIndices.at(first);
                    parsingTable->entriesTable[nonIndex][terminalIndexFirst]=cfg.productions.at(nonTerminal).productions[counter];
                    counter++;
                }
            }
            counter=0;
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
    stack<string> * stack1 = new stack<string>;
    input.push_back(ParsingTable::END_OF_TOKENS);//add endof token to indicate the end of the input string
    int ptr=0;//arrow on the current char in the input string
    while(true){
        if(stack1->top()==string(1,ParsingTable::END_OF_TOKENS)&&input.at(ptr)==ParsingTable::END_OF_TOKENS){
            cout<<"Successful the input is accepted"<<endl;
            break;
        }

        if(stack1->empty()&&input.at(ptr)!=ParsingTable::END_OF_TOKENS){
            cout<<" ERROR Found compilation error at element : "<<input.at(ptr)<<endl;
            break;
        }
        if(input.at(ptr)==ParsingTable::END_OF_TOKENS&&(!stack1->empty())){
            cout<<"string accepted and all Non-Terminals go to Epsilon"<<endl;
            break;
        }
        //TODO SHARAF

    }

}

bool ParseTableGenerator::isFirst(const string &token) {
    return firstsMap.find(token) != firstsMap.end();
}

bool ParseTableGenerator::isFollow(const string &token) {
    return followsMap.find(token) != followsMap.end();
}



