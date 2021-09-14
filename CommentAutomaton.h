#ifndef PROJECT1_STARTER_CODE_COMMENTAUTOMATON_H
#define PROJECT1_STARTER_CODE_COMMENTAUTOMATON_H

#include "Automaton.h"

class CommentAutomaton : public Automaton {
public:
    CommentAutomaton():Automaton(TokenType::COMMENT) {}
    void S0(const std::string& input);
    void S1(const std::string& input);
    void S2(const std::string& input);
    void Serr();
};

#endif //PROJECT1_STARTER_CODE_COMMENTAUTOMATON_H
