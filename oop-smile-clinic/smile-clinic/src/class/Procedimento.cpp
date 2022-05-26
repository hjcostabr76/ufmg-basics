/**
 * File: Procedimento.cpp
 * Class: Procedimento
 * Author: hjCostaBR
 * 
 * Define implementacao da classe Procedimento no sistema
 * Smile Clinic
 */
#ifndef PROCEDIMENTO_CPP
#define PROCEDIMENTO_CPP

#include <string>
#include <iostream>

#include "Procedimento.h"
#include "pessoa/funcionario/Funcionario.h"
#include "pessoa/funcionario/Funcionario.cpp"
#include "../../../date/Date.h"

using namespace std;

Procedimento::Procedimento(void) {
    cout << "\nCriando novo procedimento...";
}

// Getter: Nome
string Procedimento::getNome() {
    return this->nome;
}

// Getter: Valor
double Procedimento::getValor() {
    return this->valor;
}

// Getter: Data
Date* Procedimento::getDataProcedimento() {
    return this->dataProcedimento;
}

// Getter: Dentista
Funcionario* Procedimento::getDentista() {
    return this->dentista;
}

// Setter: Nome
void Procedimento::setNome(const string nome) {
    this->nome = nome;
}

// Setter: Valor
void Procedimento::setValor(const double valor) {
    this->valor = valor;
}

// Setter: Data Procedimento
void Procedimento::setDataProcedimento(Date* dataProcedimento) {
    this->dataProcedimento = dataProcedimento;
}

// Setter: Dentista
void Procedimento::setDentista(Funcionario* dentista) {
    this->dentista = dentista;
}

#endif