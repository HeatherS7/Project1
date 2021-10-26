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
    retString.append(std::to_string(schemes.size()) + "):\n");
    for (unsigned int i = 0; i<schemes.size(); i++) {
        retString.append("  " + schemes.at(i)->PredicateToString() + "\n");
    }
    retString.append("Facts(" + std::to_string(facts.size()) + "):\n");
    for (unsigned int i = 0; i<facts.size(); i++) {
        retString.append("  " + facts.at(i)->PredicateToString() + ".\n");
    }
    retString.append("Rules(" + std::to_string(rules.size()) + "):\n");
    for (unsigned int i = 0; i<rules.size(); i++) {
        retString.append("  " + rules.at(i)->RuleToString() + '\n');
    }
    retString.append("Queries(" + std::to_string(queries.size()) + "):\n");
    for (unsigned int i = 0; i<queries.size(); i++) {
        retString.append("  " + queries.at(i)->PredicateToString() + "?\n");
    }
    retString.append(DomainToString());

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

void DatalogProgram::AddQuery(Predicate *newQuery) {
    queries.push_back(newQuery);
}

void DatalogProgram::AddScheme(Predicate* newScheme) {
    schemes.push_back(newScheme);
}

void DatalogProgram::AddFact(Predicate* newFact) {
    facts.push_back(newFact);
}

void DatalogProgram::AddRule(Rule* newRule) {
    rules.push_back(newRule);
}

void DatalogProgram::AddDomain(std::string newDomain) {
    if (domainSet.find(newDomain) != domainSet.end()) {
        // It's already in the domain
    }
    else {
        // It's not in the domain, so add it
        domainSet.insert(newDomain);
    }

}

std::string DatalogProgram::DomainToString() {

    std::string retString = "Domain(" + std::to_string(domainSet.size()) + "):\n";
    for (auto it = domainSet.begin(); it != domainSet.end(); it++) {
        retString.append("  " + *it + "\n");
    }
    return retString;
}

void DatalogProgram::EvaluateSchemes(Database* theDatabase) {

    for (unsigned int i = 0; i < schemes.size(); i++) {
        theDatabase->AddMappedRelationship(schemes.at(i)->GetId(), Relation(schemes.at(i)->GetParameters()));
    }

}

void DatalogProgram::EvaluateFacts(Database *theDatabase) {
    /* for each fact ‘f’
     * make a tuple ‘t’ using the values from ‘f’
     * add ‘t’ to relation with the same name as ‘f’*/
    for (unsigned int i = 0; i < facts.size(); i++) {
        Tuple newTuple = Tuple(facts.at(i)->GetParameters());
        theDatabase->AddTuplesToRelation(facts.at(i)->GetId(), newTuple);
    }
}
