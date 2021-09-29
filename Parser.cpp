#include "Parser.h"

Parser::Parser() {
    index = 0;
    //DatalogProgram* myProg = new DatalogProgram();
}
Parser::Parser(DatalogProgram* theProg) {
    index = 0;
    myProg = theProg;
}
Parser::~Parser() {
    //delete myProg;
}

DatalogProgram* Parser::PerformParse(std::vector<Token*> tokenList) {
    DatalogProgramNonTerminal(tokenList);
    return myProg;

}

void Parser::DatalogProgramNonTerminal(std::vector<Token *> tokenList) {
    /* datalogProgram	->	SCHEMES COLON scheme schemeList FACTS
     * COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF*/
    if (tokenList.size()<=0) {
        throw std::exception();
    }
    Match(tokenList.at(index), TokenType::SCHEMES); // Match SCHEME
    Match(tokenList.at(index),TokenType::COLON); // Match COLON
    myProg->AddScheme((Scheme(tokenList))); // Call scheme non-terminal
    SchemeList(tokenList); // Call schemeList non-terminal
    Match(tokenList.at(index), TokenType::FACTS); // Match FACTS
    Match(tokenList.at(index), TokenType::COLON); // Match COLON
    FactList(tokenList); // Call factList non-terminal
    Match(tokenList.at(index), TokenType::RULES); // Match RULES
    Match(tokenList.at(index), TokenType::COLON); // Match COLON
    RuleList(tokenList); // Call ruleList non-terminal
    Match(tokenList.at(index), TokenType::QUERIES); // Match QUERIES
    Match(tokenList.at(index), TokenType::COLON); // Match COLON
    myProg->AddQuery(Query(tokenList)); // Call query non-terminal
    QueryList(tokenList); // Call queryList non-terminal
    Match(tokenList.at(index), TokenType::END_OF_FILE); // Match EOF



}

void Parser::Match(Token* token, TokenType matchType) {
    if (token->GetTokenType() == matchType) {
        index++;
    }
    else {
        throw token;
    }
}

Predicate* Parser::Scheme(std::vector<Token*> tokenList) {
    /* scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN*/
    Match(tokenList.at(index), TokenType::ID); // Match ID;
    class Predicate* schemePred = new class Predicate(tokenList.at(index-1)->GetTokenDescription());
    Match(tokenList.at(index), TokenType::LEFT_PAREN); // Match LEFT_PAREN
    Match(tokenList.at(index), TokenType::ID); // Match ID
    schemePred->AddParameter(new class Parameter(tokenList.at(index-1)->GetTokenDescription()));
    IdList(tokenList, schemePred); // Calls the idList non-terminal
    Match(tokenList.at(index), TokenType::RIGHT_PAREN); // Match RIGHT_PAREN
    return schemePred;

}
void Parser::IdList(std::vector<Token *> tokenList, Predicate* newPred) {
    /*idList  	-> 	COMMA ID idList | lambda*/
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::COMMA) { // It's in the First set of idList, so take this route
        Match(tokenList.at(index), TokenType::COMMA); // Match COMMA
        Match(tokenList.at(index), TokenType::ID); // Match ID
        newPred->AddParameter(new class Parameter(tokenList.at(index-1)->GetTokenDescription()));
        IdList(tokenList, newPred);
    }
    else if (nextType == TokenType::RIGHT_PAREN) { // It's in the follow set of idList, so take this route
        return;
    }
    else {
        throw tokenList.at(index);
    }

}

void Parser::SchemeList(std::vector<Token *> tokenList) {
    /*schemeList -> scheme schemeList | lambda*/
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::ID) { // It's in the First set of schemeList, so take this route
        class Predicate* newPred = new class Predicate();
        newPred = Scheme(tokenList); // Call scheme non-terminal
        myProg->AddScheme(newPred);
        SchemeList(tokenList); // Call schemeList non-terminal
    }
    else if (nextType == TokenType::FACTS) { // It's in the follow set of schemeList, so take this route
        return;
    }
    else {
        throw tokenList.at(index);
    }

}

void Parser::FactList(std::vector<Token*> tokenList) {
    /* factList	-> fact factList | lambda*/
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::ID) { // It's in the First set of factList, so take this route
        myProg->AddFact(Fact(tokenList)); // call fact non-terminal
        FactList(tokenList); // call factList non-terminal again
    }
    else if (nextType == TokenType::RULES) { // It's in the follow set of factList, so take this route
        return;
    }
    else {
        throw tokenList.at(index);
    }

}

Predicate* Parser::Fact(std::vector<Token*> tokenList) {
    /* fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD*/
    Match(tokenList.at(index), TokenType::ID); // Match ID
    Predicate* factPred = new Predicate(tokenList.at(index-1)->GetTokenDescription());
    Match(tokenList.at(index), TokenType::LEFT_PAREN); // Match LEFT_PAREN
    Match(tokenList.at(index), TokenType::STRING); // Match STRING
    factPred->AddParameter(new Parameter(tokenList.at(index-1)->GetTokenDescription()));
    myProg->AddDomain(tokenList.at(index-1)->GetTokenDescription());
    StringList(tokenList, factPred); // Call stringList
    Match(tokenList.at(index), TokenType::RIGHT_PAREN); // Match RIGHT_PAREN
    Match(tokenList.at(index), TokenType::PERIOD); // Match PERIOD
    return factPred;

}

