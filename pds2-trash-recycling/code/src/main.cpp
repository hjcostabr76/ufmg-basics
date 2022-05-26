#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>

#include "../header/common/enums.h"
#include "../header/common/class/MenuItemSet.h"
#include "../header/common/class/Controller.h"
#include "../header/common/class/MenuController.h"
#include "../header/module/login/LoginController.h"
#include "../header/module/user/UserController.h"

using namespace std;

/**
 * MAIN
 * Funcao principal do sistema
 * Trash Recycling System
 * 
 * @author hjcostabr
 */
int main(int argc, char const *argv[]) {

    // Cabecalho
    cout << endl
         << "-- SISTEMA DE CONTROLE DE RECICLAGEM DE LIXO --"
         << endl << endl;

    // Prepara controller de usuarios
    auto rejTypeService = make_shared<RejectTypeService>();
    auto regTypeDao = make_shared<RejectTypeDAO>(rejTypeService);
    auto userService = make_shared<UserService>(regTypeDao);
    auto userDao = make_shared<UserDAO>(userService);
    auto userController = make_shared<UserController>(userDao, userService, rejTypeService, regTypeDao);

    // Exibir menu principal
    vector<MenuItemSet> menuItems;

    menuItems.push_back(MenuItemSet("Login", make_shared<LoginController>(userDao, userService)));
    menuItems.push_back(MenuItemSet("Cadastro", userController, ControllerActionEnum::CREATE));
    menuItems.push_back(MenuItemSet("Sair", nullptr));

    MenuController menuController("Menu Inicial", menuItems);
    menuController.runAction();

    // Fim da execucao
    cout << endl << "FIM" << endl;
    return 0;
}