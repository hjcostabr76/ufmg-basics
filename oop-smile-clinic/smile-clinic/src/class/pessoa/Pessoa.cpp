/**
 * File: Pessoa.cpp
 * Class: Pessoa
 * Author: hjCostaBR
 * 
 * Define implementacao da classe Pessoa no sistema
 * Smile Clinic
 */
#ifndef PESSOA_CPP
#define PESSOA_CPP

#include <string>
#include <iostream>

#include "Pessoa.h"
#include "../../enum/PessoaTipoEnum.cpp"

using namespace std;

// Construtor
Pessoa::Pessoa(const string nome, const PessoaTipoEnum tipo) {
    this->nome  = nome;
    this->tipo  = tipo;
    cout << "Criando um novo " << this->getTipoNome() << ": " << nome << "...\n";
}

// Getter: Nome
string Pessoa::getNome() {
    return this->nome;
}

// Getter: Tipo
PessoaTipoEnum Pessoa::getTipo() {
    return this->tipo;
}

// Retorna string do nome do tipo de pessoa
string Pessoa::getTipoNome() {

    switch (this->tipo) {
        case PessoaTipoEnum::PACIENTE:
            return "paciente";

        case PessoaTipoEnum::FUNCIONARIO:
            return "funcionario";

        default:
            return "";
    }
}

#endif