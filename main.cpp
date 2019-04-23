#include <iostream>
#include <fstream>
#include "CFG_Generator.h"
#include "ParseTableGenerator.h"

int main() {
    string language = "../testFiles/test.txt";
    CFG_Generator cfgGenerator(language);
    CFG cfg = cfgGenerator.getCfg();

    ParsingTable *parsingTable = ParseTableGenerator(cfg).getParsingTable();

    //TODO: Do something useful with that parsing table... XD

    return 0;
}