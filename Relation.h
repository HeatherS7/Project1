#ifndef PROJECT1_STARTER_CODE_RELATION_H
#define PROJECT1_STARTER_CODE_RELATION_H

#include <set>
#include "Tuple.h"
#include "Header.h"

class Relation {
private:
    std::set<Tuple> tupleSet;
    Header relHeader;

public:
    Relation();
    Relation(Header theHeader);
    Relation(std::set<Tuple> theTupleSet);
    Relation(Header newHeader, std::set<Tuple> newTupleSet);
    void AddTuple(Tuple newTuple);
    Header GetHeader();
    // will need classes select, select, project, rename
    Relation Select(int index, std::string value);
    Relation Select(int index1, int index2);
    Relation Project(std::vector<int> indices);
    Relation Rename(std::vector<std::string> newAttributes);

};

/* TODO:
 * 1. Pass the Datalog program to the interpreter
 * 2. Get the testing working -- make sure the methods and classes work
 * 3. Get the queries working
 * */

#endif //PROJECT1_STARTER_CODE_RELATION_H
