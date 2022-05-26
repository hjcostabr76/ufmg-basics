#ifndef _SCHEDULING_CONTROLLER_CPP_
#define _SCHEDULING_CONTROLLER_CPP_

#include <sstream>
#include "../../../../header/module/user/UserModel.h"
#include "../../../../header/module/scheduling/SchedulingController.h"
#include "../../../../header/module/scheduling/SchedulingModel.h"

using namespace std;

bool SchedulingController::create(const shared_ptr<UserModel> loggedUser) {

    // Captura listas de opcoes para criar agendamento
    const bool resourcesOk = this->getOptionsForScheduling(loggedUser->getType() == UserTypeEnum::DONATOR);
    if (!resourcesOk) return false;

    bool exit = false;

    do {

        cout << "> NOVO AGENDAMENTO" << endl;
        cout << "pressione '0' para sair" << endl << endl;

        this->currentScheduling = make_shared<SchedulingModel>();

        if (!this->getDataFromStdIo(true, loggedUser)) {
            exit = true;
            break;
        }

        try {
            this->dao->insert(this->currentScheduling);
            cout << endl << "Agendamento criado com sucesso!" << endl;
            break;

        } catch (domain_error error) {
            cout << endl << "Ja existe um agendamento cadastrado com este mesmo codigo" << endl;

        } catch (invalid_argument error) {
            cout << endl << "Ops! Dados invalidos para adicionar agendamento" << endl;

        } catch (exception error) {
            cout << endl << "Falha inesperada ao tentar adicionar Ponto de Coleta" << endl;
        }

        if (this->aksYesOrNoQuestionThroughStdIO("Realizar nova tentativa?")) continue;
        exit = true;
        break;

    } while (true);

    if (exit) cout << "Usuario selecionou: 'sair'..." << endl;
    return false;
};

bool SchedulingController::getOptionsForScheduling(const bool loggedUserIsDonator) {

    const string defaultErrMsg = "Nao eh possivel cadastrar um agendamento, no momento :(\nNao ha ";
    const string errMsgAux = " disponiveis...\n";

    // Pontos de coleta
    this->availableMPoints = this->mPointDao->findAll();

    if (!this->availableMPoints.size()) {
        cout << defaultErrMsg << "Pontos de Coleta" << errMsgAux;
        return false;
    }

    // Tipos de residuo
    this->availableRejTypes = this->rejTypeDao->findAll();

    if (!this->availableRejTypes.size()) {
        cout << defaultErrMsg << "Tipos de Residuo" << errMsgAux;
        return false;
    }

    // Receptores
    if (loggedUserIsDonator) {

        this->availableReceivers = this->userDao->findAllReceivers();

        if (!this->availableReceivers.size()) {
            cout << defaultErrMsg << "Receptores" << errMsgAux;
            return false;
        }
    }

    // Doadores
    if (!loggedUserIsDonator) {

        this->availableDonators = this->userDao->findAllDonators();

        if (!this->availableDonators.size()) {
            cout << defaultErrMsg << "Doadores" << errMsgAux;
            return false;
        }
    }

    return true;
}

bool SchedulingController::getDataFromStdIo(const bool isInsert, const shared_ptr<UserModel> loggedUser) {

    // Captura codigo (se necessario)
    if (isInsert) {
        int code = this->getNumberFromStdIO("Informe um Codigo para o agendamento", "Codigo invalido");
        if (!code) return false;
        this->currentScheduling->setCode(code);
    }

    // Define data
    this->setCurrentSchedulingDate();
    if (this->currentScheduling->getDate() == "") return false;

    // Define ponto de coleta
    this->setCurrentSchedulingMeetingPoint();
    if (!this->currentScheduling->getMeetingPointCode()) return false;

    // Define doador
    this->setCurrentSchedulingUser(loggedUser, true);
    if (!this->currentScheduling->getDonatorCode()) return false;

    // Define recpetor
    this->setCurrentSchedulingUser(loggedUser, false);
    if (!this->currentScheduling->getReceiverCode()) return false;

    // Define Residuos a serem trocados
    this->setCurrentSchedulingRejectsList();
    if (!this->currentScheduling->getRejectsToBeExchangedCodes().size()) return false;

    return true;
};

