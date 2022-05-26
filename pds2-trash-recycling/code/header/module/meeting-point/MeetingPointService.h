#ifndef _MEETINGPOINT_SERVICE_H
#define _MEETINGPOINT_SERVICE_H

#include <string>
#include <memory>
#include <vector>
#include "../../common/interface/IService.h"
#include "../../common/FindResult.h"
#include "../../common/enums.h"
#include "MeetingPointModel.h"

using namespace std;

class MeetingPointService: IService {

public:
    
    MeetingPointService(void) {};

    /**
     * @inherit
     */
    bool validateStoredRegister(const vector<string> lineProps) const override;

    /**
     * @inherit
     */
    virtual void showRegisterData(const shared_ptr<MeetingPointModel> register) const;

    /**
     * Monta & Exibe 01 tabela listando dados de varios registros.
     * @param mPointList Itens a serem exibidos.
     */
    void showRegistersListData(const vector<FindResult<MeetingPointModel>> mPointList) const;

    /**
     * @inherit
     */
    shared_ptr<MeetingPointModel> getModelFromStorageLine(const vector<string> lineProps);

    /** Exibe cabecalho para exibicao tabular de dados. */
    void showDataTableHeader(void) const;
};

#endif