void Parser::StringList(std::vector<Token *> tokenList, Predicate* newPred) {
    /* stringList -> COMMA STRING stringList | lambda*/
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::COMMA) { // It's in the First set of stringList, so take this route
        Match(tokenList.at(index), TokenType::COMMA); // Match COMMA
        Match(tokenList.at(index), TokenType::STRING); // Match STRING
        newPred->AddParameter(new Parameter(tokenList.at(index-1)->GetTokenDescription()));
        myProg->AddDomain(tokenList.at(index-1)->GetTokenDescription());
        StringList(tokenList, newPred); // Call stringList again
    }
    else if (nextType == TokenType::RIGHT_PAREN) { // It's in the follow set of stringList, so take this route
        return;
    }
    else {
        throw tokenList.at(index);
    }
}

void Parser::RuleList(std::vector<Token *> tokenList) {
    /* ruleList	->	rule ruleList | lambda*/
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::ID) { // It's in the First set of ruleList, so take this route
        myProg->AddRule(RuleNonTerminal(tokenList)); // Call rule non-terminal
        RuleList(tokenList);
    }
    else if (nextType == TokenType::QUERIES) { // It's in the follow set of ruleList, so take this route
        return;
    }
    else {
        throw tokenList.at(index);
    }
}
Rule* Parser::RuleNonTerminal(std::vector<Token *> tokenList) {
    /* rule	-> headPredicate COLON_DASH predicate predicateList PERIOD*/
    Rule* newRule = new Rule();
    newRule->SetHeadPredicate(HeadPredicate(tokenList)); // Call headPredicate non-terminal
    Match(tokenList.at(index), TokenType::COLON_DASH); // Match COLON_DASH
    newRule->AddBodyPredicate(PredicateNonTerminal(tokenList)); // Call predicate
    PredicateList(tokenList, newRule); // Call predicateList
    Match(tokenList.at(index), TokenType::PERIOD); // Match PERIOD
    return newRule;
}
Predicate* Parser::HeadPredicate(std::vector<Token *> tokenList) {
    /* headPredicate ->	ID LEFT_PAREN ID idList RIGHT_PAREN */
    Match(tokenList.at(index), TokenType::ID); // Match ID
    class Predicate* hPred = new Predicate(tokenList.at(index-1)->GetTokenDescription());
    Match(tokenList.at(index), TokenType::LEFT_PAREN); // Match LEFT_PAREN
    Match(tokenList.at(index), TokenType::ID); // Match ID
    hPred->AddParameter(new Parameter(tokenList.at(index-1)->GetTokenDescription()));
    IdList(tokenList, hPred); // Call idList non-terminal
    Match(tokenList.at(index), TokenType::RIGHT_PAREN); // Match RIGHT_PAREN
    return hPred;
}
Predicate* Parser::PredicateNonTerminal(std::vector<Token *> tokenList) {
    /* predicate ->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN */
    Match(tokenList.at(index), TokenType::ID); // Match ID
    Predicate* newPred = new Predicate(tokenList.at(index-1)->GetTokenDescription());
    Match(tokenList.at(index), TokenType::LEFT_PAREN); // Match LEFT_PAREN
    newPred->AddParameter(ParameterNonTerminal(tokenList));
    ParameterList(tokenList, newPred); // Call parameterList non-terminal
    Match(tokenList.at(index), TokenType::RIGHT_PAREN); // Match RIGHT_PAREN
    return newPred;
}
Parameter* Parser::ParameterNonTerminal(std::vector<Token *> tokenList) {
    /* parameter ->	STRING | ID*/
    if (tokenList.at(index)->GetTokenType() == TokenType::STRING) {
        Match(tokenList.at(index), TokenType::STRING);
    }
    else if (tokenList.at(index)->GetTokenType() == TokenType::ID) {
        Match(tokenList.at(index), TokenType::ID);
    }
    else {
        throw tokenList.at(index);
    }
    return new class Parameter(tokenList.at(index-1)->GetTokenDescription());
}
void Parser::ParameterList(std::vector<Token *> tokenList, Predicate* newPred) {
    /* parameterList -> COMMA parameter parameterList | lambda */
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::COMMA) { // It's in the First set of parameterList, so take this route
        Match(tokenList.at(index), TokenType::COMMA); // Match COMMA
        newPred->AddParameter(ParameterNonTerminal(tokenList));
        ParameterList(tokenList, newPred);
    }
    else if (nextType == TokenType::RIGHT_PAREN) { // It's in the follow set of parameterList, so take this route
        return;
    }
    else {
        throw tokenList.at(index);
    }
}
void Parser::PredicateList(std::vector<Token *> tokenList, Rule* newRule) {
    /* predicateList ->	COMMA predicate predicateList | lambda */
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::COMMA) { // It's in the First set of predicateList, so take this route
        Match(tokenList.at(index), TokenType::COMMA);
        newRule->AddBodyPredicate(PredicateNonTerminal(tokenList));
        PredicateList(tokenList, newRule);
    }
    else if (nextType == TokenType::PERIOD) { // It's in the follow set of predicateList, so take this route
        return;
    }
    else {
        throw tokenList.at(index);
    }
}
Predicate* Parser::Query(std::vector<Token *> tokenList) {
    /* query -> predicate Q_MARK */
    class Predicate* queryPred = PredicateNonTerminal(tokenList);
    Match(tokenList.at(index), TokenType::Q_MARK);
    return queryPred;

}
void Parser::QueryList(std::vector<Token *> tokenList) {
    /* queryList ->	query queryList | lambda */
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::ID) { // It's in the First set of queryList, so take this route
        myProg->AddQuery(Query(tokenList));
        QueryList(tokenList);
    }
    else if (nextType == TokenType::END_OF_FILE) { // It's in the follow set of queryList, so take this route
        return;
    }
    else {
        throw tokenList.at(index);
    }
}
