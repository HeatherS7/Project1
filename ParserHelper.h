#ifndef PROJECT1_STARTER_CODE_PARSERHELPER_H
#define PROJECT1_STARTER_CODE_PARSERHELPER_H
#include "Token.h"
#include <vector>

class ParserHelper {
public:
    static void DatalogProgram(std::vector<Token*> tokenList, int index);
    static void Match(Token* token, TokenType matchType, int& index);
    static void Scheme(std::vector<Token*> tokenList, int& index);
    static void IdList(std::vector<Token*> tokenList, int& index);
    static void SchemeList(std::vector<Token*> tokenList, int& index);
    static void FactList(std::vector<Token*> tokenList, int& index);
    static void Fact(std::vector<Token*> tokenList, int& index);
    static void StringList(std::vector<Token*> tokenList, int& index);
    static void RuleList(std::vector<Token*> tokenList, int& index);
    static void Rule(std::vector<Token*> tokenList, int& index);
    static void HeadPredicate(std::vector<Token*> tokenList, int& index);
    static void Predicate(std::vector<Token*> tokenList, int& index);
    static void Parameter(std::vector<Token*> tokenList, int& index);
    static void ParameterList(std::vector<Token*> tokenList, int& index);
    static void PredicateList(std::vector<Token*> tokenList, int& index);
    static void Query(std::vector<Token*> tokenList, int& index);
    static void QueryList(std::vector<Token*> tokenList, int& index);

};

#endif //PROJECT1_STARTER_CODE_PARSERHELPER_H

/* TODO: match the terminals in the spot
         * 2. Make this function work
         * throw exception if it doesn't match
         * 3. create a method for every nonterminal
         * 4. Make a class for the data structures
         * 5. Create an object for the data structure and add it to the parser*/
