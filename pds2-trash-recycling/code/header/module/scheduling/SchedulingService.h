#ifndef _SCHEDULLING_SERVICE_H_
#define _SCHEDULLING_SERVICE_H_

#include <string>
#include <memory>
#include <vector>
#include "../../common/interface/IService.h"
#include "../../common/FindResult.h"
#include "../../common/enums.h"
#include "SchedulingModel.h"
#include "../meeting-point/MeetingPointDAO.h"
#include "../user/UserDAO.h"

using namespace std;

class SchedulingService: IService {

private:
    /** DAO de Pontos de Coleta. */
    shared_ptr<MeetingPointDAO> mPointDao = nullptr;
    /** DAO de Usuarios. */
    shared_ptr<UserDAO> userDao = nullptr;
    /** DAO de Tipos de Residuo. */
    shared_ptr<RejectTypeDAO> rejTypeDao = nullptr;

public:

    /**
     * Contrutor.
     *
     * @param mPointDao
     * @param userDao
     * @param rejTypeDao
     */
    SchedulingService(
        const shared_ptr<MeetingPointDAO> mPointDao,
        const shared_ptr<UserDAO> userDao,
        const shared_ptr<RejectTypeDAO> rejTypeDao

    ) : mPointDao(mPointDao),
        userDao(userDao),
        rejTypeDao(rejTypeDao)
    {};


    /**
     * @inherit
     */
    bool validateStoredRegister(const vector<string> lineProps) const override;

    /**
     * @inherit
     */
    virtual void showRegisterData(const shared_ptr<SchedulingModel> register, const bool showRejTypes) const;

    /**
     * Monta & Exibe 01 tabela listando dados de varios registros.
     * @param scheduling Itens a serem exibidos.
     */
    void showRegistersListData(const vector<FindResult<SchedulingModel>> scheduling) const;

    /**
     * @inherit
     */
    shared_ptr<SchedulingModel> getModelFromStorageLine(const vector<string> lineProps);

    /** Exibe cabecalho para exibicao tabular de dados. */
    void showDataTableHeader(void) const;
};

#endif