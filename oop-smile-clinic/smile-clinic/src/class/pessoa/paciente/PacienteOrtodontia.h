/**
 * File: PacienteOrtodontia.h
 * Class: PacienteOrtodontia
 * Author: hjCostaBR
 * 
 * Define interface da classe Paciente - Ortodontia no sistema
 * Smile Clinic
 */
#ifndef PACIENTE_ORTODONTIA_H
#define PACIENTE_ORTODONTIA_H

#include <string>

#include "Paciente.h"
#include "../../../enum/PacienteTipoEnum.cpp"

using namespace std;

class PacienteOrtodontia : public Paciente {

public:
    PacienteOrtodontia(const string nome) : Paciente(nome, PacienteTipoEnum::ORTODONTIA) {};
};

#endif