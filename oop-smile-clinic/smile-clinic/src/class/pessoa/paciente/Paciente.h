/**
 * File: Paciente.h
 * Class: Paciente
 * Author: hjCostaBR
 * 
 * Define interface da classe Paciente no sistema
 * Smile Clinic
 */
#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>

#include "../Pessoa.h"
#include "../Pessoa.cpp"
#include "../../../enum/PessoaTipoEnum.cpp"
#include "../../../enum/PacienteTipoEnum.cpp"

using namespace std;

class Paciente : public Pessoa {

public:
    Paciente() : Pessoa("", PessoaTipoEnum::PACIENTE) {};
    Paciente(const string nome, const PacienteTipoEnum tipoPaciente) : Pessoa(nome, PessoaTipoEnum::PACIENTE) {
        this->tipoPaciente = tipoPaciente;
    };

    PacienteTipoEnum getTipoPaciente(void);
    virtual void identificar(void);

protected:
    PacienteTipoEnum tipoPaciente;
    string getTipoPacienteNome(void);
};

#endif