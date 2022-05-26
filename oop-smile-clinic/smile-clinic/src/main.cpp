/**
 * File: main.cpp
 * Author: hjCostaBR
 * 
 * Arquivo principal do sistema
 * Smile Clinic
 */
#include <iostream>
#include <vector>
#include <exception>

#include "class/pessoa/funcionario/Funcionario.h"
#include "class/pessoa/funcionario/Funcionario.cpp"
#include "class/pessoa/funcionario/FuncionarioClinicoGeral.h"
#include "class/pessoa/funcionario/FuncionarioOrtodontista.h"
#include "class/pessoa/funcionario/FuncionarioPediatra.h"
#include "class/pessoa/funcionario/FuncionarioSecretaria.h"
#include "class/pessoa/paciente/Paciente.h"
#include "class/pessoa/paciente/Paciente.cpp"
#include "class/pessoa/paciente/PacientePediatria.h"
#include "class/pessoa/paciente/PacienteClinicaGeral.h"
#include "class/pessoa/paciente/PacienteOrtodontia.h"
#include "class/Orcamento.h"
#include "class/Orcamento.cpp"
#include "class/Procedimento.h"
#include "class/Procedimento.cpp"
#include "class/Clinica.h"
#include "class/Clinica.cpp"
#include "../../date/Date.h"

using namespace std;

