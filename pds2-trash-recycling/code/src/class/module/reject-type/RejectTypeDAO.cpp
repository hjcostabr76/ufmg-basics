#ifndef _REJECTTYPE_DAO_CPP_
#define _REJECTTYPE_DAO_CPP_

#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "../../../../header/common/FindResult.h"
#include "../../../../header/common/class/DAO.h"
#include "../../../../header/module/reject-type/RejectTypeDAO.h"
#include "../../../../header/module/reject-type/RejectTypeService.h"
#include "../../../../header/module/reject-type/RejectTypeModel.h"

using namespace std;

const string RejectTypeDAO::STORAGE_FILE = "reject-type.txt";

void RejectTypeDAO::writeRegisterIntoStorage(shared_ptr<RejectTypeModel> rejectType) {

    this->openStorageForWriting();

    this->writingStream
            << rejectType->getCode() << ";"
            << rejectType->getName() << ";"
            << rejectType->getStorageSpecification() << ";"
            << rejectType->getParentRejTypeCode() << ";"
            << endl;
}

string RejectTypeDAO::getStorageFileName(void) {
    return RejectTypeDAO::STORAGE_FILE;
};

shared_ptr<RejectTypeModel> RejectTypeDAO::insert(const shared_ptr<RejectTypeModel> rejectType) {

    // Validacao
    if (rejectType == nullptr) throw invalid_argument("Dados nao informados");

    auto existingRejTypeSearch = this->findOne(rejectType->getCode());
    auto existingRejType = existingRejTypeSearch.foundRegister;

    if (existingRejType != nullptr) throw domain_error("Tipo de Residuo ja existe");

    // Add
    this->writeRegisterIntoStorage(rejectType);

    // Tudo OK
    return rejectType;
};

shared_ptr<RejectTypeModel> RejectTypeDAO::update(const shared_ptr<RejectTypeModel> rejectType) {

    // Validacao
    if (rejectType == nullptr) throw invalid_argument("Dados insuficientes");
    auto existingRejTypeSearch = this->findOne(rejectType->getCode());
    if (existingRejTypeSearch.foundRegister == nullptr) throw invalid_argument("Tipo de Residuo nao existe");

    // Remove linha defasada, insere nova & retorna objeto valido
    this->deleteOne(existingRejTypeSearch.line);
    this->writeRegisterIntoStorage(rejectType);
    return rejectType;
};

FindResult<RejectTypeModel> RejectTypeDAO::findOne(const int code) {

    // Abre arquivo
    this->openStorageForReading();

    // Inicializa dados de retorno
    FindResult<RejectTypeModel> result;
    result.foundRegister = nullptr;
    result.line = 0;

    // Efetua busca
    int lineCount = 0;
    string fileLine;

    while (getline(this->readingStream, fileLine)) {

        lineCount++;

        // Extrai propriedades da linha
        stringstream ss(fileLine);
        string item;
        vector<string> lineProps;

        while (getline(ss, item, ';')) {
            lineProps.push_back(item);
        }

        // Valida valores extraidos
        if (!this->service->validateStoredRegister(lineProps)) {
            cout << endl << "** WARNING: Cadastro de Tipo de Residuo invalido (linha: " << lineCount << ") **" << endl << endl;
            continue;
        }

        // Verifica se usuario pesquisado foi encontrado
        if (code == stoi(lineProps[0])) {
            result.foundRegister = this->service->getModelFromStorageLine(lineProps);
            result.line = lineCount;
            return result;
        }
    }

    return result;
};

vector<FindResult<RejectTypeModel>> RejectTypeDAO::findAllThatCanBeParent(void) {

    vector<FindResult<RejectTypeModel>> rejTypesThatCanBeParent;
    const auto allRejTypes = this->findAll();

    for (uint i = 0; i < allRejTypes.size(); i++) {
        const auto currentRejTypeResult = allRejTypes[i];
        if (currentRejTypeResult.foundRegister->getParentRejTypeCode()) continue;
        rejTypesThatCanBeParent.push_back(currentRejTypeResult);
    }

    return rejTypesThatCanBeParent;
}

vector<FindResult<RejectTypeModel>> RejectTypeDAO::findAll(void) {

    this->openStorageForReading();

    map<int, shared_ptr<RejectTypeModel>> rejTypesMap;
    vector<FindResult<RejectTypeModel>> foundList;

    int lineCount = 0;
    string fileLine;

    while (getline(this->readingStream, fileLine)) {

        lineCount++;

        // Extrai propriedades da linha
        stringstream ss(fileLine);
        string item;
        vector<string> lineProps;

        while (getline(ss, item, ';'))
            lineProps.push_back(item);

        // Valida valores extraidos
        if (!this->service->validateStoredRegister(lineProps)) {
            cout << endl << "** WARNING: Cadastro de Tipo de Residuo invalido (linha: " << lineCount << ") **" << endl << endl;
            continue;
        }

        // Add item na lista de retorno
        FindResult<RejectTypeModel> result;
        const auto rejType = this->service->getModelFromStorageLine(lineProps);

        result.foundRegister = rejType;
        result.line = lineCount;

        foundList.push_back(result);
        rejTypesMap[rejType->getCode()] = rejType;
    }

    // Monta lista definitiva a ser retornada
    vector<FindResult<RejectTypeModel>> returnList;

    for (uint i = 0; i < foundList.size(); i++) {

        const auto foundRejType = foundList[i];
        const shared_ptr<RejectTypeModel> &currentRejType = foundRejType.foundRegister;

        if (currentRejType->getParentRejTypeCode() != 0) {

            const auto parentRejTypeSearch = rejTypesMap.find(currentRejType->getParentRejTypeCode());

            if (parentRejTypeSearch == rejTypesMap.end()) {
                cout << endl << "** WARNING: Cadastro de Tipo de Residuo invalido (linha: " << foundRejType.line << ") **" << endl << endl;
                continue;
            }

            currentRejType->setParentRejType(parentRejTypeSearch->second);
        }

        returnList.push_back(foundRejType);
    }

    return returnList;
};

#endif