#ifndef PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
#define PROJECT1_STARTER_CODE_DATALOGPROGRAM_H

#include "Rule.h"

class DatalogProgram {
    // A datalog program consists of lists of schemes, facts, rules and queries.
private:
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Rule*> rules;
    std::vector<Predicate*> queries;

public:
    ~DatalogProgram();
    std::string DatalogToString();
    std::vector<Predicate*> GetSchemesList();
    std::vector<Predicate*> GetFactsList();
    std::vector<Predicate*> GetQueriesList();
    std::vector<Rule*> GetRulesList();
    void AddQuery(Predicate* newQuery);
    void AddScheme(Predicate* newScheme);
    void AddFact(Predicate* newFact);
    void AddRule(Rule* newRule);

};

#endif //PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
