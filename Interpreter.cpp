#include "Interpreter.h"

Interpreter::Interpreter() {

}

Interpreter::Interpreter(DatalogProgram *newDatalogInfo) {
    datalogInfo = newDatalogInfo;
}

Interpreter::Interpreter(Database* newData, DatalogProgram* newDatalogInfo) {
    theData = newData;
    datalogInfo = newDatalogInfo;
}

Relation* Interpreter::EvaluatePredicate(const Predicate &p) {
    return nullptr;
}