#ifndef PROJECT1_STARTER_CODE_INTERPRETER_H
#define PROJECT1_STARTER_CODE_INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
private:
    Database* theData;
    DatalogProgram* datalogInfo;
    Relation theRelation;

public:
    Interpreter();
    Interpreter(DatalogProgram* newDatalogInfo);
    ~Interpreter();
    Interpreter(Database* newData, DatalogProgram* newDatalogInfo);
    Relation* EvaluatePredicate(const Predicate& p);
    void EvaluateSchemes();
    void EvaluateFacts();
    std::string EvaluateQueries();

};

/* TODO: Format the output
 * count how many options are available and add that to the output
 * fix warnings and errors
 * clean up the code */

#endif //PROJECT1_STARTER_CODE_INTERPRETER_H
