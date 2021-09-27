#include "ParserHelper.h"

void ParserHelper::DatalogProgram(std::vector<Token*> tokenList, int index) {
    /* datalogProgram	->	SCHEMES COLON scheme schemeList FACTS
     * COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF*/
    if (tokenList.size()<=0) {
        throw std::exception();
    }
    Match(tokenList.at(index), TokenType::SCHEMES, index); // Match SCHEME
    Match(tokenList.at(index),TokenType::COLON, index); // Match COLON
    Scheme(tokenList, index); // Call scheme non-terminal
    SchemeList(tokenList, index); // Call schemeList non-terminal
    Match(tokenList.at(index), TokenType::FACTS, index); // Match FACTS
    Match(tokenList.at(index), TokenType::COLON, index); // Match COLON
    FactList(tokenList, index); // Call factList non-terminal
    Match(tokenList.at(index), TokenType::RULES, index); // Match RULES
    Match(tokenList.at(index), TokenType::COLON, index); // Match COLON
    RuleList(tokenList, index); // Call ruleList non-terminal
    Match(tokenList.at(index), TokenType::QUERIES, index); // Match QUERIES
    Match(tokenList.at(index), TokenType::COLON, index); // Match COLON
    Query(tokenList, index); // Call query non-terminal
    QueryList(tokenList, index); // Call queryList non-terminal
    Match(tokenList.at(index), TokenType::END_OF_FILE, index); // Match EOF


}

void ParserHelper::Match(Token* token, TokenType matchType, int& index) {
    if (token->GetTokenType() == matchType) {
        index++;
    }
    else {
        throw std::exception();
    }
}

void ParserHelper::Scheme(std::vector<Token*> tokenList, int& index) {
    /* scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN*/
    Match(tokenList.at(index), TokenType::ID, index); // Match ID
    Match(tokenList.at(index), TokenType::LEFT_PAREN, index); // Match LEFT_PAREN
    Match(tokenList.at(index), TokenType::ID, index); // Match ID
    IdList(tokenList, index); // Calls the idList non-terminal
    Match(tokenList.at(index), TokenType::RIGHT_PAREN,index); // Match RIGHT_PAREN


}
void ParserHelper::IdList(std::vector<Token *> tokenList, int &index) {
    /*idList  	-> 	COMMA ID idList | lambda*/
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::COMMA) { // It's in the First set of idList, so take this route
        Match(tokenList.at(index), TokenType::COMMA, index); // Match COMMA
        Match(tokenList.at(index), TokenType::ID, index); // Match ID
        IdList(tokenList, index);
    }
    else if (nextType == TokenType::RIGHT_PAREN) { // It's in the follow set of idList, so take this route
        return;
    }
    else {
        throw std::exception();
    }

}

void ParserHelper::SchemeList(std::vector<Token *> tokenList, int &index) {
    /*schemeList -> scheme schemeList | lambda*/
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::ID) { // It's in the First set of schemeList, so take this route
        Scheme(tokenList, index); // Call scheme non-terminal
        SchemeList(tokenList, index); // Call schemeList non-terminal
    }
    else if (nextType == TokenType::FACTS) { // It's in the follow set of schemeList, so take this route
        return;
    }
    else {
        throw std::exception();
    }

}

void ParserHelper::FactList(std::vector<Token*> tokenList, int &index) {
    /* factList	-> fact factList | lambda*/
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::ID) { // It's in the First set of factList, so take this route
        Fact(tokenList, index); // call fact non-terminal
        FactList(tokenList, index); // call factList non-terminal again
    }
    else if (nextType == TokenType::RULES) { // It's in the follow set of factList, so take this route
        return;
    }
    else {
        throw std::exception();
    }

}

void ParserHelper::Fact(std::vector<Token*> tokenList, int &index) {
    /* fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD*/
    Match(tokenList.at(index), TokenType::ID, index); // Match ID
    Match(tokenList.at(index), TokenType::LEFT_PAREN, index); // Match LEFT_PAREN
    Match(tokenList.at(index), TokenType::STRING, index); // Match STRING
    StringList(tokenList, index); // Call stringList
    Match(tokenList.at(index), TokenType::RIGHT_PAREN, index); // Match RIGHT_PAREN
    Match(tokenList.at(index), TokenType::PERIOD, index); // Match PERIOD

}

void ParserHelper::StringList(std::vector<Token *> tokenList, int &index) {
    /* stringList -> COMMA STRING stringList | lambda*/
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::COMMA) { // It's in the First set of stringList, so take this route
        Match(tokenList.at(index), TokenType::COMMA, index); // Match COMMA
        Match(tokenList.at(index), TokenType::STRING, index); // Match STRING
        StringList(tokenList, index); // Call stringList again
    }
    else if (nextType == TokenType::RIGHT_PAREN) { // It's in the follow set of stringList, so take this route
        return;
    }
    else {
        throw std::exception();
    }
}

