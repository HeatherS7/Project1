#ifndef PROJECT1_STARTER_CODE_PARAMETER_H
#define PROJECT1_STARTER_CODE_PARAMETER_H

#include <string>

class Parameter {
private:
    std::string para;
    bool isId;

public:
    Parameter();
    Parameter(std::string newPara, bool isId = false);
    std::string ParameterToString();
    void SetParameter(std::string newPara);
    bool GetIsId();

};

#endif //PROJECT1_STARTER_CODE_PARAMETER_H
