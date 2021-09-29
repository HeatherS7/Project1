#include "ParserHelper.h"

void ParserHelper::DatalogProgram(std::vector<Token*> tokenList, int index, class DatalogProgram* myProg) {
    /* datalogProgram	->	SCHEMES COLON scheme schemeList FACTS
     * COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF*/
    if (tokenList.size()<=0) {
        throw std::exception();
    }
    Match(tokenList.at(index), TokenType::SCHEMES, index); // Match SCHEME
    Match(tokenList.at(index),TokenType::COLON, index); // Match COLON
    myProg->AddScheme((Scheme(tokenList, index))); // Call scheme non-terminal
    SchemeList(tokenList, index, myProg); // Call schemeList non-terminal
    Match(tokenList.at(index), TokenType::FACTS, index); // Match FACTS
    Match(tokenList.at(index), TokenType::COLON, index); // Match COLON
    FactList(tokenList, index, myProg); // Call factList non-terminal
    Match(tokenList.at(index), TokenType::RULES, index); // Match RULES
    Match(tokenList.at(index), TokenType::COLON, index); // Match COLON
    RuleList(tokenList, index, myProg); // Call ruleList non-terminal
    Match(tokenList.at(index), TokenType::QUERIES, index); // Match QUERIES
    Match(tokenList.at(index), TokenType::COLON, index); // Match COLON
    myProg->AddQuery(Query(tokenList, index)); // Call query non-terminal
    QueryList(tokenList, index, myProg); // Call queryList non-terminal
    Match(tokenList.at(index), TokenType::END_OF_FILE, index); // Match EOF



}

void ParserHelper::Match(Token* token, TokenType matchType, int& index) {
    if (token->GetTokenType() == matchType) {
        index++;
    }
    else {
        throw token;
    }
}

Predicate* ParserHelper::Scheme(std::vector<Token*> tokenList, int& index) {
    /* scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN*/
    Match(tokenList.at(index), TokenType::ID, index); // Match ID;
    class Predicate* schemePred = new class Predicate(tokenList.at(index-1)->GetTokenDescription());
    Match(tokenList.at(index), TokenType::LEFT_PAREN, index); // Match LEFT_PAREN
    Match(tokenList.at(index), TokenType::ID, index); // Match ID
    schemePred->AddParameter(new class Parameter(tokenList.at(index-1)->GetTokenDescription()));
    IdList(tokenList, index, schemePred); // Calls the idList non-terminal
    Match(tokenList.at(index), TokenType::RIGHT_PAREN,index); // Match RIGHT_PAREN
    return schemePred;

}
void ParserHelper::IdList(std::vector<Token *> tokenList, int &index, class Predicate* newPred) {
    /*idList  	-> 	COMMA ID idList | lambda*/
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::COMMA) { // It's in the First set of idList, so take this route
        Match(tokenList.at(index), TokenType::COMMA, index); // Match COMMA
        Match(tokenList.at(index), TokenType::ID, index); // Match ID
        newPred->AddParameter(new class Parameter(tokenList.at(index-1)->GetTokenDescription()));
        IdList(tokenList, index, newPred);
    }
    else if (nextType == TokenType::RIGHT_PAREN) { // It's in the follow set of idList, so take this route
        return;
    }
    else {
        throw tokenList.at(index);
    }

}

/*void ParserHelper::IdList(std::vector<Token *> tokenList, int &index) {
    /*idList  	-> 	COMMA ID idList | lambda
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
        throw tokenList.at(index);
    }

}*/

void ParserHelper::SchemeList(std::vector<Token *> tokenList, int &index, class DatalogProgram* myProg) {
    /*schemeList -> scheme schemeList | lambda*/
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::ID) { // It's in the First set of schemeList, so take this route
        class Predicate* newPred = new class Predicate();
        newPred = Scheme(tokenList, index); // Call scheme non-terminal
        myProg->AddScheme(newPred);
        SchemeList(tokenList, index, myProg); // Call schemeList non-terminal
    }
    else if (nextType == TokenType::FACTS) { // It's in the follow set of schemeList, so take this route
        return;
    }
    else {
        throw tokenList.at(index);
    }

}

