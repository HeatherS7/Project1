#include <string>
#include <fstream>
#include <iostream>
#include "Lexer.h"
#include "Parser.h"

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
    Parser myParse;
    try {
        myParse.PerformParse(myTokens);

    }
    catch(...) {
        std::cout << "Failure!";
        delete lexer;
        input.close();
        return 1;

    }
    std::cout << "Success";


    delete lexer;
    input.close();

    return 0;
}