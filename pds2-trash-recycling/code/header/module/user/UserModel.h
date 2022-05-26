#ifndef _USER_MODEL_H_
#define _USER_MODEL_H_

#include <string>
#include <vector>

#include "../reject-type/RejectTypeModel.h"
#include "../../common/interface/IModel.h"
#include "../../common/enums.h"

using namespace std;

class UserModel: public IModel {

private:
    int code = 0;
    string cpfCnpj = "";
    int type = 0;
    string name = "";
    vector<int> rejTypesOfInterestCodes;

public:

    UserModel(void) {};
    void rename(void) override {};

    // Codigo
    int getCode() const { return code; }
    void setCode(int code) { this->code = code; }

    // Cpf/Cnpj
    const string &getCpfCnpj() const { return cpfCnpj; }
    void setCpfCnpj(const string &cpfCnpj) { this->cpfCnpj = cpfCnpj; }

    // Tipo
    int getType() const { return this->type; }
    void setType(UserTypeEnum type) { this->type = type; }

    // Nome
    const string &getName() const { return name; }
    void setName(const string &name) { this->name = name; }

    // Lista de Residuos
    void resetRejectTypesOfInterest(void) { this->rejTypesOfInterestCodes = vector<int>(); };
    void addRejectTypeOfInterest(int rejTypeCode) { this->rejTypesOfInterestCodes.push_back(rejTypeCode); };
    const vector<int> getRejectTypesOfInterestCodes() const { return rejTypesOfInterestCodes; }
};

#endif