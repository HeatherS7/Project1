#ifndef PROJECT1_STARTER_CODE_PREDICATE_H
#define PROJECT1_STARTER_CODE_PREDICATE_H

#include "Parameter.h"
#include <vector>

class Predicate {
private:
    std::string id;
    std::vector<Parameter*> parameters;
    int numParameters;

public:
    Predicate();
    ~Predicate();
    std::string PredicateToString();
    void SetNumParameters(int num);
    int GetNumParameters();


};

#endif //PROJECT1_STARTER_CODE_PREDICATE_H
