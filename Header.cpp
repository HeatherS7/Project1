#include "Header.h"

Header::Header() {
    attributes = {};
}

Header::Header(std::vector<std::string> newAttributes) {
    attributes = newAttributes;
}

std::string Header::PrintAttributes() const {
    std::string ret = "";
    for (unsigned int i = 0; i < attributes.size(); i++) {
        ret.append("  " + attributes.at(i) + "=");
    }
    return ret;
}

void Header::SetHeaderAttributes(std::vector<std::string> newAttributes) {
    if (attributes.size() < newAttributes.size()) {
        throw std::exception();
    }

    for (unsigned int i = 0; i < newAttributes.size(); i++) {
        attributes.at(i) = newAttributes.at(i);
    }

}

std::string Header::GetAttributeAtIndex(int index) const {
    return attributes.at(index);
}

int Header::GetNumAttributes() const {
    return attributes.size();
}