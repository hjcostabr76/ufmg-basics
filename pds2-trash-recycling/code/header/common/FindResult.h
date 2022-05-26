#ifndef _FINDRESULT_H_
#define _FINDRESULT_H_

#include <memory>
#include "./interface/IModel.h"

/**
 * Estrutura que padroniza o formato de retorno de 01 pequisa por 01 registro
 * armazenado em arquivo de texto no sistema
 * Trash Recycling System
 *
 * @author hjcostabr
 */
template <typename T>
struct FindResult {
    shared_ptr<T> foundRegister;
    int line;
};


#endif
