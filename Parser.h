#ifndef PROJECT1_STARTER_CODE_PARSER_H
#define PROJECT1_STARTER_CODE_PARSER_H
#include <vector>
#include "Lexer.h"
#include "DatalogProgram.h"
#include "ParserHelper.h"

class Parser {
private:
    int index;
    DatalogProgram myProg;

public:
    Parser();

    DatalogProgram* PerformParse(std::vector<Token*> tokenList);

};

#endif //PROJECT1_STARTER_CODE_PARSER_H
