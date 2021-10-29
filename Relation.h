#ifndef PROJECT1_STARTER_CODE_RELATION_H
#define PROJECT1_STARTER_CODE_RELATION_H

#include <set>
#include "Tuple.h"
#include "Header.h"

class Relation {
private:
    std::set<Tuple> tupleSet;
    Header relHeader; // consists of a vector of strings

public:
    Relation();
    Relation(Header theHeader);
    Relation(std::set<Tuple> theTupleSet);
    Relation(Header newHeader, std::set<Tuple> newTupleSet);
    void AddTuple(Tuple newTuple);
    Header GetHeader();
    Relation* Select(int index, std::string value);
    Relation* Select(int index1, int index2);
    Relation Project(std::vector<int> indices);
    Relation Rename(std::vector<std::string> newAttributes);
    std::string PrintRelation(int index = 0) const;
    int GetNumTuples() const;

};

#endif //PROJECT1_STARTER_CODE_RELATION_H
