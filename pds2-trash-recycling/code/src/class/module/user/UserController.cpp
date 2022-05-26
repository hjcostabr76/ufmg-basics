#ifndef _USER_CONTROLLER_CPP_
#define _USER_CONTROLLER_CPP_

#include <memory>
#include <functional>
#include <map>
#include <algorithm>
#include <sstream>
#include "../../../../header/module/user/UserController.h"
#include "../../../../header/module/user/UserModel.h"
#include "../../../../header/common/enums.h"

using namespace std;

bool UserController::setCurrentUserPersonType(void) {

    bool reapeat = false;
    bool tried = false;
    string readInput;
    int number;

    do {

        // Notifica tentativa invalida (se necessario)
        if (tried) cout << "'" << readInput <<"' nao e um tipo valido!" << endl << endl;
        tried = true;

        // Captura entrada
        cout << "Informe o tipo de pessoa do cadastro (pf/pj): ";
        cin >> readInput;
        cin.ignore();
        reapeat = (readInput != "pf" && readInput != "pj" && readInput != "0");

    } while (reapeat);

    if (readInput == "0") return false;

    // Tudo OK
    this->currentUserType = (readInput == "pf")
        ? make_shared<PersonTypeEnum>(PersonTypeEnum ::PF)
        : make_shared<PersonTypeEnum>(PersonTypeEnum ::PJ);

    return true;
};

bool UserController::setCurrentUserCpfOrCnpj(void) {

    string docType = (*this->currentUserType == PersonTypeEnum::PF) ? "CPF" : "CNPJ";

    string readInput = "";
    bool tried = false;
    bool reapeat = false;

    do {

        // Notifica tentativa invalida (se necessario)
        if (tried) cout << docType << " invalido!" << endl << endl;
        tried = true;
        reapeat = false;

        // Captura entrada
        cout << "Informe " << docType << " do usuario (apenas numeros): ";
        cin >> readInput;

        // Verifica se usuario solicitou 'sair'
        if (readInput == "0") return false;

        // Valida entrada (comprimento)
        if ((*this->currentUserType == PersonTypeEnum::PF && readInput.length() != 11)
            || (*this->currentUserType == PersonTypeEnum::PJ && readInput.length() != 14)
        ) {
            reapeat = true;
            continue;
        }

        // Valida entrada (conteudo)
        for (uint i = 0; i < readInput.length(); i++) {
            if (isdigit(readInput[i])) continue;
            reapeat = true;
            break;
        }

    } while (reapeat);

    // Tudo OK
    this->currentUser->setCpfCnpj(readInput);
    return true;
};

bool UserController::setCurrentUserType(void) {

    string readInput = "";
    bool tried = false;

    // Monta estrutura para exibir opcoes
    vector<UserTypeEnum> userTypesList;
    map<UserTypeEnum, int> typeCodeMap;

    userTypesList.push_back(UserTypeEnum::RECEIVER);
    typeCodeMap[UserTypeEnum::RECEIVER] = 1;

    userTypesList.push_back(UserTypeEnum::DONATOR);
    typeCodeMap[UserTypeEnum::DONATOR] = 2;

    do {

        // Notifica tentativa invalida (se necessario)
        if (tried) cout << "Tipo invalido!" << endl << endl;
        tried = true;

        // Exibir opcoes
        cout << "Selecione um tipo de usuario: " << endl;

        function<void(UserTypeEnum)> showOneOption = [&typeCodeMap, this] (const UserTypeEnum userType) {
            cout << "\t" << typeCodeMap.find(userType)->second
                << " - " << this->service->getUserTypeLabel(userType) << endl;
        };

        for_each (userTypesList.begin(), userTypesList.end(), showOneOption);

        // Capturar entrada
        cin >> readInput;
        cout << endl;
        if (readInput == "0") return false;

        // Validar entrada: Tipo
        int selectedTypeCode;

        try {
            selectedTypeCode = stoi(readInput);

        } catch (exception error) {
            continue;
        }

        for (uint i = 0; i < userTypesList.size(); i++) {

            // Validar entrada: Valor
            const UserTypeEnum validUserType = userTypesList[i];
            const int validTypeCode = typeCodeMap.find(validUserType)->second;
            if (selectedTypeCode != validTypeCode) continue;

            // Opcao valida informada!
            this->currentUser->setType(validUserType);
            cout << "Tipo selecionado: " << this->service->getUserTypeLabel(validUserType) << endl << endl;
            return true;
        }

    } while (true);
};

