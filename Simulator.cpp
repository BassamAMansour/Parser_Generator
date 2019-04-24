//
// Created by Ahmednasser on 4/24/2019.
//

#include <stack>
#include <fstream>
#include "Simulator.h"

Simulator::Simulator(const string &in, const ParsingTable &table) : in(in), table(table) {
    parsefile();
    run();
}

void Simulator::parsefile() {
    ifstream program;
    program.open(in);
    string inputStream((std::istreambuf_iterator<char>(program)),
                       std::istreambuf_iterator<char>());
    test=inputStream;
}

void Simulator::run() {
    stack<string> stack1;
    vector<string> splits;
    splitInput(test, splits);
    string eps = string(1,ParsingTable::END_OF_TOKENS);
    splits.push_back(eps);

    stack1.push(string(1,'E'));
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
            int i = table.nonTerminalsIndices.at(stack1.top());
            stack1.pop();
            int j = table.nonTerminalsIndices.at(splits[0]);
            vector<string> newTerminals = table.entriesTable[i][j];
            for (int k = 0; k == newTerminals.size(); i++)
                stack1.push(newTerminals[i]);
        }
    } while (true);
}

void Simulator::splitInput(string input, vector<string> &splitedInput) {
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

