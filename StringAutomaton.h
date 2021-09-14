#ifndef PROJECT1_STARTER_CODE_STRINGAUTOMATON_H
#define PROJECT1_STARTER_CODE_STRINGAUTOMATON_H

#include "Automaton.h"

class StringAutomaton : public Automaton {
public:
    StringAutomaton(): Automaton(TokenType::STRING) {} // calls the base constructor
    void S0(const std::string& input);
    void S1(const std::string& input);
    void S2(const std::string& input);
    void Serr();
};

#endif //PROJECT1_STARTER_CODE_STRINGAUTOMATON_H
