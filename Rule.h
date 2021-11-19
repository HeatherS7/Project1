#ifndef PROJECT1_STARTER_CODE_RULE_H
#define PROJECT1_STARTER_CODE_RULE_H

#include "Predicate.h"

class Rule {
private:
    Predicate* headPredicate;
    std::vector<Predicate*> bodyPredicates;


public:
    Rule();
    ~Rule();
    std::string RuleToString();
    void SetHeadPredicate(Predicate* newHPredicate);
    void AddBodyPredicate(Predicate* newBodyPred);
    unsigned int GetBodyPredicatesSize();
    Predicate* GetBodyPredicateAtIndex(int index);
    Predicate* GetHeadPredicate();


};

#endif //PROJECT1_STARTER_CODE_RULE_H
