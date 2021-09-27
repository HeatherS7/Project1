#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "Q_MarkAutomaton.h"
#include "Left_ParenAutomaton.h"
#include "Right_ParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "StringAutomaton.h"
#include "IdAutomaton.h"
#include "CommentAutomaton.h"
#include "UndefinedAutomaton.h"
#include "End_Of_FileAutomaton.h"
#include "Automaton.h"
#include <iostream>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    for (unsigned int i=0; i < automata.size(); i++) {
        delete automata[i];
    }
    for (unsigned int i=0; i<tokens.size(); i++) {
        delete tokens[i];
    }
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new Q_MarkAutomaton());
    automata.push_back(new Left_ParenAutomaton());
    automata.push_back(new Right_ParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new UndefinedAutomaton());
    automata.push_back(new End_Of_FileAutomaton());
}

void Lexer::PrintLexer() {

    for (unsigned int i=0; i<tokens.size(); i++) {
        std::cout << tokens[i]->TokenToString() << "\n";
    }
    std::cout << "Total Tokens = " << tokens.size();
}


std::vector<Token*> Lexer::Run(std::string& input) {
    int lineNum = 1;
    Automaton* maxAutomaton;
    while(input.size() > 0) {
        int maxRead = 0;
        maxAutomaton = automata[0];
        while (input.size() > 0 && (input.at(0) == ' ' || input.at(0) == '\t')) {
            input.erase(0, 1); // as long as there is whitespace, remove it from the input
        }
        while (input.size() > 0 && input.at(0) == '\n') {
            lineNum++;
            input.erase(0,1);
            while (input.size() > 0 && input.at(0) == ' ') {
                input.erase(0,1);
            }
        }


        int inputRead = 0;
        for (unsigned int i=0; i < automata.size(); i++) {
            inputRead = automata[i]->Start(input);
            // Here is the Parallel part of the algorithm
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata[i];
            }
        }
            // Here is the Max part of the algorithm
            if (maxRead > 0) {
                Token *newToken = maxAutomaton->CreateToken(input.substr(0,maxRead), lineNum);
                lineNum += maxAutomaton->NewLinesRead();
                if (newToken->GetTokenType() != TokenType::COMMENT) {
                    tokens.push_back(newToken);
                }
            }
                // Create a single character undefined token
            else if (input != ""){
                maxRead = 1;
                Token *undefinedToken = (new UndefinedAutomaton())->CreateToken(input.substr(0, maxRead), lineNum);
                tokens.push_back(undefinedToken);
            }

        // Update `input` by removing characters read to create Token
           // std::cout << "hit here: " << input.size() << "\n";
            if (input.size() == 1) {
                input.erase();
            }
            else {
                input.erase(0, maxRead);
            }
        }
    if (input == "\n") {
        lineNum++;
    }
    Token *eofToken = (new End_Of_FileAutomaton())->CreateToken(input.substr(0, 0), lineNum);
    tokens.push_back(eofToken);

    return tokens;

}
