#ifndef _USER_CONTROLLER_H_
#define _USER_CONTROLLER_H_

#include <memory>
#include "../../common/class/Controller.h"
#include "../../common/class/MenuController.h"
#include "../../common/enums.h"
#include "../../module/reject-type/RejectTypeService.h"
#include "../../module/reject-type/RejectTypeDAO.h"
#include "./UserModel.h"
#include "./UserDAO.h"

/**
 * CONTROLLER
 * Gerencia a interacao com as 'telas' relacionadas a USUARIO no sistema
 * Trash Recycling System
 * 
 * @author hjcostabr
 */
class UserController: public Controller {

private:

    /** DAO de usuario. */
    shared_ptr<UserDAO> dao = nullptr;
    /** Servico de usuario. */
    shared_ptr<UserService> service = nullptr;

    /** DAO para entidade: Tipo de Residuo. */
    shared_ptr<RejectTypeDAO> rejTypeDao = nullptr;
    /** Classe de Servico para entidade: Tipo de Residuo. */
    shared_ptr<RejectTypeService> rejTypeService = nullptr;

    /** Dados do registro sendo manipulado no momento. */
    shared_ptr<UserModel> currentUser = nullptr;
    /** Tipo de pessoa do usuario atual. */
    shared_ptr<PersonTypeEnum> currentUserType = nullptr;


    /** Captura & define tipo (pf /pj) para insercao de novo usuario. */
    bool setCurrentUserPersonType(void);

    /** Captura & define valor para CPF/CNPJ de 01 novo usuario a ser cadastrado. */
    bool setCurrentUserCpfOrCnpj(void);

    /** Captura & define tipo do usuario atual. */
    bool setCurrentUserType(void);

    /** Captura & define nome do usuario atual. */
    bool setCurrentUserName(void);

    /** Captura & define lista de residuos de interesse de 01 usuario. */
    void setCurrentUserRejTypeList(void);

    /** Efetua cadastro de novo usuario. */
    bool create(void);

    /**
     * Captura & retorna dados para inserir/atualizar 01 registro.
     *
     * @param insert Flag: Determina se a coleta de dados eh para realizar insercao (SE nao for, sera atualizacao).
     * @param admin Flag: Determina SE o usuario atual que realiza a operacao eh ADMIN.
     * @return
     */
    bool getDataForUserFromStdIo(const bool insert, const bool admin);

    /** Atualiza cadastro de 01 registro ja armazenado. */
    bool update(shared_ptr<UserModel> currentUser);

    /** Exibe listagem de usuarios cadastrados. */
    bool showList(void) const;

public:

    /** Contrutor. */
    UserController(
        const shared_ptr<UserDAO> dao,
        const shared_ptr<UserService> service,
        const shared_ptr<RejectTypeService> rejTypeService,
        const shared_ptr<RejectTypeDAO> rejTypeDao

    ) : dao(dao), service(service), rejTypeService(rejTypeService), rejTypeDao(rejTypeDao) {};

    /**
     * @inherit
     */
    bool runAction(int action) override;

    /**
     * @inherit
     */
    bool runAction(int action, shared_ptr<UserModel> currentUser) override;
};

#endif