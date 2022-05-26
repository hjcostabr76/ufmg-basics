#ifndef _USER_SERVICE_H_
#define _USER_SERVICE_H_

#include <string>
#include <memory>
#include "../../module/reject-type/RejectTypeDAO.h"
#include "../../module/user/UserModel.h"
#include "../../common/interface/IService.h"
#include "../../common/enums.h"

using namespace std;

class UserService: IService {

private:

    /** DAO de Tipos de Residuo. */
    shared_ptr<RejectTypeDAO> rejTypeDAO = nullptr;

public:

    /** Contrutor. */
    UserService(const shared_ptr<RejectTypeDAO> rejTypeDAO): rejTypeDAO(rejTypeDAO) {};

    /**
     * @inherit
     */
    bool validateStoredRegister(const vector<string> lineProps) const override;

    /**
     * @inherit
     */
    virtual void showRegisterData(const shared_ptr<UserModel> register, const bool showRejTypes) const;

    /**
     * Informa se 01 usuario eh PJ ou PJ.
     *
     * @param cpfCnpj Documento cadastrado do usuario.
     * @return
     */
    PersonTypeEnum getUserPersonType(const string cpfCnpj) const;

    /**
     * Verifica se 01 valor corresopnde a 01 tipo valido de usuario.
     * @param type
     * @return
     */
    bool validateUserType(const int type) const;

    /**
     * Gera & retorna label para exibicao de 01 tipo de usuario.
     * @param typeCode Codigo do tipo
     * @return Label
     */
    string getUserTypeLabel(const UserTypeEnum typeCode) const;

    /**
     * @inherit
     */
    shared_ptr<UserModel> getModelFromStorageLine(const vector<string> lineProps);

    /** Exibe cabecalho para exibicao tabular de dados. */
    void showDataTableHeader(void) const;

    /**
     * Monta & Exibe 01 tabela listando dados de varios registros.
     * @param usersList Itens a serem exibidos.
     */
    void showRegistersListData(const vector<FindResult<UserModel>> usersList) const;
};

#endif