void ParserHelper::RuleList(std::vector<Token *> tokenList, int &index) {
    /* ruleList	->	rule ruleList | lambda*/
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::ID) { // It's in the First set of ruleList, so take this route
        Rule(tokenList, index); // Call rule non-terminal
        RuleList(tokenList, index);
    }
    else if (nextType == TokenType::QUERIES) { // It's in the follow set of ruleList, so take this route
        return;
    }
    else {
        throw std::exception();
    }
}
void ParserHelper::Rule(std::vector<Token *> tokenList, int &index) {
    /* rule	-> headPredicate COLON_DASH predicate predicateList PERIOD*/
    HeadPredicate(tokenList, index); // Call headPredicate non-terminal
    Match(tokenList.at(index), TokenType::COLON_DASH, index); // Match COLON_DASH
    Predicate(tokenList, index); // Call predicate
    PredicateList(tokenList, index); // Call predicateList
    Match(tokenList.at(index), TokenType::PERIOD, index); // Match PERIOD
}
void ParserHelper::HeadPredicate(std::vector<Token *> tokenList, int &index) {
    /* headPredicate ->	ID LEFT_PAREN ID idList RIGHT_PAREN */
    Match(tokenList.at(index), TokenType::ID, index); // Match ID
    Match(tokenList.at(index), TokenType::LEFT_PAREN, index); // Match LEFT_PAREN
    Match(tokenList.at(index), TokenType::ID, index); // Match ID
    IdList(tokenList, index); // Call idList non-terminal
    Match(tokenList.at(index), TokenType::RIGHT_PAREN, index); // Match RIGHT_PAREN
}
void ParserHelper::Predicate(std::vector<Token *> tokenList, int &index) {
    /* predicate ->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN */
    Match(tokenList.at(index), TokenType::ID, index); // Match ID
    Match(tokenList.at(index), TokenType::LEFT_PAREN, index); // Match LEFT_PAREN
    Parameter(tokenList, index); // Call parameter non-terminal
    ParameterList(tokenList, index); // Call parameterList non-terminal
    Match(tokenList.at(index), TokenType::RIGHT_PAREN, index); // Match RIGHT_PAREN
}
void ParserHelper::Parameter(std::vector<Token *> tokenList, int &index) {
    /* parameter ->	STRING | ID*/
    if (tokenList.at(index)->GetTokenType() == TokenType::STRING) {
        Match(tokenList.at(index), TokenType::STRING, index);
    }
    else if (tokenList.at(index)->GetTokenType() == TokenType::ID) {
        Match(tokenList.at(index), TokenType::ID, index);
    }
    else {
        throw std::exception();
    }
}
void ParserHelper::ParameterList(std::vector<Token *> tokenList, int &index) {
    /* parameterList -> COMMA parameter parameterList | lambda */
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::COMMA) { // It's in the First set of parameterList, so take this route
        Match(tokenList.at(index), TokenType::COMMA, index); // Match COMMA
        Parameter(tokenList, index);
        ParameterList(tokenList, index);
    }
    else if (nextType == TokenType::RIGHT_PAREN) { // It's in the follow set of parameterList, so take this route
        return;
    }
    else {
        throw std::exception();
    }
}
void ParserHelper::PredicateList(std::vector<Token *> tokenList, int &index) {
    /* predicateList ->	COMMA predicate predicateList | lambda */
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::COMMA) { // It's in the First set of predicateList, so take this route
        Match(tokenList.at(index), TokenType::COMMA, index);
        Predicate(tokenList, index);
        PredicateList(tokenList, index);
    }
    else if (nextType == TokenType::PERIOD) { // It's in the follow set of predicateList, so take this route
        return;
    }
    else {
        throw std::exception();
    }
}
void ParserHelper::Query(std::vector<Token *> tokenList, int &index) {
    /* query -> predicate Q_MARK */
    Predicate(tokenList, index);
    Match(tokenList.at(index), TokenType::Q_MARK, index);
}
void ParserHelper::QueryList(std::vector<Token *> tokenList, int &index) {
    /* queryList ->	query queryList | lambda */
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::ID) { // It's in the First set of queryList, so take this route
        Query(tokenList, index);
        QueryList(tokenList, index);
    }
    else if (nextType == TokenType::END_OF_FILE) { // It's in the follow set of queryList, so take this route
        return;
    }
    else {
        throw std::exception();
    }
}