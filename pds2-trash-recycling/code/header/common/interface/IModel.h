#ifndef _MODEL_H_
#define _MODEL_H_

#include <iostream>

using namespace std;

/**
 * MODELO
 * Interface a ser implementada por classes que implementem a funcao de MODELO no sistema
 * Trash Recycling System
 *
 * @author hjcostabr
 */
class IModel {

public:
    IModel(void) {};
    ~IModel(void) {};

    virtual void rename(void) = 0;
};

#endif