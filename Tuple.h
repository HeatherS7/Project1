#ifndef PROJECT1_STARTER_CODE_TUPLE_H
#define PROJECT1_STARTER_CODE_TUPLE_H

#include <vector>
#include <string>

class Tuple {
private:
    std::vector<std::string> values;

public:
    Tuple();
    Tuple(std::vector<std::string> newValues);
    bool operator< (const Tuple &rhs) const;
    std::string PrintTuple() const;
    std::string GetValueAtIndex(int index) const;
    void SetTuple(std::vector<std::string> newValues);
    int GetNumValues() const;
    std::vector<std::string> GetValues() const;


};

#endif //PROJECT1_STARTER_CODE_TUPLE_H
