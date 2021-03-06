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
    std::string PrintDatabase();
    void AddTuplesToRelation(std::string headerName, Tuple newTuple);
    Relation* FindRelationByName(std::string name);
    std::map<std::string, Relation> GetMap();
    int GetNumTuplesInDatabase() const;

};

#endif //PROJECT1_STARTER_CODE_DATABASE_H
