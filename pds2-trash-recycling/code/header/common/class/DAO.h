#ifndef _DAO_H_
#define _DAO_H_

#include <vector>
#include <memory>
#include <fstream>
#include "../interface/IModel.h"
#include "../interface/IService.h"

/**
 * DAO
 * Clase generica a ser extendida por classes que implementem a funcao de DAO no sistema
 * Trash Recycling System
 *
 * @author hjcostabr
 */
class DAO {

private:

    /** Monta & retorno path para arquivo de armazenamento utilizado por esta DAO. */
    string getStorageFilePath(void);

    /**
     * Fecha o arquivo de armazenamento da DAO (SE estiver aberto).
     * @param writing Flag: Determina se o stream a ser encerrado eh de leitura (SE nao for, sera de escrita).
     */
    void closeStorage(bool writing);

protected:

    /** Path relativo a pasta da chamada para execuaco para a pasta de armazenamento. */
    static const string STORAGE_DIR_PATH;

    /** Strema de ESCRITA do arquivo de armazenamento desta DAO. */
    ofstream writingStream;

    /** Strema de LEITURA do arquivo de armazenamento desta DAO. */
    ifstream readingStream;


    /**
     * Abre arquivo de armazenamento usado pela DAO para ESCRITA.
     * @param filePath Path do arquivo.
     */
    void openStorageForWriting(void);

    /**
     * Abre arquivo de armazenamento usado pela DAO para LEITURA.
     * @param filePath Path do arquivo.
     */
    void openStorageForReading(void);

    /** Define & retorna nome do arquivo de armazenamento utilizado pela DAO. */
    virtual string getStorageFileName(void) = 0;

public:

    DAO(void) {};
    ~DAO(void);

    /**
     * Implementa logica para insercao de novo registro.
     *
     * @param model Dados a serem inseridos.
     * @return Registro recem inserido.
     */
    virtual shared_ptr<IModel> insert(const shared_ptr<IModel> model) {};

    /**
     * Implementa logica para atualizacao 01 registro ja cadstrado.
     *
     * @param model Dados a serem persistidos.
     * @return Registro recem atualizado.
     */
    virtual shared_ptr<IModel> update(const shared_ptr<IModel> model) {};

    /**
     * Remove do armazenamento 01 registro identificado pelo numero de sua linha.
     * @param line
     */
    void deleteOne(const int line);
};

#endif