void ParserHelper::FactList(std::vector<Token*> tokenList, int &index, class DatalogProgram* myProg) {
    /* factList	-> fact factList | lambda*/
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::ID) { // It's in the First set of factList, so take this route
        myProg->AddFact(Fact(tokenList, index, myProg)); // call fact non-terminal
        FactList(tokenList, index, myProg); // call factList non-terminal again
    }
    else if (nextType == TokenType::RULES) { // It's in the follow set of factList, so take this route
        return;
    }
    else {
        throw tokenList.at(index);
    }

}

Predicate* ParserHelper::Fact(std::vector<Token*> tokenList, int &index, class DatalogProgram* myProg) {
    /* fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD*/
    Match(tokenList.at(index), TokenType::ID, index); // Match ID
    class Predicate* factPred = new class Predicate(tokenList.at(index-1)->GetTokenDescription());
    Match(tokenList.at(index), TokenType::LEFT_PAREN, index); // Match LEFT_PAREN
    Match(tokenList.at(index), TokenType::STRING, index); // Match STRING
    factPred->AddParameter(new class Parameter(tokenList.at(index-1)->GetTokenDescription()));
    myProg->AddDomain(tokenList.at(index-1)->GetTokenDescription());
    StringList(tokenList, index, factPred, myProg); // Call stringList
    Match(tokenList.at(index), TokenType::RIGHT_PAREN, index); // Match RIGHT_PAREN
    Match(tokenList.at(index), TokenType::PERIOD, index); // Match PERIOD
    return factPred;

}

void ParserHelper::StringList(std::vector<Token *> tokenList, int &index, class Predicate* newPred, class DatalogProgram* myProg) {
    /* stringList -> COMMA STRING stringList | lambda*/
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::COMMA) { // It's in the First set of stringList, so take this route
        Match(tokenList.at(index), TokenType::COMMA, index); // Match COMMA
        Match(tokenList.at(index), TokenType::STRING, index); // Match STRING
        newPred->AddParameter(new class Parameter(tokenList.at(index-1)->GetTokenDescription()));
        myProg->AddDomain(tokenList.at(index-1)->GetTokenDescription());
        StringList(tokenList, index, newPred, myProg); // Call stringList again
    }
    else if (nextType == TokenType::RIGHT_PAREN) { // It's in the follow set of stringList, so take this route
        return;
    }
    else {
        throw tokenList.at(index);
    }
}

/*void ParserHelper::StringList(std::vector<Token *> tokenList, int &index) {
    /* stringList -> COMMA STRING stringList | lambda
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
        throw tokenList.at(index);
    }
}*/

