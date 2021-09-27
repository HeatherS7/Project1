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


};

#endif //PROJECT1_STARTER_CODE_RULE_H
