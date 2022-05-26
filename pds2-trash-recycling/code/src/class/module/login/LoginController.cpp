#ifndef _LOGIN_CONTROLLER_CPP_
#define _LOGIN_CONTROLLER_CPP_

#include <stdio.h>
#include <memory>

#include "../../../../header/common/class/MenuItemSet.h"
#include "../../../../header/common/class/MenuController.h"
#include "../../../../header/module/login/LoginController.h"
#include "../../../../header/module/user/UserController.h"
#include "../../../../header/module/user/UserService.h"
#include "../../../../header/module/user/UserDAO.h"
#include "../../../../header/module/reject-type/RejectTypeController.h"
#include "../../../../header/module/reject-type/RejectTypeService.h"
#include "../../../../header/module/reject-type/RejectTypeDAO.h"
#include "../../../../header/module/meeting-point/MeetingPointController.h"
#include "../../../../header/module/meeting-point/MeetingPointService.h"
#include "../../../../header/module/meeting-point/MeetingPointDAO.h"
#include "../../../../header/module/scheduling/SchedulingController.h"
#include "../../../../header/module/scheduling/SchedulingService.h"
#include "../../../../header/module/scheduling/SchedulingDAO.h"

using namespace std;

void LoginController::reset(void) {
    this->userLoginCode = 0;
    this->userLoginPwd = "";
};

// @todo: Ocultar senha do usuario!!
// void LoginController::getLoginUserPwd(void) {
//     string readInput;
//     cout << "Informe a senha do usuario: ";
//     cin >> readInput;
//     if (readInput != "0") this->userLoginPwd = readInput;
// };

// @todo: Validar senha
shared_ptr<UserModel> LoginController::login() {

    do {

        // Inicializa tela de LOGIN
        this->reset();
        cout << "> LOGIN" << endl
             << "pressione '0' para sair" << endl
             << endl;

        try {

            // Captura codigo & senha para login
            this->userLoginCode = this->getNumberFromStdIO("Informe o Codigo do usuario", "Codigo invalido");
            if (!this->userLoginCode) return nullptr;

            // @todo: Validar senha
            // this->getLoginUserPwd();
            // if (this->userLoginPwd != "") return false;

            // Executa autenticacao
            auto searchResult = this->userDao->findOne(this->userLoginCode, "");
            auto loggedUser = searchResult.foundRegister;

            if (loggedUser != nullptr) {

                cout << "Login realizado com sucesso: Seja bem vindo(a) "
                    << loggedUser->getName()
                    << " (" << this->userService->getUserTypeLabel((UserTypeEnum)loggedUser->getType()) << ")!"
                    << endl << endl;

                return loggedUser;
            }

            cout << "Usuario nao encontrado!" << endl << endl;

        } catch (exception error) {
            cout << "Falha inesperada ao tentar realizar autenticacao de usuario" << endl;
        }

        cout << "Realizar nova tentativa? (s/n): ";
        string tryAgain;
        cin >> tryAgain;
        cout << endl;
        if (tryAgain != "s") return nullptr;

    } while (true);
};

void LoginController::showLoggedOptions(const shared_ptr<UserModel> loggedUser) {

    // Ininicializar dependencias
    vector<MenuItemSet> menuItems;

    auto rejectTypeService = make_shared<RejectTypeService>();
    auto rejectTypeDao = make_shared<RejectTypeDAO>(rejectTypeService);
    auto rejectTypeController = make_shared<RejectTypeController>(rejectTypeDao, rejectTypeService);

    auto userService = make_shared<UserService>(rejectTypeDao);
    auto userDao = make_shared<UserDAO>(userService);
    auto userController = make_shared<UserController>(userDao, userService, rejectTypeService, rejectTypeDao);

    const auto mPointService = make_shared<MeetingPointService>();
    const auto mPointDao = make_shared<MeetingPointDAO>(mPointService);
    const auto mPointController = make_shared<MeetingPointController>(mPointDao, mPointService);

    // Opcoes exclusivas para usuario admin
    if (loggedUser->getType() == UserTypeEnum::ADMIN) {

        menuItems.push_back(MenuItemSet("Novo Tipo de Residuo", rejectTypeController, ControllerActionEnum::CREATE));
        menuItems.push_back(MenuItemSet("Listar Tipos de Residuo", rejectTypeController, ControllerActionEnum::RETRIVE, loggedUser));
        menuItems.push_back(MenuItemSet("Novo Ponto de Coleta", mPointController, ControllerActionEnum::CREATE));
        menuItems.push_back(MenuItemSet("Listar Pontos de Coleta", mPointController, ControllerActionEnum::RETRIVE));
        menuItems.push_back(MenuItemSet("Listar usuarios", userController, ControllerActionEnum::RETRIVE));

    // Opcoes exclusivas para usuarios que NAO sao admin
    } else {

        const auto schedulingService = make_shared<SchedulingService>(mPointDao, userDao, rejectTypeDao);
        const auto schedulingDao = make_shared<SchedulingDAO>(schedulingService);

        const auto schedulingController = make_shared<SchedulingController>(
                schedulingDao,
                schedulingService,
                mPointDao,
                mPointService,
                userDao,
                userService,
                rejectTypeDao,
                rejectTypeService
        );

        menuItems.push_back(MenuItemSet("Agendar Coleta de Residuos", schedulingController, ControllerActionEnum::CREATE, loggedUser));
        menuItems.push_back(MenuItemSet("Minhas coletas agendadas", schedulingController, ControllerActionEnum::RETRIVE, loggedUser));
    }

    // Opcoes validas para qualquer usuario
    menuItems.push_back(MenuItemSet("Atualizar dados pessoais", userController, ControllerActionEnum::UPDATE, loggedUser));
    menuItems.push_back(MenuItemSet("Sair", nullptr));

    // Exibir menu
    MenuController menuController("Menu Principal", menuItems);
    menuController.runAction();
};

bool LoginController::runAction(void) {

    auto loggedUser = this->login();

    if (loggedUser == nullptr) {
        cout << "Usuario selecionou: 'sair'..." << endl;
        return false;
    }

    this->showLoggedOptions(loggedUser);
    return true;
};

#endif