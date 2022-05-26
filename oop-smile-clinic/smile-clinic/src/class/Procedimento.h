/**
 * File: Procedimento.h
 * Class: Procedimento
 * Author: hjCostaBR
 * 
 * Define interface da classe Procedimento no sistema
 * Smile Clinic
 */
#ifndef PROCEDIMENTO_H
#define PROCEDIMENTO_H

#include <string>

#include "../../../date/Date.h"
#include "pessoa/funcionario/Funcionario.h"
#include "pessoa/funcionario/Funcionario.cpp"

using namespace std;

class Procedimento {

private:
    string nome;
    double valor;
    Date* dataProcedimento;
    Funcionario* dentista;

public:
    Procedimento(void);

    // Getters
    string getNome(void);
    double getValor(void);
    Date* getDataProcedimento(void);
    Funcionario* getDentista(void);

    // Setters
    void setNome(const string nome);
    void setValor(const double valor);
    void setDataProcedimento(Date* dataProcedimento);
    void setDentista(Funcionario* dentista);
};

#endif