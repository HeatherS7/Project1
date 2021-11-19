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
    Relation* theRelation = theData->FindRelationByName(p.GetId());
    std::vector<std::string> variables = {};
    std::vector<std::string> variablesWoPlaceholders = {};
    std::vector<int> headerIndex = {};
    // select for each constant in the query
    for (unsigned int j = 0; j < p.GetNumParameters(); j++) {
        if (!p.GetParameterAtIndexIsId(j)) {
            theRelation = theRelation->Select(j, p.GetParameterAtIndex(j));
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
                theRelation = theRelation->Select(i, j);
            }
        }
    }

    // project using the positions of the variables
    unsigned int index = 0;
    while (index < variablesWoPlaceholders.size()) {
        for (unsigned int j = 0 ; j < variablesWoPlaceholders.size(); j++) {
            if ((variablesWoPlaceholders.at(index) == variablesWoPlaceholders.at(j)) && (index != j)) {
                variablesWoPlaceholders.erase(variablesWoPlaceholders.begin() + j);
                headerIndex.erase(headerIndex.begin() + j);
            }
        }
        index++;
    }
    theRelation = theRelation->Project(headerIndex);

    // rename to match the names of variables in ‘q’
    theRelation = theRelation->Rename(variablesWoPlaceholders);

    return theRelation;


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

    std::string retString = "Query Evaluation\n";
    for (unsigned int i = 0; i < datalogInfo->GetQueriesSize(); i++) {
        Predicate* predToEval = datalogInfo->GetQueryAtIndex(i);
        Relation* newRel = EvaluatePredicate(*predToEval);
        std::string hasSolution = "No";
        if (newRel->GetNumTuples() > 0) {
            // It has a solution!
            hasSolution = "Yes";
        }

        retString.append(datalogInfo->GetQueryAtIndex(i)->PredicateToString() + "? ");
        if (hasSolution == "Yes") {
            retString.append(hasSolution + "(" + std::to_string(newRel->GetNumTuples()) + ")");
        } else {
            retString.append(hasSolution);
        }
        retString.append(newRel->PrintRelation());
        delete newRel;
    }

    return retString;

}

std::string Interpreter::EvaluateRules() {
    // Evaluate the predicates on the right-hand side of the rule
    std::vector<Relation*> intermediateResults = {};
    std::vector<std::string> tuplePrintout = {};
    Relation newRel = Relation();
    bool addedNewTuples = true;
    int numTimesThroughRules = 0;
    std::string relString = "";
    std::cout << "Rule Evaluation" << std::endl;
    for (unsigned int i = 0; i < datalogInfo->GetRulesSize(); i++) {
        tuplePrintout.push_back("");
    }
    while(addedNewTuples) {
        int initialNumTuples = theData->GetNumTuplesInDatabase();
        for (unsigned int i = 0; i < datalogInfo->GetRulesSize(); i++) {
            std::cout << datalogInfo->GetRuleAtIndex(i)->RuleToString() << std::endl;

            for (unsigned int j = 0; j < datalogInfo->GetRuleAtIndex(i)->GetBodyPredicatesSize(); j++) {
                Predicate *predToEval = datalogInfo->GetRuleAtIndex(i)->GetBodyPredicateAtIndex(j);
                intermediateResults.push_back(EvaluatePredicate(*predToEval));
            }
            // Join the relations that result
            if (intermediateResults.size() > 1) {
                newRel = *newRel.NaturalJoin(intermediateResults.at(0), intermediateResults.at(1));
                for (unsigned int j = 2; j < intermediateResults.size(); j++) {
                    newRel = *newRel.NaturalJoin(&newRel, intermediateResults.at(j));
                }
            } else if (intermediateResults.size() > 0) {
                newRel = *intermediateResults.at(0);
            }
            intermediateResults.clear();

            // Project the columns that appear in the head predicate
            std::vector<int> indices;
            std::vector<std::string> attributes = datalogInfo->GetRuleAtIndex(i)->GetHeadPredicate()->GetParameters();
            std::vector<std::string> headAttributes = newRel.GetHeader().GetAttributes();
            for (unsigned int i = 0; i < attributes.size(); i++) {
                auto it = std::find(headAttributes.begin(), headAttributes.end(),
                                    attributes.at(i));
                if (it != headAttributes.end()) {
                    indices.push_back(it - headAttributes.begin());
                }
            }
            newRel = *newRel.Project(indices);

            // Rename the relation to make it union-compatible
            Relation *relInDatabase = theData->FindRelationByName(
                    datalogInfo->GetRuleAtIndex(i)->GetHeadPredicate()->GetId());
            newRel = *newRel.Rename(relInDatabase->GetHeader().GetAttributes());

            // Union with the relation in the database
            //Relation dummyRel = *newRel.Union(&newRel, relInDatabase, true);
            relInDatabase->Union(&newRel, true);

        }
        int afterNumOfTuples = theData->GetNumTuplesInDatabase();
        (afterNumOfTuples > initialNumTuples) ? addedNewTuples = true : addedNewTuples = false;
        numTimesThroughRules++;
    }

    relString.append("\nSchemes populated after " + std::to_string(numTimesThroughRules) + " passes through the Rules.\n");

    return relString;
}