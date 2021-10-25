#include "Database.h"

Database::Database() {
    dataMap = {};
}

void Database::AddMappedRelationship(std::string newKey, Relation newRelation) {
    dataMap.insert(std::pair<std::string, Relation>(newKey, newRelation));
}
