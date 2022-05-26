/**
 * File: Orcamento.h
 * Class: Orcamento
 * Author: hjCostaBR
 * 
 * Define interface da classe Orcamento no sistema
 * Smile Clinic
 */
#ifndef ORCAMENTO_H
#define ORCAMENTO_H

#include <string>
#include <vector>

#include "../../../date/Date.h"
#include "pessoa/paciente/Paciente.h"
#include "Procedimento.h"

using namespace std;

class Orcamento {

public:
    Orcamento(void);
    vector<Procedimento> getProcedimentos();
    bool isPago(void);

    // Getters
    Date* getDataPagamento(void);
    Paciente* getPaciente(void);
    double getValorTotal(void);

    // Setters
    void addProcedimento(const Procedimento procedimento);
    void setDataPagamento(Date* DataPagamento);
    void setPaciente(Paciente* paciente);

private:
    Date* dataPagamento;
    Paciente* paciente;
    vector<Procedimento> procedimentos;
};

#endif