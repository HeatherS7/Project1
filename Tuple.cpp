#include "Tuple.h"

Tuple::Tuple() {
    values = {};
}

Tuple::Tuple(std::vector<std::string> newValues) {
    values = newValues;
}

bool Tuple::operator< (const Tuple &rhs) const {
    return values < rhs.values;
}

std::string Tuple::PrintTuple() const {
    std::string ret = "";
    for (unsigned int i = 0; i < values.size(); i++) {
        ret.append(values.at(i));
        if (i < values.size()-1) {
            ret.append(", ");
        }
    }
    return ret;
}

std::string Tuple::GetValueAtIndex(int index) const {
    return values.at(index);
}

void Tuple::SetTuple(std::vector<std::string> newValues) {
    values = newValues;
}

int Tuple::GetNumValues() const {
    return values.size();
}

std::vector<std::string> Tuple::GetValues() const {
    return values;
}