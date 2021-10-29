#include "Parameter.h"

Parameter::Parameter() {
    para = "";
}

Parameter::Parameter(std::string newPara, bool isId) {
    para = newPara;
    this->isId = isId;
}

std::string Parameter::ParameterToString() {
    return para;
}
void Parameter::SetParameter(std::string newPara) {
    para = newPara;
}

bool Parameter::GetIsId() {
    return isId;
}
