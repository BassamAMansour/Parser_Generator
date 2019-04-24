//
// Created by Ahmednasser on 4/24/2019.
//

#include <stack>
#include <fstream>
#include "Simulator.h"

Simulator::Simulator(const string &in, const ParsingTable &table, string startState) : in(in), table(table),
                                                                                       startState(startState) {
    parsefile();
    run();
}

void Simulator::parsefile() {
    ifstream program;
    program.open(in);
    string line;
    string inputStream;
    while (getline(program, line)) {
        inputStream += line;
        inputStream += " ";
    }
    program.close();
    test = inputStream;
}

void Simulator::run() {
    vector<string> stack1;
    vector<string> splits;
    splitInput(test, splits);
    string eps = string(1, ParsingTable::END_OF_TOKENS);
    splits.push_back(eps);

    stack1.push_back(eps);
    stack1.push_back(startState);

    cout.width(20);
    cout << left;
    cout << "Stack";
    cout.width(20);
    cout << left;
    cout << "Input";
    cout.width(20);
    cout << left;
    cout << "Output";

    do {
        cout << endl;
        int len = 0;
        for (int l = 0; l < stack1.size(); ++l) {
            cout << stack1[l] << " ";
            len += stack1[l].length() + 1;
        }
        for (int l = len; l < 20; ++l)cout << " ";
        len = 0;
        for (int l = 0; l < splits.size(); ++l) {
            cout << splits[l] << " ";
            len += splits[l].length() + 1;
        }
        //end print stack + input

        if (stack1.back() == eps && splits[0] == eps) {
            for (int l = len; l < 20; ++l)cout << " ";
            cout << "accept";
            break;
        }

        if (stack1.empty() && splits[0] != eps) {
            for (int l = len; l < 20; ++l)cout << " ";
            cout << " ERROR Found compilation error at element : " << splits[0] << endl;
            break;
        }

//        if (splits[0] == eps && (!stack1.empty())) {
//            cout << "string accepted and all Non-Terminals go to Epsilon" << endl;
//            break;
//        }

        if (stack1.back() == splits[0]) {
            stack1.pop_back();
            splits.erase(splits.begin());
            continue;
        } else {
            auto itr = table.nonTerminalsIndices.find(stack1.back());
            if (itr == table.nonTerminalsIndices.end()) {
                for (int l = len; l < 20; ++l)cout << " ";
                cout << "Error matching: " << stack1.back() << endl;
                stack1.pop_back();
                continue;
            }
            int i = itr->second;
            itr = table.terminalsIndices.find(splits[0]);

            int j;
            if (itr == table.terminalsIndices.end()) {
                splits.erase(splits.begin());
                continue;
            } else {
                j = itr->second;
            }

            vector<string> newTerminals = table.entriesTable[i][j];

            if (newTerminals.empty()) {
                for (int l = len; l < 20; ++l)cout << " ";
                cout << "Error" << endl;
                splits.erase(splits.begin());
                continue;
            } else if (newTerminals[0] == "&") {
                for (int l = len; l < 20; ++l)cout << " ";
                cout << stack1.back() << "-> &";
                stack1.pop_back();
                continue;
            }

            for (int l = len; l < 20; ++l)cout << " ";
            cout << stack1.back() << "-> ";
            stack1.pop_back();
            for (int k = newTerminals.size() - 1; k >= 0; k--)
                stack1.push_back(newTerminals[k]);

            for (int l = 0; l < newTerminals.size(); ++l)
                cout << newTerminals[l] << " ";
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
    if (s < tmp.length())
        splitedInput.push_back(input.substr(s, tmp.length() - s));

}

