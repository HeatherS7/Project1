#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string &input) {
    type = TokenType::COMMENT;
    if (input[index] == '#') {
        index++;
        if (input[index] == '|') {
            index++;
            inputRead = 2;
            S2(input);
        }
        else {
            inputRead = 1;
            S1(input);
        }
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string &input) {
    while (input[index]!='\n' && input.size()>((unsigned)index)) {
        inputRead++;
        index++;
    }
}

void CommentAutomaton::S2(const std::string& input) {
    while (input[index]!= '|' && input.size()>((unsigned)index)) {
        if (input[index] == '\n') {
            newLines++;
        }
        inputRead++;
        index++;
    }
    if (input[index] == '|') {
        inputRead++;
        index++;
        if (input[index] == '#') {
            inputRead++;
            index++;
        }
        else {
            S2(input);
        }
    }
    else {
        Serr();
    }
}

void CommentAutomaton::Serr() {
    type = TokenType::UNDEFINED;
}