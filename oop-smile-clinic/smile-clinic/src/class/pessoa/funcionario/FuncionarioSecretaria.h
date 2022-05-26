/**
 * File: FuncionarioSecretaria.h
 * Class: FuncionarioSecretaria
 * Author: hjCostaBR
 * 
 * Define interface da classe Funcionario - Secretaria no sistema
 * Smile Clinic
 */
#ifndef FUNCIONARIO_SECRETARIA_H
#define FUNCIONARIO_SECRETARIA_H

#include <string>

#include "Funcionario.h"
#include "../../../enum/FuncionarioTipoEnum.cpp"

using namespace std;

class FuncionarioSecretaria : public Funcionario {

public:
    FuncionarioSecretaria(const string nome) : Funcionario(nome, FuncionarioTipoEnum::SECRETARIA) { };
};

#endif