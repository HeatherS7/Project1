#ifndef PROJECT1_STARTER_CODE_INTERPRETER_H
#define PROJECT1_STARTER_CODE_INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
private:
    Database* theData;
    DatalogProgram* datalogInfo;

public:
    Interpreter();
    Interpreter(DatalogProgram* newDatalogInfo);
    Interpreter(Database* newData, DatalogProgram* newDatalogInfo);
    Relation* EvaluatePredicate(const Predicate& p);

};

#endif //PROJECT1_STARTER_CODE_INTERPRETER_H
