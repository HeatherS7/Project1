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
    Predicate(std::string id);
    ~Predicate();
    std::string PredicateToString();
    void SetNumParameters(int num);
    int GetNumParameters() const;
    void AddParameter(Parameter* newPara);
    void AddParameter(std::vector<Parameter*> newParameters);
    std::string GetId() const;
    std::vector<std::string> GetParameters() const;
    std::string GetParameterAtIndex(int index) const;
    bool GetParameterAtIndexIsId(int index) const;


};

#endif //PROJECT1_STARTER_CODE_PREDICATE_H
