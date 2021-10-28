#include "Interpreter.h"
#include <iostream>

Interpreter::Interpreter() {
}

Interpreter::Interpreter(DatalogProgram *newDatalogInfo) {
    datalogInfo = newDatalogInfo;

}

Interpreter::~Interpreter() {

}

Interpreter::Interpreter(Database* newData, DatalogProgram* newDatalogInfo) {
    theData = newData;
    datalogInfo = newDatalogInfo;
}

Relation* Interpreter::EvaluatePredicate(const Predicate &p) {

    // get the relation with the same name as the query
    theRelation = theData->FindRelationByName(p.GetId());
    std::vector<std::string> variables = {};
    std::vector<std::string> variablesWoPlaceholders = {};
    std::vector<int> headerIndex = {};
    // select for each constant in the query
    for (unsigned int j = 0; j < p.GetNumParameters(); j++) {
        if (!p.GetParameterAtIndexIsId(j)) {
            theRelation = *theRelation.Select(j, p.GetParameterAtIndex(j));
            variables.push_back("");
            //headerIndex.push_back(-1);
        } else {
            // we know it's a variable, so it to the vector to be evaluated later :-)
            variables.push_back(p.GetParameterAtIndex(j));
            variablesWoPlaceholders.push_back(p.GetParameterAtIndex(j));
            headerIndex.push_back(j);
        }
    }
    // select for each pair of matching variables in the queries
    for (unsigned int i = 0; i < variables.size(); i++) {
        for (unsigned int j = 0; j < variables.size(); j++) {
            if ((variables.at(i) == variables.at(j)) && variables.at(i) != "") {
                theRelation = *theRelation.Select(i, j);
            }
        }
    }

    // project using the positions of the variables
    theRelation = theRelation.Project(headerIndex);

    // rename to match the names of variables in ‘q’
    theRelation = theRelation.Rename(variablesWoPlaceholders);

    return &theRelation;


}

void Interpreter::EvaluateSchemes() {
    for (unsigned int i = 0; i < datalogInfo->GetSchemesSize(); i++) {
        theData->AddMappedRelationship(datalogInfo->GetSchemeAtIndex(i)->GetId(),
                                       Relation(Header(datalogInfo->GetSchemeAtIndex(i)->GetParameters())));

    }
}

void Interpreter::EvaluateFacts() {
    /* for each fact ‘f’
 * make a tuple ‘t’ using the values from ‘f’
 * add ‘t’ to relation with the same name as ‘f’*/
    for (unsigned int i = 0; i < datalogInfo->GetFactsSize(); i++) {
        Tuple newTuple = Tuple(datalogInfo->GetFactAtIndex(i)->GetParameters());
        theData->AddTuplesToRelation(datalogInfo->GetFactAtIndex(i)->GetId(), newTuple);
    }
}

std::string Interpreter::EvaluateQueries() {
    /* for each query ‘q’
get the relation ‘r’ with the same name as the query ‘q’
select for each constant in the query ‘q’
select for each pair of matching variables in ‘q’
project using the positions of the variables in ‘q’
rename to match the names of variables in ‘q’
print the resulting relation
*/

    /*Relation* newRel;
    std::string retString = "";
    int numConstants = 0;
    std::vector<std::string> variables = {};
    std::vector<int> headerIndex = {};
    for (unsigned int i = 0; i < datalogInfo->GetQueriesSize(); i++) {
        Predicate* toEvaluate = datalogInfo->GetQueryAtIndex(i);
        newRel = EvaluatePredicate(*toEvaluate);
        retString.append(newRel->PrintRelation());
    }*/

    std::string retString = "";
    for (unsigned int i = 0; i < datalogInfo->GetQueriesSize(); i++) {
        Predicate* predToEval = datalogInfo->GetQueryAtIndex(i);
        Relation* newRel = EvaluatePredicate(*predToEval);
        retString.append(newRel->PrintRelation());
    }

    return retString;

}