int main(int argsc, char **argsv) {

    // Instrucoes
    cout    << "\n== INSTRUCOES =================" << endl
            << "Nao utilizar espacos para definir os nomes solicitados durante a execucao!" << endl
            << "\nEntendeu? (s)" << endl << endl;

    getchar();

    // Captura nome da clinica
    char nome[50];

    cout << "\n\n";
    cout << "- Clinica\n";

    cout << "Informe o nome da clinica: ";
    scanf("%s", nome);
    string nomeClinica(nome);

    // Captura nomes dos funcionarios
    cout << "\n-Funcionarios\n";
    
    cout << "Informe o nome do Clinico Geral: ";
    scanf("%s", nome);
    string nomeClinicoGeral(nome);

    cout << "Informe o nome do Ortodontista: ";
    scanf("%s", nome);
    string nomeOrtodontista(nome);

    cout << "Informe o nome do Pediatra: ";
    scanf("%s", nome);
    string nomePediatra(nome);

    cout << "Informe o nome da Secretaria: ";
    scanf("%s", nome);
    string nomeSecretaria(nome);

    // Captura nomes dos pacientes
    cout << "\n-Pacientes\n";

    cout << "Informe o nome de um(a) paciente de Clinica Geral: ";
    scanf("%s", nome);
    string nomePacienteClinica(nome);

    cout << "Informe o nome de um(a) paciente de Ortodontia: ";
    scanf("%s", nome);
    string nomePacienteOrtodontia(nome);

    cout << "Informe o nome de um(a) paciente de Pediatria: ";
    scanf("%s", nome);
    string nomePacientePediatria(nome);

    // Cria clinica
    cout << "\n\n";
    Clinica clinica = Clinica(nomeClinica);

    // Cria funcionarios
    cout << "\n";
    vector<Funcionario*> funcionarios;
    
    funcionarios.push_back(new FuncionarioClinicoGeral(nomeClinicoGeral));
    funcionarios.push_back(new FuncionarioOrtodontista(nomeOrtodontista));
    funcionarios.push_back(new FuncionarioPediatra(nomePediatra));
    funcionarios.push_back(new FuncionarioSecretaria(nomeSecretaria));

    // Cria pacientes
    cout << "\n";

    vector<Paciente*> pacientes;
    pacientes.push_back(new PacienteClinicoGeral(nomePacienteClinica));
    pacientes.push_back(new PacienteOrtodontia(nomePacienteOrtodontia));
    pacientes.push_back(new PacientePediatria(nomePacientePediatria));

    // Identifica funcionarios
    cout << "\nTestando funcionarios: \n";

    for (uint i = 0; i < funcionarios.size(); i++) {
        funcionarios[i]->identificar();
        clinica.addPessoa(funcionarios[i]);
    }

    // Identifica pacientes
    cout << "\nTestando pacientes: \n";

    for (uint i = 0; i < pacientes.size(); i++) {
        pacientes[i]->identificar();
        clinica.addPessoa(pacientes[i]);
    }

    // Inicia simulacao (se necessario)
    char iniciar;
    cout << "\nIniciar simulacao? (s/n) ";
    cin >> iniciar;
    
    if (iniciar == 's') {

        // Add promocoes para a clinica
        char repetir;

        do {

            cout << "\nInsira o nome de uma nova promocao para a clinica '" << clinica.getNome() << "': " << endl;
            scanf("%s", nome);
            string nomePromocao(nome);

            clinica.addPromocao(nomePromocao);

            cout << "\nAdicionar mais uma promocao? (s/n) ";
            cin >> repetir;

        } while (repetir == 's');

        // Lista de procedimentos
        vector<Procedimento> procedimentos;

        // Procedimento: Limpeza
        Date* dataProcedimento = new Date("dd/mm/aaaa", "01/12/2017");
        procedimentos.push_back(Procedimento());
        procedimentos[0].setNome("Limpeza");
        procedimentos[0].setDentista(funcionarios[0]);
        procedimentos[0].setValor(50);
        procedimentos[0].setDataProcedimento(dataProcedimento);

        // Procedimento: Remover Siso
        dataProcedimento = new Date("dd/mm/aaaa", "01/11/2017");
        procedimentos.push_back(Procedimento());
        procedimentos[1].setNome("Remover Siso");
        procedimentos[1].setDentista(funcionarios[1]);
        procedimentos[1].setValor(350);
        procedimentos[1].setDataProcedimento(dataProcedimento);

        // Procedimento: Canal
        dataProcedimento = new Date("dd/mm/aaaa", "01/10/2017");
        procedimentos.push_back(Procedimento());
        procedimentos[2].setNome("Carie");
        procedimentos[2].setDentista(funcionarios[2]);
        procedimentos[2].setValor(250);
        procedimentos[2].setDataProcedimento(dataProcedimento);

        // Lista de orcamentos
        vector<Orcamento> orcamentos;

        // Orcamento: Bruno
        orcamentos.push_back(Orcamento());
        orcamentos[0].addProcedimento(procedimentos[0]);
        orcamentos[0].addProcedimento(procedimentos[1]);
        orcamentos[0].setPaciente(pacientes[0]);

        // Orcamento: Breno
        Date* dataPagamento = new Date("dd/mm/aaaa", "25/12/2017");
        orcamentos.push_back(Orcamento());
        orcamentos[1].addProcedimento(procedimentos[2]);
        orcamentos[1].addProcedimento(procedimentos[1]);
        orcamentos[1].setPaciente(pacientes[1]);
        orcamentos[1].setDataPagamento(dataPagamento);

        // Lista dados dos orcamentos
        cout << "\n\nListando orcamentos...\n";

        for (uint j = 0; j < orcamentos.size(); j++) {
            Orcamento orcamento = orcamentos[j];

            cout << "- " << (j + 1) << " - Orcamento do paciente " << orcamento.getPaciente()->getNome() << ":";
            cout << "\n\t- Valor: R$ " << orcamento.getValorTotal();

            if (orcamento.isPago()) {
                cout << "\n\t- Pago na data: " << orcamento.getDataPagamento()->getDate() << ";";

            } else {
                cout << "\n\t- Ainda nao foi pago;";
            }

            cout << "\n\t- Lista de procedimentos:";

            for (uint k = 0; k < orcamento.getProcedimentos().size(); k++) {
                Procedimento procedimento = orcamento.getProcedimentos()[k];
                cout << "\n\t\t- " << (k + 1) << " - " << procedimento.getNome();
                cout << "\n\t\t\t Dentista: " << procedimento.getDentista()->getNome() << ";";
                cout << "\n\t\t\t Preco: " << procedimento.getValor() << ";";
                cout << "\n\t\t\t Data: " << procedimento.getDataProcedimento()->getDate() << ";";
                cout << "\n";
            }

            cout << "\n";
        }

        // Notificar pacientes sobre promocoes
        cout << "\n\nGerar notificacao de promocoes:" << endl;

        do {

            cout << "\nInforme o nome de uma promocao para notificar os pacientes da clinica '" << clinica.getNome() << "'" << endl;
            scanf("%s", nome);
            string nomePromocao(nome);

            clinica.notificarPromocao(nomePromocao);

            cout << "\nNotificar sobre outra promocao? (s/n) ";
            cin >> repetir;

        } while (repetir == 's');
    }

    // Fim
    cout << "\n\nFinalizando execucao...\n";
}