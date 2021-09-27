#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"
#include <iostream>

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;

    void CreateAutomata();
    Automaton* maxAutomaton;

    // TODO: add any other private methods here (if needed)

public:
    Lexer();
    ~Lexer();

    std::vector<Token*> Run(std::string& input);
    void PrintLexer();
    
    // TODO: add other public methods here

};

#endif // LEXER_H

