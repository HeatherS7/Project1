#include "Token.h"
#include <iostream>

Token::Token() {

}
Token::~Token() {

}

Token::Token(TokenType type, std::string description, int line) {
    // TODO: initialize all member variables
    fullType = type;
    fullDescription = description;
    lineNum = line;
}

std::string Token::EnumToString(TokenType type) {
    switch(type) {
        case TokenType::COLON: return "COLON";
        case TokenType::COLON_DASH: return "COLON_DASH";
        case TokenType::COMMA: return "COMMA";
        case TokenType::PERIOD: return "PERIOD";
        case TokenType::Q_MARK: return "Q_MARK";
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::END_OF_FILE: return "EOF";
        case TokenType::MULTIPLY: return "MULTIPLY";
        case TokenType::ADD: return "ADD";
        case TokenType::SCHEMES: return "SCHEMES";
        case TokenType::FACTS: return "FACTS";
        case TokenType::RULES: return "RULES";
        case TokenType::QUERIES: return "QUERIES";
        case TokenType::STRING: return "STRING";
        case TokenType::ID: return "ID";
        case TokenType::COMMENT: return "COMMENT";
        case TokenType::UNDEFINED: return "UNDEFINED";
    }
    return "";
}

std::string Token::TokenToString() {
    std::string returnString = "(" + EnumToString(fullType) + ",\"" + fullDescription + "\"," + std::to_string(lineNum) + ")";
    return returnString;
}

TokenType Token::GetTokenType() {
    return fullType;
}

std::string Token::GetTokenDescription() {
    return fullDescription;
}

int Token::GetTokenLineNum() {
    return lineNum;
}

