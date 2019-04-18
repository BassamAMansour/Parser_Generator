#include <iostream>
#include "CFG_Generator.h"
#include "ParseTableGenerator.h"

int main() {

    //TODO: Get CFG from text file
    string language = "Language";

    ParsingTable *parsingTable = ParseTableGenerator(CFG_Generator(language).getCfg()).getParsingTable();

    //TODO: Do something useful with that parsing table... XD

    return 0;
}