bool SchedulingController::update(const shared_ptr<UserModel> loggedUser) {

    // Captura listas de opcoes para criar agendamento
    const bool resourcesOk = this->getOptionsForScheduling(loggedUser->getType() == UserTypeEnum::DONATOR);
    if (!resourcesOk) return false;

    cout << endl << "> EDITAR AGENDAMENTO" << endl << endl;

    // Exibir dados atuais
    cout << "Dados atuais cadastrados:" << endl;
    this->service->showDataTableHeader();
    this->service->showRegisterData(this->currentScheduling, true);
    cout << endl;

    // Confirmar desejo pela alteracao
    if (!this->aksYesOrNoQuestionThroughStdIO("Alterar cadastro?")) return false;
    cin.ignore();

    do {
        try {

            if (!this->getDataFromStdIo(false, loggedUser)) return false;

            this->dao->update(this->currentScheduling);
            cout << "Dados atualizados com sucesso!" << endl;
            return true;

        } catch (invalid_argument error) {
            cout << "Ops! Dados de Agendamento invalidos" << endl;

        } catch (exception error) {
            cout << "Falha inesperada ao tentar atualizar Agendamento" << endl;
        }

        if (!this->aksYesOrNoQuestionThroughStdIO("Realizar nova tentativa?")) return false;

    } while (true);
};

bool SchedulingController::changeStatus(void) {

    do {
        try {

            const bool setDone = !this->currentScheduling->isDone();
            this->currentScheduling->setDone(setDone);
            this->dao->update(this->currentScheduling);

            const string aux = setDone ? "Realizado" : "Nao realizado";
            cout << "Status do Agendamento alterado para: " << aux << endl;
            return true;

        } catch (invalid_argument error) {
            cout << "Ops! Dados de Agendamento invalidos" << endl;

        } catch (exception error) {
            cout << "Falha inesperada ao tentar alterar status de um Agendamento" << endl;
        }

        if (!this->aksYesOrNoQuestionThroughStdIO("Realizar nova tentativa?")) return false;

    } while (true);
};

bool SchedulingController::showList(shared_ptr<UserModel> loggedUser) {

    cout << "> MEUS AGENDAMENTOS" << endl
         << "Pressione '0' para sair..." << endl << endl;

    // Exibe listagem
    const auto schedulingList = this->dao->findByUser(loggedUser->getCode());
    this->service->showRegistersListData(schedulingList);
    if (!schedulingList.size()) return true;

    // Captura acao selecionada pelo usuario
    string action = "";

    do {

        if (action != "") cout << "Acao '" << action << "' invalida!" << endl << endl;
        cout << "Pressione 's' (altear status) 'e' (para editar) ou 'r' (para remover): ";

        char readInput[100];
        scanf("%s", &readInput);
        action = string(readInput);

        if (action == "0") return false;

    } while (action != "e" && action != "r" && action != "s");

    const bool changeStatus = (action == "s");
    const bool remove = (action == "r");
    const bool update = (action == "e");

    string actionStr = "EDITAR";

    if (changeStatus) {
        actionStr = "ALTERAR STATUS";

    } else if (remove) {
        actionStr = "REMOVER";
    }

    cout << "Opcao selecionada: " << actionStr << endl << endl;

    // Seleciona item sobre o qual a acao sera executada
    FindResult<SchedulingModel> schedulingSearch;
    string selectionDescMsg = "Informe o codigo do Agendamento a ser ";
    string selectionDescMsgComplement = "editado";

    if (changeStatus) {
        selectionDescMsgComplement = "marcado como realizado/nao realizado";

    } else if (remove) {
        selectionDescMsgComplement = "removido";
    }

    selectionDescMsg += selectionDescMsgComplement;

    do {

        const int selectedSchedulingCode = this->getNumberFromStdIO(selectionDescMsg, "Codigo invalido: ");
        if (selectedSchedulingCode == 0) return false;

        schedulingSearch = this->dao->findOne(selectedSchedulingCode);

        if (schedulingSearch.foundRegister == nullptr) {
            cout << "Agendamento nao encontrado (codigo invalido)" << endl << endl;
            const auto tryAgain = this->aksYesOrNoQuestionThroughStdIO("Deseja tentar novamente?");
            if (!tryAgain) return false;
        }

    } while (schedulingSearch.foundRegister == nullptr);

    // Executa remocao (se necessario)
    if (remove) {
        this->dao->deleteOne(schedulingSearch.line);
        cout << "Agendamento removido com sucesso!" << endl;
        return true;
    }

    // Executa edicao ou alteracao de status
    this->currentScheduling = schedulingSearch.foundRegister;
    return (update) ? this->update(loggedUser) : this->changeStatus();
};

