#ifndef PROJECT1_STARTER_CODE_PARSERHELPER_H
#define PROJECT1_STARTER_CODE_PARSERHELPER_H
#include "Token.h"
#include "DatalogProgram.h"
#include "Parameter.h"
#include "Predicate.h"
#include <vector>

class ParserHelper {
public:
    static void DatalogProgram(std::vector<Token*> tokenList, int index, DatalogProgram* myProg);
    static void Match(Token* token, TokenType matchType, int& index);
    static Predicate* Scheme(std::vector<Token*> tokenList, int& index);
    static void IdList(std::vector<Token*> tokenList, int& index, Predicate* newPred);
    //static void IdList(std::vector<Token*> tokenList, int& index); // overloaded function for testing
    static void SchemeList(std::vector<Token*> tokenList, int& index, class DatalogProgram* myProg);
    static void FactList(std::vector<Token*> tokenList, int& index, class DatalogProgram* myProg);
    static Predicate* Fact(std::vector<Token*> tokenList, int& index, class DatalogProgram* myProg);
    static void StringList(std::vector<Token*> tokenList, int& index, class Predicate* newPred, class DatalogProgram* myProg);
    //static void StringList(std::vector<Token*> tokenList, int& index); // overloaded function for testing
    static void RuleList(std::vector<Token*> tokenList, int& index, class DatalogProgram* myProg);
    static Rule* Rule(std::vector<Token*> tokenList, int& index);
    static Predicate* HeadPredicate(std::vector<Token*> tokenList, int& index);
    static Predicate* Predicate(std::vector<Token*> tokenList, int& index);
    static Parameter* Parameter(std::vector<Token*> tokenList, int& index);
    static void ParameterList(std::vector<Token*> tokenList, int& index, class Predicate* newPred);
    //static void ParameterList(std::vector<Token*> tokenList, int& index); // overloaded function for testing
    static void PredicateList(std::vector<Token*> tokenList, int& index, class Rule* newRule);
    static class Predicate* Query(std::vector<Token*> tokenList, int& index);
    static void QueryList(std::vector<Token*> tokenList, int& index, class DatalogProgram* myProg);

};

#endif //PROJECT1_STARTER_CODE_PARSERHELPER_H

/* TODO: match the terminals in the spot
         * 2. Make this function work
         * throw exception if it doesn't match
         * 3. create a method for every nonterminal
         * 4. Make a class for the data structures
         * 5. -> Create an object for the data structure and add it to the parser
         * 6. Figure out what this domain thing is
         *
         * Finish the rules nonterminals
         * Figure out the domain thing*/
