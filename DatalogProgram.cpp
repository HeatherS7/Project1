#include "DatalogProgram.h"

DatalogProgram::~DatalogProgram() {
    for (unsigned int i = 0; i<schemes.size(); i++) {
        delete schemes.at(i);
    }
    for (unsigned int i = 0; i<facts.size(); i++) {
        delete facts.at(i);
    }
    for (unsigned int i = 0; i<queries.size(); i++) {
        delete queries.at(i);
    }
    for (unsigned int i = 0; i<rules.size(); i++) {
        delete rules.at(i);
    }
}

std::string DatalogProgram::DatalogToString() {
    std::string retString = "";
    retString.append("Schemes(");
    retString.append(std::to_string(schemes.size()));
    retString.push_back(')');
    for (unsigned int i = 0; i<schemes.size(); i++) {
        retString.append("  " + schemes.at(i)->PredicateToString() + '\n');
    }
    retString.append("Facts(" + std::to_string(facts.size()) + ")");
    for (unsigned int i = 0; i<facts.size(); i++) {
        retString.append("  " + facts.at(i)->PredicateToString() + '\n');
    }
    retString.append("Rules(" + std::to_string(rules.size()) + '\n');
    for (unsigned int i = 0; i<rules.size(); i++) {
        retString.append("  " + rules.at(i)->RuleToString() + '\n');
    }
    retString.append("Queries(" + std::to_string(queries.size()) + '\n');
    for (unsigned int i = 0; i<queries.size(); i++) {
        retString.append("  " + queries.at(i)->PredicateToString() + '\n');
    }

    return retString;


}

std::vector<Predicate*> DatalogProgram::GetSchemesList() {
    return schemes;
}
std::vector<Predicate*> DatalogProgram::GetFactsList() {
    return facts;
}
std::vector<Predicate*> DatalogProgram::GetQueriesList() {
    return queries;
}
std::vector<Rule*> DatalogProgram::GetRulesList() {
    return rules;
}