bool SchedulingController::runAction(int action, shared_ptr<UserModel> loggedUser) {

    if (action != ControllerActionEnum::CREATE && action != ControllerActionEnum::RETRIVE)
        throw invalid_argument("Acao invalida para controlador de agendamentos");

    switch (action) {
        case ControllerActionEnum ::CREATE:
            return !this->create(loggedUser);

        case ControllerActionEnum ::RETRIVE:
            const bool actionDone = this->showList(loggedUser);
            if (!actionDone) cout << "Usuario selecionou sair..." << endl;
            return false;
    }
};

void SchedulingController::setCurrentSchedulingDate(void) {
    cout << "Informe a data deste agendamento (nao eh validado): ";
    char readInput[100];
    cin.getline(readInput, sizeof(readInput));
    const string answer = string(readInput);
    if (answer!= "0") this->currentScheduling->setDate(answer);
};

void SchedulingController::setCurrentSchedulingMeetingPoint(void) {

    // Confirma intencao
    cout << endl;
    const bool goOn = this->aksYesOrNoQuestionThroughStdIO("Avancar para selecionar Ponto de Coleta?");
    if (!goOn) return;

    // Exibe opcoes disponiveis
    cout << ">> Pontos de Coleta disponiveis: " << endl;
    this->mPointService->showRegistersListData(this->availableMPoints);

    // Captura selecao do usuario
    shared_ptr<MeetingPointModel> selectedMPoint = nullptr;
    int selectedMPointCode;

    do {

        // Captura codigo
        selectedMPointCode = this->getNumberFromStdIO("Informe o codigo do Ponto de Coleta a ser selecionado", "Codigo invalido");
        bool found = false;

        for (uint i = 0; i < this->availableMPoints.size(); i++) {
            const auto currentMpoint = this->availableMPoints[i].foundRegister;
            if (currentMpoint->getCode() != selectedMPointCode) continue;
            found = true;
            selectedMPoint = currentMpoint;
            break;
        }

        if (found) break;

        // Notifica falha
        const bool tryAgain = this->aksYesOrNoQuestionThroughStdIO("Nao existe um Ponto de Coleta com este codigo. Deseja tentar novamente?");
        if (!tryAgain) return;

    } while (true);

    // Add Ponto de Coleta
    cout << "Ponto de Coleta selecionado: " << selectedMPoint->getName() << endl;
    this->currentScheduling->setMeetingPointCode(selectedMPointCode);
};

