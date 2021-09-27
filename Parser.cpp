#include "Parser.h"

Parser::Parser() {
    index = 0;
}

void Parser::PerformParse(std::vector<Token*> tokenList) {

    ParserHelper::DatalogProgram(tokenList, index);

}
