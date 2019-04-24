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
    string line;
    string inputStream;
    while (getline(program, line)){
        inputStream+=line;
        inputStream+= " ";
    }
    program.close();
    test = inputStream;
}

void Simulator::run() {
    stack<string> stack1;
    vector<string> splits;
    splitInput(test, splits);
    string eps = string(1,ParsingTable::END_OF_TOKENS);
    splits.push_back(eps);

    stack1.push(eps);
    stack1.push(string(1,'E'));

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
            auto itr = table.nonTerminalsIndices.find(stack1.top());
            if (itr == table.nonTerminalsIndices.end()){
                cout<<"Error matching: " << stack1.top()<<endl;
                stack1.pop();
                continue;
            }
            int i = itr->second;
            itr = table.terminalsIndices.find(splits[0]);

            int j;
            if (itr == table.terminalsIndices.end()){
                splits.erase(splits.begin());
                continue;
            } else {
                j = itr->second;
            }

            vector<string> newTerminals = table.entriesTable[i][j];

            if (newTerminals.empty()){
                cout<<"Error"<<endl;
                splits.erase(splits.begin());
                continue;
            } else if (newTerminals[0] == eps) {
                stack1.pop();
                continue;
            }

            stack1.pop();
            for (int k = 0; k < newTerminals.size(); k++)
                stack1.push(newTerminals[k]);
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

