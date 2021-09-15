#include <string>
#include <fstream>
#include <iostream>
#include "Lexer.h"

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

    lexer->Run(completeFile);

    lexer->PrintLexer();


    delete lexer;
    input.close();

    return 0;
}