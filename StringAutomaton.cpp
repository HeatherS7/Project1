#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string &input) {
    type = TokenType::STRING;
    if (input[index] == '\'') {
        inputRead = 1;
        index++;
        S1(input);
    } else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string &input) {
    while ((input.size()>((unsigned)index)) && input[index]!= '\'') {
        if (input[index] == '\n') {
            newLines++;
        }
        inputRead++;
        index++;
    }
    if (input.size()>((unsigned)index)) {
        S2(input);
    }
    else { // It has reached EOF
        Serr();
    }
}

void StringAutomaton::S2(const std::string &input) {
    if(input[index] == '\'') {
        inputRead++;
        index++;
        if (input[index]!=EOF && (input[index] == '\'')) {
            inputRead++;
            index++;
            S1(input);
        }
    }
}

void StringAutomaton::Serr() {
    type = TokenType::UNDEFINED;
}
