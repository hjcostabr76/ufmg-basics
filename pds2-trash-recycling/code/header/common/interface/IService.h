#ifndef _SERVICE_H_
#define _SERVICE_H_

#include <iostream>
#include <vector>
#include <memory>
#include "IModel.h"

using namespace std;

/**
 * SERVICO
 * Interface a ser implementada por classes que implementem a funcao de SERVICO no sistema
 * Trash Recycling System
 *
 * @author hjcostabr
 */
class IService {

public:
    IService(void) {};
    ~IService(void) {};

    /**
     * Informa se dados contidos numa linha do arquivo de armazenamento correspondem a 01 registro valido.
     *
     * @param lineProps
     * @return
     */
    virtual bool validateStoredRegister(const vector<string> lineProps) const = 0;

    /**
     * Exibe dados de 01 registro.
     * @param register
     */
    virtual void showRegisterData(const shared_ptr<IModel> register) const {};

    /**
     * Transforma dados de 01 registro armazenado numa instancia do modelo gerido pela DAO.
     *
     * @param lineProps Propriedades do registro armazenado.
     * @return
     */
    virtual shared_ptr<IModel> getModelFromStorageLine(const vector<string> lineProps) const {};
};

#endif