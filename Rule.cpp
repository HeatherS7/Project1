#include "Rule.h"

Rule::Rule() {
    headPredicate = new Predicate();
}
Rule::~Rule() {
    delete headPredicate;
    for (unsigned int i = 0; i<bodyPredicates.size(); i++) {
        delete bodyPredicates.at(i);
    }
}

std::string Rule::RuleToString() {
    std::string retString = headPredicate->PredicateToString();
    retString.append(":-");
    for (unsigned int i = 0; i<bodyPredicates.size(); i++) {
        retString.append(bodyPredicates.at(i)->PredicateToString());
    }
    retString.push_back('.');

    return retString;
}