bool UserController::setCurrentUserName(void) {
    const string readInput = this->getStringFromStdIO("Informe nome do usuario: ");
    if (readInput == "0") return false;
    this->currentUser->setName(readInput);
    return true;
};

void UserController::setCurrentUserRejTypeList(void) {

    // Confirma intencao alterar essa lista
    cout << endl;
    const bool update = this->aksYesOrNoQuestionThroughStdIO("Deseja alterar lista de Tipos de Residuo de interesse?");
    if (!update) return;

    // Exibe opcoes disponiveis
    cout << ">> Tipos de Residuo disponiveis: " << endl;
    const auto rejTypesSearch = this->rejTypeDao->findAll();
    this->rejTypeService->showRegistersListData(rejTypesSearch);

    // Captura selecao do usuario
    vector<int> selectedCodes;

    do {

        // Captura
        const string selectedCodesStr = this->getStringFromStdIO("Insira lista de codigos (separados por virgula): ");

        stringstream ss(selectedCodesStr);
        string item;
        bool error = false;

        while (getline(ss, item, ',')) {

            try {

                const int code = stoi(item);
                const auto existanceTestSearch = this->rejTypeDao->findOne(code);

                if (existanceTestSearch.foundRegister == nullptr) {
                    cout << "Tipo de Residuo de codigo '" << code << "' nao existe" << endl;
                    error = true;
                    continue;
                }

                selectedCodes.push_back(code);

            } catch (exception err) {
                cout << "Valor invalido: '" << item << "'" << endl;
                error = true;
            }
        }

        // Valida
        if (!error && selectedCodes.size() > 0) break;

        cout << endl;
        const bool tryAgain = this->aksYesOrNoQuestionThroughStdIO("Lista invalida. Deseja tentar novamente?");
        if (!tryAgain) return;

    } while (true);

    cin.ignore();

    // Add tipos de residuo para o usuario
    for (uint i = 0; i < selectedCodes.size(); i++)
        this->currentUser->addRejectTypeOfInterest(selectedCodes[i]);
};

bool UserController::getDataForUserFromStdIo(const bool insert, const bool admin) {

    cout << "pressione '0' para sair" << endl
         << endl;

    if (!this->setCurrentUserPersonType()) return false;

    if (insert) {
        int code = this->getNumberFromStdIO("Informe um Codigo para o usuario", "Codigo invalido");
        if (!code) return false;
        this->currentUser->setCode(code);
    }

    if (!this->setCurrentUserCpfOrCnpj()) return false;
    if (!admin && !this->setCurrentUserType()) return false;
    if (!this->setCurrentUserName()) return false;
    this->setCurrentUserRejTypeList();

    return true;
};

bool UserController::create(void) {

    do {

        cout << "> CADASTRO" << endl;

        this->currentUser = make_shared<UserModel>();
        this->currentUserType = nullptr;

        if (!this->getDataForUserFromStdIo(true, false)) return false;

        try {
            this->dao->insert(this->currentUser);
            cout << "Usuario criado com sucesso!" << endl;
            return true;

        } catch (invalid_argument error) {
            cout << "Ops! Dados de usuario invalidos" << endl;

        } catch (domain_error error) {
            string docType = (*this->currentUserType == PersonTypeEnum::PF) ? "CPF" : "CNPJ";
            cout << "Ops! Codigo ou " << docType << " ja cadastrado(s) para outro usuario." << endl;

        } catch (exception error) {
            cout << "Falha inesperada ao tentar adicionar usuario" << endl;
        }

        if (!this->aksYesOrNoQuestionThroughStdIO("Realizar nova tentativa?")) return false;

    } while (true);
};

