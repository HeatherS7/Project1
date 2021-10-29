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

Relation* Relation::Select(int index, std::string value) {
    std::set<Tuple>::iterator it = tupleSet.begin();
    Relation* newRel = new Relation(relHeader);

    while (it != tupleSet.end()) {
        if (it->GetValueAtIndex(index) == value) {
            newRel->AddTuple(*it);
        }

        it++;
    }

    return newRel;
}

Relation* Relation::Select(int index1, int index2) {
    std::set<Tuple>::iterator it = tupleSet.begin();
    Relation* newRel = new Relation(relHeader);

    while (it != tupleSet.end()) {
        if (it->GetValueAtIndex(index1) == it->GetValueAtIndex(index2)) {
            newRel->AddTuple(*it);
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
            tupleValues.push_back(it->GetValueAtIndex(indices.at(i)));
        }
        newRel.AddTuple(Tuple(tupleValues));
        it++;
    }

    return newRel;

}

Relation Relation::Rename(std::vector<std::string> newAttributes) {
    Relation newRel = Relation(Header(newAttributes),tupleSet);

    //newRel.GetHeader().SetHeaderAttributes(newAttributes);

    return newRel;
}

std::string Relation::PrintRelation(int index) const {
    std::string retString = "";
    std::set<Tuple>::iterator it = tupleSet.begin();

    if (relHeader.GetNumAttributes() > 0) {
        retString.append("\n");
    }

        /*while (it != tupleSet.end()) {
            retString.append(relHeader.PrintAttributes() + it->PrintTuple() + "\n");
            it++;
        }*/
    while (it != tupleSet.end()) {
        retString.append("  ");
        for (int i = 0; i < relHeader.GetNumAttributes(); i++) {
            retString.append(relHeader.GetAttributeAtIndex(i) + "=" + it->GetValueAtIndex(i));
            if (i < relHeader.GetNumAttributes() - 1) {
                retString.append(", ");
            } else {
                retString.append("\n");
            }
        }
        it++;
    }
    if (relHeader.GetNumAttributes() == 0) {
        retString.append("\n");
    }
    return retString;
}

int Relation::GetNumTuples() const {
    return tupleSet.size();
}
