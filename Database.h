#ifndef PROJECT1_STARTER_CODE_DATABASE_H
#define PROJECT1_STARTER_CODE_DATABASE_H

#include <map>
#include <string>
#include "Relation.h"

class Database {
private:
    std::map<std::string, Relation> dataMap;

public:
    Database();
    void AddMappedRelationship(std::string, Relation);

};

#endif //PROJECT1_STARTER_CODE_DATABASE_H
