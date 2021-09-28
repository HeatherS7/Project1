#include "Parser.h"

Parser::Parser() {
    index = 0;
}

DatalogProgram* Parser::PerformParse(std::vector<Token*> tokenList) {
    DatalogProgram* myProg = new DatalogProgram();
    ParserHelper::DatalogProgram(tokenList, index, myProg);
    return myProg;

}
