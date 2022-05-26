/**
 * File: FuncionarioPediatra.h
 * Class: FuncionarioPediatra
 * Author: hjCostaBR
 * 
 * Define interface da classe Funcionario - Pediatra no sistema
 * Smile Clinic
 */
#ifndef FUNCIONARIO_PEDIATRA_H
#define FUNCIONARIO_PEDIATRA_H

#include <string>

#include "Funcionario.h"
#include "../../../enum/FuncionarioTipoEnum.cpp"

using namespace std;

class FuncionarioPediatra : public Funcionario {

public:
    FuncionarioPediatra(const string nome) : Funcionario(nome, FuncionarioTipoEnum::PEDIATRA) {};
};

#endif