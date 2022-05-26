#ifndef _REJECTTYPE_MODEL_H_
#define _REJECTTYPE_MODEL_H_

#include <string>
#include <memory>

using namespace std;

class RejectTypeModel {

private:
    int code = 0;
    string name = "";
    string storageSpecification = "";
    int parentRejTypeCode = 0;
    shared_ptr<RejectTypeModel> parentRejType = nullptr;

public:
    RejectTypeModel(void) {};

    // Codigo
    int getCode() const { return code; }
    void setCode(int code) { this->code = code; }

    // Nome
    const string getName() const { return name; }
    void setName(const string name) { this->name = name; }

    // Instrucoes de armazenamento
    const string getStorageSpecification() const { return storageSpecification; }
    void setStorageSpecification(const string storageSpecification) { this->storageSpecification = storageSpecification; }

    // Tipo de Residuo 'pai'
    shared_ptr<RejectTypeModel> getParentRejType() const { return this->parentRejType; }
    void setParentRejType(const shared_ptr<RejectTypeModel> parentRejType) { this->parentRejType = parentRejType; }

    int getParentRejTypeCode() const { return this->parentRejTypeCode; }
    void setParentRejTypeCode(int code) { this->parentRejTypeCode = code; }
};

#endif