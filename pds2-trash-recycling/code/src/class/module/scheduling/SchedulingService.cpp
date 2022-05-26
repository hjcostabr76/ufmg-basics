#ifndef _SCHEDULLING_SERVICE_CPP_
#define _SCHEDULLING_SERVICE_CPP_

#include <vector>
#include <sstream>
#include "../../../../header/module/scheduling/SchedulingModel.h"
#include "../../../../header/module/scheduling/SchedulingService.h"
#include "../../../../header/common/FindResult.h"

bool SchedulingService::validateStoredRegister(const vector<string> lineProps) const {

    if (lineProps.size() != 7) return false;

    // Valida codigos de: Ponto de Coleta, Doador & Receptor
    for (int i = 1; i <= 6; i++) {
        if (i == 1 || i == 5) continue;
        try { stoi(lineProps[i]); }
        catch (exception err) { return false; }
    }

    // Valida flag Concluido?
    int done = stoi(lineProps[6]);
    if (done != 0 && done != 1) return false;

    return true;
};

void SchedulingService::showRegisterData(const shared_ptr<SchedulingModel> scheduling, const bool showRejTypes) const {

    // Captura relacionamentos
    const auto mPointSearch = this->mPointDao->findOne(scheduling->getMeetingPointCode());
    const auto mPoint = mPointSearch.foundRegister;
    if (mPoint == nullptr) throw domain_error("meeting-point");

    const auto donatorSearch = this->userDao->findOne(scheduling->getDonatorCode());
    const auto donator = donatorSearch.foundRegister;
    if (donator == nullptr) throw domain_error("donator");

    const auto receiverSearch = this->userDao->findOne(scheduling->getReceiverCode());
    const auto receiver = receiverSearch.foundRegister;
    if (receiver == nullptr) throw domain_error("receiver");

    const string doneFlagValue = scheduling->isDone() ? "Realizado" : "Nao Realizado";

    // Exibe dados
    cout << "|\t" << scheduling->getCode() << "\t|"
        << " " << scheduling->getDate() << "\t|"
        << " " << mPoint->getName() << "\t|"
        << " " << donator->getName() << "\t|"
        << "\t" << receiver->getName() << "\t|"
        << "\t" << doneFlagValue << "\t|" << endl;

    if (!showRejTypes) return;

    // @todo: Continuar daqui...
    if (!scheduling->getRejectsToBeExchangedCodes().size()) {
        cout << "Nenhum Residuo a ser trocado..." << endl;
        return;
    }

    cout << "Residuos a serem trocados: ";

    for (uint i = 0; i < scheduling->getRejectsToBeExchangedCodes().size(); i++) {

        const int rejTypeCode = scheduling->getRejectsToBeExchangedCodes()[i];
        const auto rejTypeSearch = this->rejTypeDao->findOne(rejTypeCode);

        if (rejTypeSearch.foundRegister == nullptr) {
            cout << endl << "** WARNING: Cadastro de Agendamento invalido (tipo de residuo nao existe: " << rejTypeCode << ") **" << endl << endl;
            continue;
        }

        if (i > 0) cout << ", ";
        cout << rejTypeSearch.foundRegister->getName();
    }

    cout << endl;
};

void SchedulingService::showDataTableHeader(void) const {
    cout << "|\tCodigo\t|"
        << "\tData\t|"
        << "\tPonto de Coleta\t|"
        << "\tDoador\t|"
        << "\tReceptor\t|"
        << "\tStatus\t\t|"
        << endl;
};

void SchedulingService::showRegistersListData(const vector<FindResult<SchedulingModel>> schedulingList) const {

    if (!schedulingList.size()) {
        cout << "Nenhum registro encontrado..." << endl;
        return;
    }

    this->showDataTableHeader();

    for (uint i = 0; i < schedulingList.size(); i++) {
        this->showRegisterData(schedulingList[i].foundRegister, false);
    }

    cout << endl;
};

shared_ptr<SchedulingModel> SchedulingService::getModelFromStorageLine(const vector<string> lineProps) {

    if (!this->validateStoredRegister(lineProps))
        throw invalid_argument("Tentativa de gerar Agendamento a partir de dados invalidos");

    auto scheduling = make_shared<SchedulingModel>();
    scheduling->setCode(stoi(lineProps[0]));
    scheduling->setDate(lineProps[1]);
    scheduling->setMeetingPointCode(stoi(lineProps[2]));
    scheduling->setDonatorCode(stoi(lineProps[3]));
    scheduling->setReceiverCode(stoi(lineProps[4]));
    scheduling->setDone(stoi(lineProps[6]) == 1);

    // Add lista de tipos de residuos a serem trocados (se houver)
    vector<int> rejTypeCodes;

    stringstream ss(lineProps[5]);
    string item;

    while (getline(ss, item, ',')) {

        try {
            rejTypeCodes.push_back(stoi(item));

        } catch (exception err) {
            cout << endl << "** WARNING: Cadastro de Agendamento invalido (tipo de residuo invalido: " << item << ") **" << endl << endl;
            continue;
        }
    }

    for (uint i = 0; i < rejTypeCodes.size(); i++)
        scheduling->addRejectToBeExchangedCode(rejTypeCodes[i]);

    return scheduling;
};

#endif
