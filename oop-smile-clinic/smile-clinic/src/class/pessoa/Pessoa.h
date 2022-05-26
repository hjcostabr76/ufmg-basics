/**
 * File: Pessoa.h
 * Class: Pessoa
 * Author: hjCostaBR
 * 
 * Define interface da classe Pessoa no sistema
 * Smile Clinic
 */
#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include "../../enum/PessoaTipoEnum.cpp"

using namespace std;

class Pessoa {

public:
    Pessoa(const string nome, const PessoaTipoEnum tipo);
    string getNome(void);
    PessoaTipoEnum getTipo(void);
    virtual void identificar(void) = 0;

protected:
    string nome;
    PessoaTipoEnum tipo;
    string getTipoNome(void);
};

#endif