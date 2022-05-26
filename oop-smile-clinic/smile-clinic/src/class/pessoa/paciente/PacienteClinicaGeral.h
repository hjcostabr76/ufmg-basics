/**
 * File: PacienteClinicoGeral.h
 * Class: PacienteClinicoGeral
 * Author: hjCostaBR
 * 
 * Define interface da classe Paciente - Clinica Geral no sistema
 * Smile Clinic
 */
#ifndef PACIENTE_CLINICA_H
#define PACIENTE_CLINICA_H

#include <string>

#include "Paciente.h"
#include "../../../enum/PacienteTipoEnum.cpp"

using namespace std;

class PacienteClinicoGeral : public Paciente {

public:
    PacienteClinicoGeral(const string nome) : Paciente(nome, PacienteTipoEnum::CLINICA_GERAL){};
};

#endif