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

bool Relation::AddTuple(Tuple newTuple) {
    bool isInSet = false;
    if (tupleSet.find(newTuple) != tupleSet.end()) {
        isInSet = true;
    }
    tupleSet.insert(newTuple);
    return isInSet;
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

Relation* Relation::Project(std::vector<int> indices) {
    std::set<Tuple>::iterator it = tupleSet.begin();
    std::vector<std::string> newHeader = {};
    for (unsigned int i = 0; i < indices.size(); i++) {
        newHeader.push_back(relHeader.GetAttributeAtIndex(indices.at(i)));
    }
    Relation* newRel = new Relation(Header(newHeader));
    while (it != tupleSet.end()) {
        std::vector<std::string> tupleValues = {};
        for (unsigned int i = 0; i < indices.size(); i++) {
            tupleValues.push_back(it->GetValueAtIndex(indices.at(i)));
        }
        newRel->AddTuple(Tuple(tupleValues));
        it++;
    }

    return newRel;

}

Relation* Relation::Rename(std::vector<std::string> newAttributes) {
    Relation* newRel = new Relation(Header(newAttributes),tupleSet);

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

Relation* Relation::Union(Relation *rel1, Relation *rel2, bool printNewTuples) {
    std::set<Tuple>::iterator it1 = rel1->tupleSet.begin();

    while (it1 != rel1->tupleSet.end()) {
        bool isInSet = rel2->AddTuple(*it1);
        if ((!isInSet) && printNewTuples) {
            std::string retString = "";
            for (int i = 0; i < rel1->GetHeader().GetNumAttributes(); i++) {
                if (i == 0) {
                    retString.append("  ");
                }
                retString.append(rel1->GetHeader().GetAttributeAtIndex(i) + "=" + it1->GetValueAtIndex(i));
                if (i < rel1->GetHeader().GetNumAttributes() - 1) {
                    retString.append(", ");
                } else {
                    retString.append("\n");
                }
            }
            std::cout << retString;
        }
        it1++;
    }
    return rel2;
}

Relation* Relation::NaturalJoin(Relation *rel1, Relation *rel2) {
    Relation* newRel = new Relation();
    // make the header h for the result relation
    //	    (combine r1's header with r2's header)
    std::vector<std::string> newHeadAttributes = {};
    std::vector<int> colsRel1Same = {};
    std::vector<int> colsRel2Same = {};
    for (unsigned int i = 0; i < rel1->GetHeader().GetNumAttributes(); i++) {
        std::vector<std::string> rel2Headers = rel2->GetHeader().GetAttributes();
        newHeadAttributes.push_back(rel1->GetHeader().GetAttributeAtIndex(i));
        auto it = std::find(rel2Headers.begin(), rel2Headers.end(),
                            rel1->GetHeader().GetAttributeAtIndex(i));
        if (it != rel2Headers.end()) {
            colsRel1Same.push_back(i);
            colsRel2Same.push_back(it - rel2Headers.begin());
        }
    }
    for (unsigned int i = 0; i < rel2->GetHeader().GetNumAttributes(); i++) {
        auto it = std::find(newHeadAttributes.begin(), newHeadAttributes.end(),
                            rel2->GetHeader().GetAttributeAtIndex(i));
        if (it == newHeadAttributes.end()) {
            newHeadAttributes.push_back(rel2->GetHeader().GetAttributeAtIndex(i));
        }
    }
    newRel->relHeader = Header(newHeadAttributes);

    // for each tuple t1 in r1
    //	    for each tuple t2 in r2
    //
    //		if t1 and t2 can join
    //		    join t1 and t2 to make tuple t
    //		    add tuple t to relation r
    //		end if
    //
    //	    end for
    //	end for

    bool commonAttr = colsRel1Same.size() > 0 ? true : false;
    bool sameAttr = (rel1->relHeader.GetNumAttributes() == rel2->relHeader.GetNumAttributes())
            ? (rel1->relHeader.GetNumAttributes() == colsRel1Same.size()) ? true : false : false;

    std::vector<std::string> newTuple = {};
    std::set<Tuple>::iterator it1 = rel1->tupleSet.begin();
    while (it1 != rel1->tupleSet.end()) {
        std::set<Tuple>::iterator it2 = rel2->tupleSet.begin();
        while (it2 != rel2->tupleSet.end()) {

            // Case 1: No common attributes
            if (!commonAttr) {
                std::vector<std::string> values = it1->GetValues();
                newTuple.insert(newTuple.begin(), values.begin(), values.end());
                values.empty();
                values = it2->GetValues();
                newTuple.insert(newTuple.end(), values.begin(), values.end());
                newRel->AddTuple(Tuple(newTuple));
                newTuple.clear();
            }
            // Case 2: All the same attributes
            else if (sameAttr) {
                newRel->Union(rel1, rel2);
            }
            // Case 3: Some common, but not all
            else {
                bool canCombine = false;
                for (unsigned int i = 0; i < colsRel1Same.size(); i++) {
                    if (it1->GetValueAtIndex(colsRel1Same.at(i)) == it2->GetValueAtIndex(colsRel2Same.at(i))) {
                        canCombine = true;
                    } else {
                        canCombine = false;
                        break;
                    }
                }
                if (canCombine) {
                    std::vector<std::string> values = it1->GetValues();
                    newTuple.insert(newTuple.begin(), values.begin(), values.end());
                    /*for (unsigned int i = 0; i < colsRel1Same.size(); i++) {
                        newTuple.erase(newTuple.begin() + (colsRel1Same.at(i) - i));
                    }*/
                    values.empty();
                    values = it2->GetValues();
                    newTuple.insert(newTuple.end(), values.begin(), values.end());
                    for (unsigned int i = 0; i < colsRel2Same.size(); i++) {
                        newTuple.erase(newTuple.begin() + it1->GetNumValues() + colsRel2Same.at(i) - i);
                    }
                    newRel->AddTuple(Tuple(newTuple));
                    newTuple.clear();
                }
            }

            it2++;
        }
        it1++;
    }


    return newRel;
}

