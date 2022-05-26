#ifndef _REJECT_TYPE_CONTROLLER_H_
#define _REJECT_TYPE_CONTROLLER_H_

#include <memory>
#include "../../common/class/Controller.h"
#include "../../common/class/MenuController.h"
#include "../../module/user/UserModel.h"
#include "./RejectTypeModel.h"
#include "./RejectTypeDAO.h"
#include "./RejectTypeService.h"

/**
 * CONTROLLER
 * Gerencia a interacao com as 'telas' relacionadas a TIPOS de RESIDUO no sistema
 * Trash Recycling System
 * 
 * @author hjcostabr
 */
class RejectTypeController: public Controller {

private:

    /** DAO. */
    shared_ptr<RejectTypeDAO> dao = nullptr;

    /** Classe de servico. */
    shared_ptr<RejectTypeService> service = nullptr;

    /** Dados do registro sendo manipulado no momento. */
    shared_ptr<RejectTypeModel> currentRejectType = nullptr;


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
    bool update(shared_ptr<RejectTypeModel> rejType);

    /**
     * Captura & define nome para o registro em edicao no momento.
     * @return Retorna falso caso o usuario selecione 'sair'. Ou true.
     */
    bool setCurrentRejectTypeName(void);

    /**
     * Captura & define instrucoes de armazenamento para registro em edicao no momento.
     * @return Retorna falso caso o usuario selecione 'sair'. Ou true.
     */
    bool setCurrentRejectTypeStorageSpecification(void);

    /**
     * Captura & define tipo de residuo 'pai' do tipo sendo cadastrado no momento.
     * @return Retorna falso caso o usuario selecione 'sair'. Ou true.
     */
    bool setCurrentRejTypeParent(void);

    /**
     * Monta & exibe listagem de registros + opcoes de acao.
     * @return Flag: SE o usuario selecionou 'sair'.
     */
    bool showList(const shared_ptr<UserModel> currentUser);

public:

    /** Contrutor. */
    RejectTypeController(const shared_ptr<RejectTypeDAO> dao, const shared_ptr<RejectTypeService> service)
        : dao(dao), service(service)
        {};

    /**
     * @inherit
     */
    virtual bool runAction(int action) override;

    /**
     * @inherit
     */
    virtual bool runAction(int action, shared_ptr<UserModel> currentUser);
};

#endif