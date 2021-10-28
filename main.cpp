#include <string>
#include <fstream>
#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include "Database.h"

using namespace std;

int main(int argc, char** argv) {

    // check command line arguments
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " input_file" << endl;
        return 1;
    }

    // open file
    string line;
    string completeFile;
    string fileName = argv[1];
    ifstream input(fileName);
    if (!input.is_open()) {
        cout << "File " << fileName << " could not be found or opened." << endl;
        return 1;
    }
    else {
        while (getline(input,line)) {
            completeFile.append(line);
            completeFile.append("\n");
        }
        //completeFile.erase(completeFile.size()-1,completeFile.size()-1);
    }

    Lexer* lexer = new Lexer();

    std::vector<Token*> myTokens = lexer->Run(completeFile);

    //lexer->PrintLexer();
    //Parser myParse;
   // DatalogProgram* myProg = new DatalogProgram();
   DatalogProgram* myProg = new DatalogProgram();
   Database* myDatabase = new Database();
   Parser myParse = Parser(myProg);
   Interpreter theInterpreter = Interpreter(myDatabase, myProg);
    try {
        myProg = myParse.PerformParse(myTokens);
        theInterpreter.EvaluateSchemes();
        theInterpreter.EvaluateFacts();
        std::cout << theInterpreter.EvaluateQueries() << std::endl;
        std::cout << myDatabase->PrintDatabase() << std::endl;

    }
    catch(Token* token) {
        std::cout << "Failure!" << std::endl;
        std::cout << "  " << token->TokenToString();

        //delete myParse;
        delete myProg;
        delete lexer;
        delete myDatabase;
        input.close();
        return 0;

    }
    catch(...) {
        std::cout << "Something else went wrong!";
    }
    //std::cout << "Success!" << std::endl;
    //std::cout << myProg->DatalogToString();

    //delete myParse;
    delete myProg;
    delete lexer;
    delete myDatabase;
    input.close();

    return 0;
}