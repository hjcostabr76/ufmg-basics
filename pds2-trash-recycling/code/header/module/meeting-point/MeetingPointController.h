#ifndef _MEETINGPOINT_CONTROLLER_H_
#define _MEETINGPOINT_CONTROLLER_H_

#include <memory>
#include "../../common/class/Controller.h"
#include "../../common/class/MenuController.h"
#include "../../module/user/UserModel.h"
#include "./MeetingPointModel.h"
#include "./MeetingPointDAO.h"
#include "./MeetingPointService.h"

/**
 * CONTROLLER
 * Gerencia a interacao com as 'telas' relacionadas a PONTO de COLETA no sistema
 * Trash Recycling System
 * 
 * @author hjcostabr
 */
class MeetingPointController: public Controller {

private:

    /** DAO. */
    shared_ptr<MeetingPointDAO> dao = nullptr;

    /** Classe de servico. */
    shared_ptr<MeetingPointService> service = nullptr;

    /** Dados do registro sendo manipulado no momento. */
    shared_ptr<MeetingPointModel> currentMeetingPoint = nullptr;


    /** Efetua cadastro de novo usuario. */
    bool create(void);

    /**
     * Captura & retorna dados para inserir/atualizar 01 registro.
     *
     * @param insert Flag: Determina se a coleta de dados eh para realizar insercao (SE nao for, sera atualizacao).
     * @return
     */
    bool getDataFromStdIo(const bool insert);

    /** Atualiza cadastro de 01 registro ja armazenado. */
    bool update(shared_ptr<MeetingPointModel> rejType);

    /**
     * Monta & exibe listagem de registros + opcoes de acao.
     * @return Flag: SE o usuario selecionou 'sair'.
     */
    bool showList(void);

    /** Captura & define nome para o registro em edicao no momento. */
    void setCurrentMeetingPointName(void);

public:

    /** Contrutor. */
    MeetingPointController(const shared_ptr<MeetingPointDAO> dao, const shared_ptr<MeetingPointService> service)
        : dao(dao), service(service) {};

    /**
     * @inherit
     */
    virtual bool runAction(int action) override;
};

#endif