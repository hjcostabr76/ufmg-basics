/**
 * File: Clinica.h
 * Class: Clinica
 * Author: hjCostaBR
 * 
 * Define interface da classe Clinica no sistema
 * Smile Clinic
 */
#ifndef CLINICA_H
#define CLINICA_H

#include <string>
#include <vector>

#include "pessoa/Pessoa.h"
#include "pessoa/Pessoa.cpp"

using namespace std;

class Clinica {

private:
    vector<Pessoa*> pessoas;
    vector<string> promocoes;
    string nome;

public:
    Clinica(const string nome);
    
    void notificarPromocao(const string nomePromocao);
    void addPessoa(Pessoa* pessoa);
    void addPromocao(const string nomePromocao);

    // Getter
    vector<Pessoa*> getPessoas(void);
    string getNome(void);
    
    ~Clinica(void);
};

#endif