#ifndef _USER_DAO_H_
#define _USER_DAO_H_

#include <memory>
#include "UserModel.h"
#include "UserService.h"
#include "../../common/class/DAO.h"
#include "../../common/FindResult.h"

/**
 * DAO
 * Gerencia acesso a 'camada de dados' relacionados a entidade USUARIO no sistema
 * Trash Recycling System
 * 
 * @author hjcostabr
 */
class UserDAO: public DAO {

private:

    /** Nome do arquivo de armqazenamento de dados. */
    static const string STORAGE_FILE;

    /** Classe de servico. */
    shared_ptr<UserService> service = nullptr;


    /**
     * Encapsula procedimento de escrita de 01 registro no arquivo de armazenamento.
     * @param user Dados a serem escritos.
     */
    void writeRegisterIntoStorage(shared_ptr<UserModel> user);

    /**
     * Captura & retorna lista com todos os registros armazenados de 01 determinado tipo.
     *
     * @param type Tipo do qual os registros pesquisados devem fazer parte.
     * @return
     */
    vector<FindResult<UserModel>> findAllByType(const UserTypeEnum type);

protected:

    /**
     * @inherit
     */
    string getStorageFileName(void) override;

public:

    UserDAO(shared_ptr<UserService> service): service(service) {};

    /**
     * @inherit
     */
    shared_ptr<UserModel> insert(const shared_ptr<UserModel> model);

    /**
     * @inherit
     */
    shared_ptr<UserModel> update(const shared_ptr<UserModel> user);

    /**
     * Pesquisa & retorna 01 registro identificado pelo codigo.
     *
     * @param code Codito do registro a ser encontrado.
     * @return Estrutura contendo o registro encontrado + a linha do arquivo em que ele esta.
     */
    FindResult<UserModel> findOne(const int code);

    /**
     * Pesquisa & retorna 01 registro identificado pelo cpf / cnpj.
     *
     * @param cpfCnpj Cpf/Cnpj do registro a ser encontrado.
     * @return Estrutura contendo o registro encontrado + a linha do arquivo em que ele esta.
     */
    FindResult<UserModel> findOne(const string cpfCnpj);

    /**
     * Pesquisa & retorna 01 registro identificado pelo codigo, cpf ou cnpj.
     *
     * @param code Codito do registro a ser encontrado.
     * @param cpfCnpj Cpf/Cnpj do registro a ser encontrado.
     * @return Estrutura contendo o registro encontrado + a linha do arquivo em que ele esta.
     */
    FindResult<UserModel> findOne(const int code, const string cpfCnpj);

    /**
     * Captura & retorna lista com todos os registros armazenados.
     * @return
     */
    vector<FindResult<UserModel>> findAll(void);

    /**
     * Captura & retorna lista com todos os registros armazenados do tipo DOADOR.
     * @return
     */
    vector<FindResult<UserModel>> findAllDonators(void);

    /**
     * Captura & retorna lista com todos os registros armazenados do tipo RECEPTOR.
     * @return
     */
    vector<FindResult<UserModel>> findAllReceivers(void);
};

#endif