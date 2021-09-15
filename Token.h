#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COLON,
    COLON_DASH,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    STRING,
    ID,
    COMMENT,
    UNDEFINED,
    END_OF_FILE
};

class Token
{
private:

    TokenType fullType;
    std::string fullDescription;
    int lineNum;

    std::string EnumToString(TokenType type);


public:
    Token();
    ~Token();
    Token(TokenType type, std::string description, int line);
    std::string TokenToString();



};

#endif // TOKEN_H

