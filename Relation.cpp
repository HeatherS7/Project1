#include "Relation.h"

Relation::Relation() {
    tupleSet = {};
    relHeader = Header();
}

Relation::Relation(Header theHeader) {
    relHeader = theHeader;
    tupleSet = {};
}

Relation::Relation(std::set<Tuple> theTupleSet) {
    tupleSet = theTupleSet;
    relHeader = Header();
}

Relation::Relation(Header newHeader, std::set<Tuple> newTupleSet) {
    relHeader = newHeader;
    tupleSet = newTupleSet;
}

void Relation::AddTuple(Tuple newTuple) {
    tupleSet.insert(newTuple);
}

Header Relation::GetHeader() {
    return relHeader;
}

Relation Relation::Select(int index, std::string value) {
    std::set<Tuple>::iterator it = tupleSet.begin();
    Relation newRel = Relation(relHeader);

    while (it != tupleSet.end()) {
        if (it->GetValueAtIndex(index) == value) {
            newRel.AddTuple(*it);
        }

        it++;
    }

    return newRel;
}

Relation Relation::Select(int index1, int index2) {
    std::set<Tuple>::iterator it = tupleSet.begin();
    Relation newRel = Relation(relHeader);

    while (it != tupleSet.end()) {
        if (it->GetValueAtIndex(index1) == it->GetValueAtIndex(index2)) {
            newRel.AddTuple(*it);
        }
        it++;
    }

    return newRel;

}

Relation Relation::Project(std::vector<int> indices) {
    std::set<Tuple>::iterator it = tupleSet.begin();
    std::vector<std::string> newHeader = {};
    for (unsigned int i = 0; i < indices.size(); i++) {
        newHeader.push_back(relHeader.GetAttributeAtIndex(indices.at(i)));
    }
    Relation newRel = Relation(Header(newHeader));
    while (it != tupleSet.end()) {
        std::vector<std::string> tupleValues = {};
        for (unsigned int i = 0; i < indices.size(); i++) {
            tupleValues.push_back(it->GetValueAtIndex(i));
        }
        newRel.AddTuple(Tuple(tupleValues));
        it++;
    }

    return newRel;

}

Relation Relation::Rename(std::vector<std::string> newAttributes) {
    Relation newRel = Relation(tupleSet);

    newRel.GetHeader().SetHeaderAttributes(newAttributes);

    return newRel;
}

std::string Relation::PrintRelation() const {
    std::string retString = relHeader.PrintAttributes();
    // TODO: add functionality to print the tupleSet
    return retString;
}
