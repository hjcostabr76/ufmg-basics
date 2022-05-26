#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <iostream>
#include <memory>
#include "../interface/IModel.h"
#include "../../module/user/UserModel.h"

using namespace std;

/**
 * CONTROLLER
 * Classes generica a ser extendida por classes que implementem a funcao de Controlador no sistema
 * Trash Recycling System
 *
 * @author hjcostabr
 */
class Controller {

private:

    /** Emite falha generica para chamada invalida de metodos desta classe. */
    void throwBadFunctionCall(void) const;

protected:

    /** Codigo da acao do controller a ser realizada. */
    int action;

    /**
     * Interage com o usuario via cli para capturar 01 valor numerico.
     *
     * @param presentationMsg Mensagem de descricao do proposito do numero obtido.
     * @param invalidInputMsg Mensagem para caso de insercao de valor invalido.
     * @return Valor numerico valido obtido.
     */
    int getNumberFromStdIO(string presentationMsg, string invalidInputMsg) const;

    /**
     * Captura 01 resposta de sim/nao de 01 usuario via terminal.
     * @param presentationMsg Mensagem descritiva da pergunta.
     * @return SE a resposta foi 'sim'.
     */
    bool aksYesOrNoQuestionThroughStdIO(string presentationMsg) const;

    /**
     * Captura & retorna 01 string inserido pelo usuario do sistema via terminal.
     *
     * @param presentationMsg Mensagem descritiva do valor a ser capturado.
     * @return Valor capturado.
     */
    string getStringFromStdIO(const string presentationMsg);

public:

    Controller(void) {};
    ~Controller(void) {};

    /**
     * Encapsula procedimento de inicializacao do controlador.
     * @return Flag: Se execucao do programa do programa deve ser encerrada.
     */
    virtual bool runAction();

    /**
     * Encapsula procedimento de inicializacao do controlador.
     *
     * @param action Codigo da acao do controller a ser realizada.
     * @return Flag: Se execucao do programa do programa deve ser encerrada.
     */
    virtual bool runAction(int action);

    /**
     * Encapsula procedimento de inicializacao do controlador.
     *
     * @param action Codigo da acao do controller a ser realizada.
     * @param currentUser Usuario atual que executa a acao.
     * @return Flag: Se execucao do programa do programa deve ser encerrada.
     */
    virtual bool runAction(int action, shared_ptr<UserModel> currentUser);
};

#endif