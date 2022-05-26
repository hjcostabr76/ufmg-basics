/**
 * File: PacientePediatria.h
 * Class: PacientePediatria
 * Author: hjCostaBR
 * 
 * Define interface da classe Paciente - Pediatria no sistema
 * Smile Clinic
 */
#ifndef PACIENTE_PEDIATRIA_H
#define PACIENTE_PEDIATRIA_H

#include <string>

#include "Paciente.h"
#include "../../../enum/PacienteTipoEnum.cpp"

using namespace std;

class PacientePediatria : public Paciente {

public:
    PacientePediatria(const string nome) : Paciente(nome, PacienteTipoEnum::PEDIATRIA) {};
};

#endif