#ifndef _MEETINGPOINT_DAO_H
#define _MEETINGPOINT_DAO_H

#include <memory>
#include <string>
#include "MeetingPointService.h"
#include "../../common/class/DAO.h"
#include "../../common/FindResult.h"

/**
 * DAO
 * Gerencia acesso a 'camada de dados' relacionados a entidade PONTO de COLETA no sistema
 * Trash Recycling System
 * 
 * @author hjcostabr
 */
class MeetingPointDAO: public DAO {

private:

    /** Nome do arquivo de armqazenamento de dados. */
    static const string STORAGE_FILE;

    /** Classe de servico. */
    shared_ptr<MeetingPointService> service = nullptr;

    /**
     * Encapsula procedimento de escrita de 01 registro no arquivo de armazenamento.
     * @param meetingPoint Dados a serem escritos.
     */
    void writeRegisterIntoStorage(shared_ptr<MeetingPointModel> meetingPoint);

protected:

    /**
     * @inherit
     */
    string getStorageFileName(void) override;

public:

    MeetingPointDAO(shared_ptr<MeetingPointService> service): service(service) {};

    /**
     * @inherit
     */
    shared_ptr<MeetingPointModel> insert(const shared_ptr<MeetingPointModel> model);

    /**
     * @inherit
     */
    shared_ptr<MeetingPointModel> update(const shared_ptr<MeetingPointModel> mPoint);

    /**
     * Pesquisa & retorna 01 registro identificado pelo codigo.
     *
     * @param code Codito do registro a ser encontrado.
     * @return Estrutura contendo o registro encontrado + a linha do arquivo em que ele esta.
     */
    FindResult<MeetingPointModel> findOne(const int code);

    /**
     * Captura & retorna lista com todos os registros armazenados.
     * @return
     */
    vector<FindResult<MeetingPointModel>> findAll(void);
};

#endif