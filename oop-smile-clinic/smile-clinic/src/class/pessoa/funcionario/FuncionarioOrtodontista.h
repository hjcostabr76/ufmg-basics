/**
 * File: FuncionarioOrtodontista.h
 * Class: FuncionarioOrtodontista
 * Author: hjCostaBR
 * 
 * Define interface da classe Funcionario - Ortodontista no sistema
 * Smile Clinic
 */
#ifndef FUNCIONARIO_ORTODONTISTA_H
#define FUNCIONARIO_ORTODONTISTA_H

#include <string>

#include "Funcionario.h"
#include "../../../enum/FuncionarioTipoEnum.cpp"

using namespace std;

class FuncionarioOrtodontista : public Funcionario {

public:
    FuncionarioOrtodontista(const string nome) : Funcionario(nome, FuncionarioTipoEnum::ORTODONTISTA) { };
};

#endif