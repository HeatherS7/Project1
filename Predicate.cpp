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
unsigned int Predicate::GetNumParameters() const {
    return parameters.size(); //numParameters;
}
void Predicate::AddParameter(Parameter* newPara) {
    parameters.push_back(newPara);
}
void Predicate::AddParameter(std::vector<Parameter*> newParameters) {
    for (unsigned int i=0; i<newParameters.size(); i++) {
        parameters.push_back(newParameters.at(i));
    }
}

std::string Predicate::GetId() const {
    return id;
}

std::vector<std::string> Predicate::GetParameters() const {
    std::vector<std::string> returnVector = {};
    for (unsigned int i = 0; i < parameters.size(); i++) {
        returnVector.push_back(parameters.at(i)->ParameterToString());
    }
    return returnVector;
}

std::string Predicate::GetParameterAtIndex(int index) const {
    return parameters.at(index)->ParameterToString();
}

bool Predicate::GetParameterAtIndexIsId(int index) const {
    return parameters.at(index)->GetIsId();
}