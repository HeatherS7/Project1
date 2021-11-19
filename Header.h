#ifndef PROJECT1_STARTER_CODE_HEADER_H
#define PROJECT1_STARTER_CODE_HEADER_H

#include <vector>
#include <string>

class Header {
private:
    std::vector<std::string> attributes;

public:
    Header();
    Header(std::vector<std::string> newAttributes);
    std::string PrintAttributes() const;
    void SetHeaderAttributes(std::vector<std::string> newAttributes);
    std::string GetAttributeAtIndex(int index) const;
    std::vector<std::string> GetAttributes();
    int GetNumAttributes() const;

};

#endif //PROJECT1_STARTER_CODE_HEADER_H
