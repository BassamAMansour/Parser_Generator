#include <iostream>
#include "CFG_Generator.h"
#include "ParseTableGenerator.h"
#include "Simulator.h"

int main() {
    string language = "../tests/grammar modified.txt";
    string input = "../tests/test1.txt";
    CFG_Generator cfgGenerator(language);
    const CFG &cfg = cfgGenerator.getCfg();

    ParsingTable *parsingTable = ParseTableGenerator(cfg).getParsingTable();
    Simulator s (input,*parsingTable);
    //PRINTING TABLE
    /*for (int i = 0; i < (int) parsingTable->entriesTable.size(); ++i) {
        for (int j = 0; j < (int) parsingTable->entriesTable[i].size(); ++j) {
            cout<<i<<","<<j<<" : "<<endl;
            for (int k = 0; k < (int) parsingTable->entriesTable[i][j].size(); ++k) {
                cout<<parsingTable->entriesTable[i][j][k]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }*/

    //TODO: Do something useful with that parsing table... XD

    return 0;
}