void ParserHelper::RuleList(std::vector<Token *> tokenList, int &index, class DatalogProgram* myProg) {
    /* ruleList	->	rule ruleList | lambda*/
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::ID) { // It's in the First set of ruleList, so take this route
        myProg->AddRule(Rule(tokenList, index)); // Call rule non-terminal
        RuleList(tokenList, index, myProg);
    }
    else if (nextType == TokenType::QUERIES) { // It's in the follow set of ruleList, so take this route
        return;
    }
    else {
        throw tokenList.at(index);
    }
}
Rule* ParserHelper::Rule(std::vector<Token *> tokenList, int &index) {
    /* rule	-> headPredicate COLON_DASH predicate predicateList PERIOD*/
    class Rule* newRule = new class Rule();
    newRule->SetHeadPredicate(HeadPredicate(tokenList, index)); // Call headPredicate non-terminal
    Match(tokenList.at(index), TokenType::COLON_DASH, index); // Match COLON_DASH
    newRule->AddBodyPredicate(Predicate(tokenList, index)); // Call predicate
    PredicateList(tokenList, index, newRule); // Call predicateList
    Match(tokenList.at(index), TokenType::PERIOD, index); // Match PERIOD
    return newRule;
}
Predicate* ParserHelper::HeadPredicate(std::vector<Token *> tokenList, int &index) {
    /* headPredicate ->	ID LEFT_PAREN ID idList RIGHT_PAREN */
    Match(tokenList.at(index), TokenType::ID, index); // Match ID
    class Predicate* hPred = new class Predicate(tokenList.at(index-1)->GetTokenDescription());
    Match(tokenList.at(index), TokenType::LEFT_PAREN, index); // Match LEFT_PAREN
    Match(tokenList.at(index), TokenType::ID, index); // Match ID
    hPred->AddParameter(new class Parameter(tokenList.at(index-1)->GetTokenDescription()));
    IdList(tokenList, index, hPred); // Call idList non-terminal
    Match(tokenList.at(index), TokenType::RIGHT_PAREN, index); // Match RIGHT_PAREN
    return hPred;
}
Predicate* ParserHelper::Predicate(std::vector<Token *> tokenList, int &index) {
    /* predicate ->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN */
    Match(tokenList.at(index), TokenType::ID, index); // Match ID
    class Predicate* newPred = new class Predicate(tokenList.at(index-1)->GetTokenDescription());
    Match(tokenList.at(index), TokenType::LEFT_PAREN, index); // Match LEFT_PAREN
    newPred->AddParameter(Parameter(tokenList, index));
    ParameterList(tokenList, index, newPred); // Call parameterList non-terminal
    Match(tokenList.at(index), TokenType::RIGHT_PAREN, index); // Match RIGHT_PAREN
    return newPred;
}
Parameter* ParserHelper::Parameter(std::vector<Token *> tokenList, int &index) {
    /* parameter ->	STRING | ID*/
    if (tokenList.at(index)->GetTokenType() == TokenType::STRING) {
        Match(tokenList.at(index), TokenType::STRING, index);
    }
    else if (tokenList.at(index)->GetTokenType() == TokenType::ID) {
        Match(tokenList.at(index), TokenType::ID, index);
    }
    else {
        throw tokenList.at(index);
    }
    return new class Parameter(tokenList.at(index-1)->GetTokenDescription());
}
void ParserHelper::ParameterList(std::vector<Token *> tokenList, int &index, class Predicate* newPred) {
    /* parameterList -> COMMA parameter parameterList | lambda */
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::COMMA) { // It's in the First set of parameterList, so take this route
        Match(tokenList.at(index), TokenType::COMMA, index); // Match COMMA
        newPred->AddParameter(Parameter(tokenList, index));
        ParameterList(tokenList, index, newPred);
    }
    else if (nextType == TokenType::RIGHT_PAREN) { // It's in the follow set of parameterList, so take this route
        return;
    }
    else {
        throw tokenList.at(index);
    }
}
/*void ParserHelper::ParameterList(std::vector<Token *> tokenList, int &index) {
    /* parameterList -> COMMA parameter parameterList | lambda
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
        throw tokenList.at(index);
    }
}*/
void ParserHelper::PredicateList(std::vector<Token *> tokenList, int &index, class Rule* newRule) {
    /* predicateList ->	COMMA predicate predicateList | lambda */
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::COMMA) { // It's in the First set of predicateList, so take this route
        Match(tokenList.at(index), TokenType::COMMA, index);
        newRule->AddBodyPredicate(Predicate(tokenList, index));
        PredicateList(tokenList, index, newRule);
    }
    else if (nextType == TokenType::PERIOD) { // It's in the follow set of predicateList, so take this route
        return;
    }
    else {
        throw tokenList.at(index);
    }
}
Predicate* ParserHelper::Query(std::vector<Token *> tokenList, int &index) {
    /* query -> predicate Q_MARK */
    class Predicate* queryPred = Predicate(tokenList, index);
    Match(tokenList.at(index), TokenType::Q_MARK, index);
    return queryPred;

}
void ParserHelper::QueryList(std::vector<Token *> tokenList, int &index, class DatalogProgram* myProg) {
    /* queryList ->	query queryList | lambda */
    TokenType nextType = tokenList.at(index)->GetTokenType();
    if (nextType == TokenType::ID) { // It's in the First set of queryList, so take this route
        myProg->AddQuery(Query(tokenList, index));
        QueryList(tokenList, index, myProg);
    }
    else if (nextType == TokenType::END_OF_FILE) { // It's in the follow set of queryList, so take this route
        return;
    }
    else {
        throw tokenList.at(index);
    }
}