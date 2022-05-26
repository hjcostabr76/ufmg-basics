#ifndef _MEETINGPOINT_SERVICE_CPP_
#define _MEETINGPOINT_SERVICE_CPP_

#include <vector>
#include "../../../../header/module/meeting-point/MeetingPointService.h"
#include "../../../../header/common/FindResult.h"

bool MeetingPointService::validateStoredRegister(const vector<string> lineProps) const {

    if (lineProps.size() != 2) return false;

    try { stoi(lineProps[0]); }
    catch (exception err) { return false; }

    return true;
};

void MeetingPointService::showRegisterData(const shared_ptr<MeetingPointModel> mPoint) const {
    cout << "|\t" << mPoint->getCode() << "\t| "
        << mPoint->getName() << "\t|"
        << endl;
};

void MeetingPointService::showDataTableHeader(void) const {
    cout << "|\tCodigo\t|"
        << "\tNome\t\t|"
        << endl;
};

void MeetingPointService::showRegistersListData(const vector<FindResult<MeetingPointModel>> mPointList) const {

    if (!mPointList.size()) {
        cout << "Nenhum registro encontrado..." << endl;
        return;
    }

    this->showDataTableHeader();

    for (uint i = 0; i < mPointList.size(); i++) {
        this->showRegisterData(mPointList[i].foundRegister);
    }

    cout << endl;
};

shared_ptr<MeetingPointModel> MeetingPointService::getModelFromStorageLine(const vector<string> lineProps) {

    if (!this->validateStoredRegister(lineProps))
        throw invalid_argument("Tentativa de gerar Ponto de Coleta a partir de dados invalidos");

    auto mPoint = make_shared<MeetingPointModel>();
    mPoint->setCode(stoi(lineProps[0]));
    mPoint->setName(lineProps[1]);
    return mPoint;
};

#endif