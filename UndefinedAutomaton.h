#ifndef PROJECT1_STARTER_CODE_UNDEFINEDAUTOMATON_H
#define PROJECT1_STARTER_CODE_UNDEFINEDAUTOMATON_H

#include "Automaton.h"

class UndefinedAutomaton : public Automaton {
public:
    UndefinedAutomaton():Automaton(TokenType::UNDEFINED) {}
    void S0(const std::string& input);

};

#endif //PROJECT1_STARTER_CODE_UNDEFINEDAUTOMATON_H
