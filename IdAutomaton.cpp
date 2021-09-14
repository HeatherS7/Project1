#include "IdAutomaton.h"

void IDAutomaton::S0(const std::string &input) {
    if (isalpha(input[index])){
        inputRead = 1;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void IDAutomaton::S1(const std::string &input) {
    while (isalpha(input[index]) || isdigit(input[index])) {
        inputRead++;
        index++;
    }
}