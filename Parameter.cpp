#include "Parameter.h"

Parameter::Parameter() {
    para = "";
}

Parameter::Parameter(std::string newPara) {
    para = newPara;
}

std::string Parameter::ParameterToString() {
    return para;
}
void Parameter::SetParameter(std::string newPara) {
    para = newPara;
}
