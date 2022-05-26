#ifndef _USER_DAO_CPP_
#define _USER_DAO_CPP_

#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../../../../header/common/FindResult.h"
#include "../../../../header/common/class/DAO.h"
#include "../../../../header/module/user/UserDAO.h"
#include "../../../../header/module/user/UserService.h"

using namespace std;

const string UserDAO::STORAGE_FILE = "user.txt";

string UserDAO::getStorageFileName(void) {
    return UserDAO::STORAGE_FILE;
};

FindResult<UserModel> UserDAO::findOne(const int code, const string cpfCnpj) {

    // Abre arquivo
    this->openStorageForReading();

    // Inicializa dados de retorno
    FindResult<UserModel> result;
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
            cout << endl << "** WARNING: Cadastro de usuário invalido (linha: " << lineCount << ") **" << endl << endl;
            continue;
        }

        // Verifica se usuario pesquisado foi encontrado
        if (code == stoi(lineProps[0]) || cpfCnpj == lineProps[1]) {
            result.foundRegister = this->service->getModelFromStorageLine(lineProps);
            result.line = lineCount;
            return result;
        }
    }

    return result;
};

FindResult<UserModel> UserDAO::findOne(const string cpfCnpj) {
    return this->findOne(0, cpfCnpj);
};

FindResult<UserModel> UserDAO::findOne(const int code) {
    return this->findOne(code, "");
};

shared_ptr<UserModel> UserDAO::insert(const shared_ptr<UserModel> user) {

    // Validacao
    if (user == nullptr) throw invalid_argument("Falha ao tentar inserir usuario cujo os dados nao foram informados");

    auto existingUserSearch = this->findOne(user->getCode(), user->getCpfCnpj());
    auto existingUser = existingUserSearch.foundRegister;

    if (existingUser != nullptr) throw domain_error("Tentativa de inserir usuario que ja existe");

    // Add usuario
    this->writeRegisterIntoStorage(user);

    // Tudo OK
    return user;
};

shared_ptr<UserModel> UserDAO::update(const shared_ptr<UserModel> user) {

    if (user == nullptr) throw invalid_argument("Dados insuficientes");

    // Verifica SE usuario existe
    auto existingUserSearch = this->findOne(user->getCode());
    if (existingUserSearch.foundRegister == nullptr) throw invalid_argument("Usuario nao existe");

    // Verifica SE cpf/cnpj esta disponivel
    auto docValidationSearch = this->findOne(user->getCpfCnpj());
    auto docValidationFoundUser = existingUserSearch.foundRegister;

    if (docValidationFoundUser != nullptr && docValidationFoundUser->getCode() != user->getCode())
        throw domain_error("Dados repetidos");

    // Remove linha atual do usuario
    this->deleteOne(existingUserSearch.line);

    // Add nova linha para usuario
    this->writeRegisterIntoStorage(user);

    // Tudo OK
    return user;
};

void UserDAO::writeRegisterIntoStorage(shared_ptr<UserModel> user) {

    this->openStorageForWriting();

    this->writingStream
        << user->getCode() << ";"
        << user->getCpfCnpj() << ";"
        << user->getType() << ";"
        << user->getName() << ";";

    for (uint i = 0; i < user->getRejectTypesOfInterestCodes().size(); i++) {
        if (i > 0) this->writingStream << ",";
        this->writingStream << user->getRejectTypesOfInterestCodes()[i];
    }

    this->writingStream << ";" << endl;
};

vector<FindResult<UserModel>> UserDAO::findAll(void) {

    this->openStorageForReading();

    vector<FindResult<UserModel>> returnList;
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
            cout << endl << "** WARNING: Cadastro de Usuario invalido (linha: " << lineCount << ") **" << endl << endl;
            continue;
        }

        // Add item na lista de retorno
        FindResult<UserModel> result;
        result.foundRegister = this->service->getModelFromStorageLine(lineProps);
        result.line = lineCount;
        returnList.push_back(result);
    }

    return returnList;
};

vector<FindResult<UserModel>> UserDAO::findAllByType(const UserTypeEnum type) {

    this->openStorageForReading();

    vector<FindResult<UserModel>> returnList;
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
            cout << endl << "** WARNING: Cadastro de Usuario invalido (linha: " << lineCount << ") **" << endl << endl;
            continue;
        }

        // Valida se registro eh do tipo desejado
        const auto user = this->service->getModelFromStorageLine(lineProps);
        if (user->getType() != type) continue;

        // Add item na lista de retorno
        FindResult<UserModel> result;
        result.foundRegister = user;
        result.line = lineCount;
        returnList.push_back(result);
    }

    return returnList;
};

vector<FindResult<UserModel>> UserDAO::findAllDonators(void) {
    return this->findAllByType(UserTypeEnum::DONATOR);
};

vector<FindResult<UserModel>> UserDAO::findAllReceivers(void) {
    return this->findAllByType(UserTypeEnum::RECEIVER);
};

#endif