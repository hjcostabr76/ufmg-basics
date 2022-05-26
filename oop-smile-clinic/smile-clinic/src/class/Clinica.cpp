/**
 * File: Clinica.cpp
 * Class: Clinica
 * Author: hjCostaBR
 * 
 * Define implementacao da classe Clinica no sistema
 * Smile Clinic
 */
#ifndef CLINICA_CPP
#define CLINICA_CPP

#include <string>
#include <vector>

#include "Clinica.h"
#include "pessoa/Pessoa.h"
#include "pessoa/Pessoa.cpp"

using namespace std;

Clinica::Clinica(const string nome) {
    this->nome = nome;
    cout << "Criando clinica: " << nome << endl;
}

// Add pessoa a lista de pessoas relacionadas a clinica
void Clinica::addPessoa(Pessoa* pessoa) {
    this->pessoas.push_back(pessoa);
}

void Clinica::addPromocao(const string nomePromocao) {
    this->promocoes.push_back(nomePromocao);
    cout << "Adicionando promocao '" << nomePromocao << "' para a clinica '" << this->nome << "'" << endl;
}

// Notifica clientes de uma nova promocao
void Clinica::notificarPromocao(const string nomePromocao) {

    // Verifica se a promocao solicitada existe
    bool found = false;

    for (uint i = 0; i < this->promocoes.size(); i++) {
        if (this->promocoes[i] == nomePromocao) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Ops! Nenuma promocao cadastrada com esse nome (" << nomePromocao << ")...";
        return;
    }

    // Notifica pacientes da promocao
    for (uint i = 0; i < this->pessoas.size(); i++) {

        Pessoa* pessoa = this->pessoas[i];

        if (pessoa->getTipo() == PessoaTipoEnum::PACIENTE) {
            cout << "Notificando paciente '" << pessoa->getNome() << "' da promocao: '" << nomePromocao << "'..." << endl;
        }
    }
}

// Getter: Nome
string Clinica::getNome(void) {
    return this->nome;
}

// Destrutor: Chama o destrutor de cada pessoa associada a clinica
Clinica::~Clinica() {
    for (uint i = 0; i < this->pessoas.size(); i++) {
        this->pessoas[i]->~Pessoa();
    }
}

#endif