#include "Database.h"

Database::Database() {
    dataMap = {};
}

void Database::AddMappedRelationship(std::string newKey, Relation newRelation) {
    dataMap.insert(std::pair<std::string, Relation>(newKey, newRelation));
}

std::string Database::PrintDatabase() {
    std::string retString = "";
    for (auto it = dataMap.cbegin(); it != dataMap.cend(); ++it) {
        retString.append(it->first + " " + it->second.PrintRelation() + "\n");
    }
    return retString;

}

void Database::AddTuplesToRelation(std::string headerName, Tuple newTuple) {
    for (auto it = dataMap.cbegin(); it != dataMap.cend(); ++it) {
        if (it->first == headerName) {
            dataMap[it->first].AddTuple(newTuple);
            break;
        }
    }
}

Relation Database::FindRelationByName(std::string name) {
    return dataMap.find(name)->second;
}

std::map<std::string, Relation> Database::GetMap() {
    return dataMap;
}