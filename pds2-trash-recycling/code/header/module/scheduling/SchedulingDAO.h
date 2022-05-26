#ifndef _SCHEDULING_DAO_H_
#define _SCHEDULING_DAO_H_

#include "../../common/class/DAO.h"
#include "SchedulingService.h"

/**
 * DAO
 * Gerencia acesso a 'camada de dados' relacionados a entidade AGENDAMENTO no sistema
 * Trash Recycling System
 *
 * @author hjcostabr
 */
class SchedulingDAO: public DAO {

private:

    /** Nome do arquivo de armqazenamento de dados. */
    static const string STORAGE_FILE;

    /** Classe de servico. */
    shared_ptr<SchedulingService> service = nullptr;

    /**
     * Encapsula procedimento de escrita de 01 registro no arquivo de armazenamento.
     * @param scheduling Dados a serem escritos.
     */
    void writeRegisterIntoStorage(shared_ptr<SchedulingModel> scheduling);

protected:

    /**
     * @inherit
     */
    string getStorageFileName(void) override;

public:

    SchedulingDAO(shared_ptr<SchedulingService> service): service(service) {};

    /**
     * @inherit
     */
    shared_ptr<SchedulingModel> insert(const shared_ptr<SchedulingModel> model);

    /**
     * @inherit
     */
    shared_ptr<SchedulingModel> update(const shared_ptr<SchedulingModel> scheduling);

    /**
     * Pesquisa & retorna 01 registro identificado pelo codigo.
     *
     * @param code Codito do registro a ser encontrado.
     * @return Estrutura contendo o registro encontrado + a linha do arquivo em que ele esta.
     */
    FindResult<SchedulingModel> findOne(const int code);

    /**
     * Captura & retorna lista com todos os registros associado a 01 determinado usuario.
     * @return
     */
    vector<FindResult<SchedulingModel>> findByUser(const int userCode);
};

#endif