#ifndef PROJECT1_STARTER_CODE_END_OF_FILEAUTOMATON_H
#define PROJECT1_STARTER_CODE_END_OF_FILEAUTOMATON_H

#include "Automaton.h"

class End_Of_FileAutomaton : public Automaton {
public:
    End_Of_FileAutomaton():Automaton(TokenType::END_OF_FILE) {}
    void S0(const std::string& input) {
        inputRead = 0;
    }
};

#endif //PROJECT1_STARTER_CODE_END_OF_FILEAUTOMATON_H
