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
    std::string PrintAttributes();
    void SetHeaderAttributes(std::vector<std::string> newAttributes);
    std::string GetAttributeAtIndex(int index);

};

#endif //PROJECT1_STARTER_CODE_HEADER_H
