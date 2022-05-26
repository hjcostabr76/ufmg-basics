#ifndef _LOGIN_CONTROLLER_H_
#define _LOGIN_CONTROLLER_H_

#include "../../common/class/Controller.h"
#include "../../common/class/MenuController.h"
#include "../../module/user/UserDAO.h"
#include "../../module/user/UserService.h"

/**
 * CONTROLLER
 * Gerencia a interacao com a 'tela' de LOGIN de usuario no sistema
 * Trash Recycling System
 * 
 * @author hjcostabr
 */
class LoginController: public Controller {

private:

    /** DAO de usuario. */
    shared_ptr<UserDAO> userDao = nullptr;

    /** Classe de servico de usuario. */
    shared_ptr<UserService> userService = nullptr;

    /** Codigo do usuario para o qual eh feita 01 tentativa de login. */
    int userLoginCode = 0;

    /** Senha do usuario para o qual eh feita 01 tentativa de login. */
    string userLoginPwd = "";


    /** Forca valor das variaveis necessarias para autenticacao para seus valores 'default'. */
    void reset(void);

    /** Captura senha para autenticacao do usuario. */
    // void getLoginUserPwd(void);

    /**
     * Encapsula procedimento de interacao com usuario para realizar login.
     * @return Usuario logado (em caso de sucesso).
     */
    shared_ptr<UserModel> login(void);

    /**
     * Monta & exibe opcoes para usuario logado.
     * @param loggedUser Usuario logado.
     */
    void showLoggedOptions(const shared_ptr<UserModel> loggedUser);

public:

    /** Contrutor. */
    LoginController(const shared_ptr<UserDAO> userDao, const shared_ptr<UserService> userService)
        : userDao(userDao), userService(userService)
        {};

    /**
     * @inherit
     */
    virtual bool runAction(void) override;
};

#endif