#ifndef _REJECTTYPE_DAO_H_
#define _REJECTTYPE_DAO_H_

#include <memory>
#include <string>
#include "RejectTypeService.h"
#include "../../common/class/DAO.h"
#include "../../common/FindResult.h"

/**
 * DAO
 * Gerencia acesso a 'camada de dados' relacionados a entidade TIPO de RESIDUO no sistema
 * Trash Recycling System
 * 
 * @author hjcostabr
 */
class RejectTypeDAO: public DAO {

private:

    /** Nome do arquivo de armqazenamento de dados. */
    static const string STORAGE_FILE;

    /** Classe de servico. */
    shared_ptr<RejectTypeService> service = nullptr;

    /**
     * Encapsula procedimento de escrita de 01 registro no arquivo de armazenamento.
     * @param rejectType Dados a serem escritos.
     */
    void writeRegisterIntoStorage(shared_ptr<RejectTypeModel> rejectType);

protected:

    /**
     * @inherit
     */
    string getStorageFileName(void) override;

public:

    RejectTypeDAO(shared_ptr<RejectTypeService> service): service(service) {};

    /**
     * @inherit
     */
    shared_ptr<RejectTypeModel> insert(const shared_ptr<RejectTypeModel> model);

    /**
     * @inherit
     */
    shared_ptr<RejectTypeModel> update(const shared_ptr<RejectTypeModel> rejectType);

    /**
     * Pesquisa & retorna 01 registro identificado pelo codigo.
     *
     * @param code Codito do registro a ser encontrado.
     * @return Estrutura contendo o registro encontrado + a linha do arquivo em que ele esta.
     */
    FindResult<RejectTypeModel> findOne(const int code);

    /**
     * Captura & retorna lista com todos os registros armazenados.
     * @return
     */
    vector<FindResult<RejectTypeModel>> findAll(void);

    /**
     * Captura & retorna lista com todos os registros armazenados que NAO sao subtipos de outro.
     * @return
     */
    vector<FindResult<RejectTypeModel>> findAllThatCanBeParent(void);
};

#endif
