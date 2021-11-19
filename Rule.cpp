#include "Rule.h"

Rule::Rule() {
    //Predicate* headPredicate = new Predicate();
}
Rule::~Rule() {
    //delete headPredicate;
    for (unsigned int i = 0; i<bodyPredicates.size(); i++) {
        delete bodyPredicates.at(i);
    }
}

std::string Rule::RuleToString() {
    std::string retString = headPredicate->PredicateToString();
    retString.append(" :- ");
    for (unsigned int i = 0; i<bodyPredicates.size(); i++) {
        retString.append(bodyPredicates.at(i)->PredicateToString());
        if (i<bodyPredicates.size()-1){
            retString.append(",");
        }
    }
    retString.push_back('.');

    return retString;
}
void Rule::SetHeadPredicate(Predicate *newHPredicate) {
    headPredicate = newHPredicate;
}
void Rule::AddBodyPredicate(Predicate *newBodyPred) {
    bodyPredicates.push_back(newBodyPred);
}

unsigned int Rule::GetBodyPredicatesSize() {
    return bodyPredicates.size();
}

Predicate* Rule::GetBodyPredicateAtIndex(int index) {
    return bodyPredicates.at(index);
}

Predicate* Rule::GetHeadPredicate() {
    return headPredicate;
}
