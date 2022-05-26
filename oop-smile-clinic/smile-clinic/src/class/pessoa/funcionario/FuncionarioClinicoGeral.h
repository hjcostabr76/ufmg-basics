/**
 * File: FuncionarioClinicoGeral.h
 * Class: FuncionarioClinicoGeral
 * Author: hjCostaBR
 * 
 * Define interface da classe Funcionario - Clinico Geral no sistema
 * Smile Clinic
 */
#ifndef FUNCIONARIO_CLINICO_H
#define FUNCIONARIO_CLINICO_H

#include <string>

#include "Funcionario.h"
#include "../../../enum/FuncionarioTipoEnum.cpp"

using namespace std;

class FuncionarioClinicoGeral : public Funcionario {

public:
    FuncionarioClinicoGeral(const string nome) : Funcionario(nome, FuncionarioTipoEnum::CLINICO_GERAL) { };
};

#endif