void SchedulingController::setCurrentSchedulingUser(const shared_ptr<UserModel> loggedUser, const bool setDonator) {

    // Define usuario logado como doador (se necessario)
    if (setDonator && loggedUser->getType() == UserTypeEnum::DONATOR) {
        this->currentScheduling->setDonatorCode(loggedUser->getCode());
        return;
    }

    // Define usuario logado como receptor (se necessario)
    if (!setDonator && loggedUser->getType() == UserTypeEnum::RECEIVER) {
        this->currentScheduling->setReceiverCode(loggedUser->getCode());
        return;
    }

    // Confirma intencao
    cout << endl;
    const string schedullingUserType = setDonator ? "Doador" : "Receptor";
    const bool goOn = this->aksYesOrNoQuestionThroughStdIO("Avancar para selecionar " + schedullingUserType + "?");
    if (!goOn) return;

    // Exibe opcoes disponiveis
    cout << ">> " + schedullingUserType + "s disponiveis: " << endl;
    const auto availableUsers = setDonator ? this->availableDonators : this->availableReceivers;
    this->userService->showRegistersListData(availableUsers);

    // Captura selecao do usuario
    shared_ptr<UserModel> selectedUser = nullptr;
    int selectedUserCode;

    do {

        // Captura codigo
        selectedUserCode = this->getNumberFromStdIO("Informe o codigo do " + schedullingUserType + " a ser selecionado", "Codigo invalido");
        bool found = false;

        for (uint i = 0; i < availableUsers.size(); i++) {
            const auto currentUser = availableUsers[i].foundRegister;
            if (currentUser->getCode() != selectedUserCode) continue;
            found = true;
            selectedUser = currentUser;
            break;
        }

        if (found) break;

        // Notifica falha
        const bool tryAgain = this->aksYesOrNoQuestionThroughStdIO("Nao existe um(a) " + schedullingUserType + " com este codigo. Deseja tentar novamente?");
        if (!tryAgain) return;
        cout << endl;

    } while (true);

    // Tudo OK
    cout << schedullingUserType << " selecionado(a): " << selectedUser->getName() << endl;

    if (setDonator) {
        this->currentScheduling->setDonatorCode(selectedUserCode);

    } else {
        this->currentScheduling->setReceiverCode(selectedUserCode);
    }
};

void SchedulingController::setCurrentSchedulingRejectsList(void) {

    // Confirma intencao
    cout << endl;
    const bool goOn = this->aksYesOrNoQuestionThroughStdIO("Avancar para selecionar Lista de Residuos a serem trocados?");
    if (!goOn) return;

    // Exibe opcoes disponiveis
    cout << ">> Tipos de Residuo disponiveis: " << endl;
    this->rejTypeService->showRegistersListData(this->availableRejTypes);

    // Captura selecao do usuario
    vector<shared_ptr<RejectTypeModel>> selectedRejTypes;
    bool repeat = true;

    do {

        // Captura
        const string selectedCodesStr = this->getStringFromStdIO("Insira lista de codigos (separados por virgula): ");

        stringstream ss(selectedCodesStr);
        string item;
        bool error = false;

        while (getline(ss, item, ',')) {

            try {

                // Captura codigo
                const int rejTypeCode = stoi(item);
                bool exists = false;

                for (uint i = 0; i < this->availableRejTypes.size(); i++) {
                    const auto currentRejType = this->availableRejTypes[i].foundRegister;
                    if (currentRejType->getCode() != rejTypeCode) continue;
                    selectedRejTypes.push_back(currentRejType);
                    exists = true;
                    break;
                }

                // Valida
                if (exists) continue;

                cout << "Tipo de Residuo de codigo '" << rejTypeCode << "' nao existe" << endl;
                error = true;

            } catch (exception err) {
                cout << "Valor invalido: '" << item << "'" << endl;
                error = true;
            }
        }

        // Valida
        if (!error && selectedRejTypes.size() > 0) {
            repeat = false;
            continue;
        }

        cout << endl;
        cin.ignore();
        const bool tryAgain = this->aksYesOrNoQuestionThroughStdIO("Lista invalida. Deseja tentar novamente?");
        if (!tryAgain) return;

    } while (repeat);

    // Add tipos de residuo
    cout << "Residuos selecionados: ";

    for (uint i = 0; i < selectedRejTypes.size(); i++) {
        const auto selectedRejType = selectedRejTypes[i];
        this->currentScheduling->addRejectToBeExchangedCode(selectedRejType->getCode());
        if (i > 0) cout << ", ";
        cout << selectedRejType->getName();
    }

    cout << endl;
};

#endif