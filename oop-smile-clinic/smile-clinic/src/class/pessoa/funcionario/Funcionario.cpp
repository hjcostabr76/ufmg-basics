/**
 * File: Funcionario.cpp
 * Class: Funcionario
 * Author: hjCostaBR
 * 
 * Define implementacao da classe Funcionario no sistema
 * Smile Clinic
 */
#ifndef FUNCIONARIO_CPP
#define FUNCIONARIO_CPP

#include <string>
#include <iostream>

#include "Funcionario.h"
#include "../../../enum/FuncionarioTipoEnum.cpp"

using namespace std;

// Identificar
void Funcionario::identificar() {
    cout << "Eu sou um(a) " << this->getTipoFuncionarioNome() << "! Meu nome eh " << this->nome << "\n";
}

// Getter: Tipo de funcionario
FuncionarioTipoEnum Funcionario::getTipoFuncionario() {
    return this->tipoFuncionario;
}

// Retorna string do nome do tipo de funcionario
string Funcionario::getTipoFuncionarioNome() {
    switch (this->tipoFuncionario) {
        case FuncionarioTipoEnum::CLINICO_GERAL:
            return "Clinico Geral";

        case FuncionarioTipoEnum::ORTODONTISTA:
            return "Ortodontista";

        case FuncionarioTipoEnum::PEDIATRA:
            return "Pediatra";

        case FuncionarioTipoEnum::SECRETARIA:
            return "Secretaria";

        default:
            return "";
    }
}

#endif