bool UserController::update(shared_ptr<UserModel> currentUser) {

    // Exibir dados atuais
    cout << "Dados atuais cadastrados:" << endl;
    this->service->showDataTableHeader();
    this->service->showRegisterData(currentUser, true);
    cout << endl;

    // Confirmar desejo pela alteracao
    if (!this->aksYesOrNoQuestionThroughStdIO("Alterar cadastro?")) return false;

    do {
        try {

            this->currentUser = currentUser;
            this->currentUserType = nullptr;

            if (!this->getDataForUserFromStdIo(false, (UserTypeEnum)currentUser->getType() == UserTypeEnum::ADMIN))
                return false;

            this->dao->update(this->currentUser);
            cout << "Dados atualizados com sucesso!" << endl;
            return true;

        } catch (invalid_argument error) {
            cout << "Ops! Dados de usuario invalidos" << endl;

        } catch (domain_error error) {
            string docType = (*this->currentUserType == PersonTypeEnum::PF) ? "CPF" : "CNPJ";
            cout << "Ops! " << docType << " ja cadastrado para outro usuario." << endl;

        } catch (exception error) {
            cout << "Falha inesperada ao tentar atualizar usuario" << endl;
        }

        if (!this->aksYesOrNoQuestionThroughStdIO("Realizar nova tentativa?")) return false;

    } while (true);
};

bool UserController::showList(void) const {

    cout << "> USUARIOS" << endl
         << "Pressione '0' para sair..." << endl << endl;

    // Exibe listagem
    this->service->showRegistersListData(this->dao->findAll());

    // Captura acao selecionada pelo usuario
    string action = "";

    const bool remove = this->aksYesOrNoQuestionThroughStdIO("Deseja remover algum Usuario?");
    if (!remove) return false;

    // Seleciona item sobre o qual a acao sera executada
    FindResult<UserModel> userSearch;

    do {

        const int selectedUserCode = this->getNumberFromStdIO("Informe o codigo do Usuario a ser removido", "Codigo invalido: ");
        if (selectedUserCode == 0) return false;

        if (selectedUserCode == 1) {
            cout << "Usuario ADMIN nao pode ser removido" << endl << endl;
            const auto tryAgain = this->aksYesOrNoQuestionThroughStdIO("Deseja tentar novamente?");
            if (!tryAgain) return false;
            continue;
        }

        userSearch = this->dao->findOne(selectedUserCode);

        if (userSearch.foundRegister == nullptr) {
            cout << "Usuario nao encontrado (codigo invalido)" << endl << endl;
            const auto tryAgain = this->aksYesOrNoQuestionThroughStdIO("Deseja tentar novamente?");
            if (!tryAgain) return false;
        }

    } while (userSearch.foundRegister == nullptr);

    // Executa remocao
    this->dao->deleteOne(userSearch.line);
    cout << "Usuario removido com sucesso!" << endl;
    return true;
};

bool UserController::runAction(int action) {

    if (action != ControllerActionEnum::CREATE && action != ControllerActionEnum::RETRIVE)
        throw invalid_argument("Acao invalida para controlador de usuarios (1)");

    bool exit = false;

    switch (action) {
        case ControllerActionEnum::CREATE:
            exit = !this->create();
            break;

        case ControllerActionEnum::RETRIVE:
            exit = !this->showList();
            break;
    }

    if (exit) cout << "Usuario selecionou: 'sair'..." << endl;
    return false;
};

bool UserController::runAction(int action, shared_ptr<UserModel> currentUser) {
    if (action != ControllerActionEnum::UPDATE) throw invalid_argument("Acao invalida para controlador de usuarios (2)");
    if (!this->update(currentUser)) cout << "Usuario selecionou: 'sair'..." << endl;
    return false;
};

#endif