#include "Predicate.h"

Predicate::Predicate() {
    id = "";
    numParameters = 0;
}
Predicate::Predicate(std::string id) {
    this->id = id;
}

Predicate::~Predicate() {
    for (unsigned int i = 0; i<parameters.size(); i++) {
        delete parameters.at(i);
    }
}

std::string Predicate::PredicateToString() {
    std::string retString = id + "(";
    for (unsigned int i = 0; i<parameters.size(); i++) {
        retString.append(parameters.at(i)->ParameterToString());
        if (i<parameters.size()-1) {
            retString.push_back(',');
        }
    }
    retString.push_back(')');

    return retString;

}
void Predicate::SetNumParameters(int num) {
    numParameters += num;
}
int Predicate::GetNumParameters() {
    return numParameters;
}
void Predicate::AddParameter(Parameter* newPara) {
    parameters.push_back(newPara);
}
void Predicate::AddParameter(std::vector<Parameter*> newParameters) {
    for (unsigned int i=0; i<newParameters.size(); i++) {
        parameters.push_back(newParameters.at(i));
    }
}