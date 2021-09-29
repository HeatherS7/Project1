#ifndef PROJECT1_STARTER_CODE_PARSER_H
#define PROJECT1_STARTER_CODE_PARSER_H
#include <vector>
#include "Lexer.h"
#include "DatalogProgram.h"

class Parser {
private:
    int index;
    DatalogProgram* myProg;

    void DatalogProgramNonTerminal(std::vector<Token*> tokenList);
    void Match(Token* token, TokenType matchType);
    Predicate* Scheme(std::vector<Token*> tokenList);
    void IdList(std::vector<Token*> tokenList, Predicate* newPred);
    void SchemeList(std::vector<Token*> tokenList);
    void FactList(std::vector<Token*> tokenList);
    Predicate* Fact(std::vector<Token*> tokenList);
    void StringList(std::vector<Token*> tokenList, Predicate* newPred);
    void RuleList(std::vector<Token*> tokenList);
    Rule* RuleNonTerminal(std::vector<Token*> tokenList);
    Predicate* HeadPredicate(std::vector<Token*> tokenList);
    Predicate* PredicateNonTerminal(std::vector<Token*> tokenList);
    Parameter* ParameterNonTerminal(std::vector<Token*> tokenList);
    void ParameterList(std::vector<Token*> tokenList, Predicate* newPred);
    void PredicateList(std::vector<Token*> tokenList, Rule* newRule);
    Predicate* Query(std::vector<Token*> tokenList);
    void QueryList(std::vector<Token*> tokenList);

public:
    Parser();
    Parser(DatalogProgram* theProg);
    ~Parser();

    DatalogProgram* PerformParse(std::vector<Token*> tokenList);

};

#endif //PROJECT1_STARTER_CODE_PARSER_H

/* TODO:
 * Refactor code--get rid of ParserHelper so methods are no longer static
 * Possibly rename some of the methods that also have classes
 * */
