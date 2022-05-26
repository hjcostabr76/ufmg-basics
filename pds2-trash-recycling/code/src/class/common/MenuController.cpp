#ifndef _MENU_CONTROLLER_CPP_
#define _MENU_CONTROLLER_CPP_

#include <iostream>
#include "../../../header/common/class/MenuController.h"

using namespace std;

bool MenuController::isSelectedItemValid(int selectedCode) {
    return (selectedCode >= 0 && selectedCode < this->menuItems.size());
}

void MenuController::showMenuOptions(void) {

    cout << ">> Opcoes Disponiveis:" << endl;

    for (int i = 0; i < this->menuItems.size(); i++) {
        cout << "\t- " << (i + 1) << " " << this->menuItems[i].getMenuString() << endl;
    }

    cout << endl;
}

MenuItemSet MenuController::showOptionsAndGetSelectedController(void) {

    bool tried = false;
    string readInput;
    int selectedOptionCode;

    do {

        // Notifica tentativa invalida (se necessario)
        if (tried) cout << "Opção invalida '" << readInput << "'!" << endl << endl;
        tried = true;

        // Exibe menu
        cout << "> " << this->name << endl;
        this->showMenuOptions();

        // Captura selecao de 01 item do menu
        cin >> readInput;
        cin.ignore();

        try {
            selectedOptionCode = (stoi(readInput) - 1);

        } catch(exception error) {
            selectedOptionCode = -1;
        }

    } while (!this->isSelectedItemValid(selectedOptionCode));

    // Exibe opcao selecionada
    MenuItemSet selectedOption = this->menuItems[selectedOptionCode];

    cout << endl
         << "Opcao selecionada: "
         << selectedOption.getMenuString() << endl
         << endl;

    // Retorna opcao selecionada
    return this->menuItems[selectedOptionCode];
}

bool MenuController::runAction(void) {

    do {

        auto selectedMenuItem = this->showOptionsAndGetSelectedController();

        // Valida se ha controlador
        auto controller = selectedMenuItem.getController();
        if (controller == nullptr) return false;

        // Chamada SEM parametros
        auto controllerAction = selectedMenuItem.getControllerAction();

        if (!controllerAction) {
            if (controller->runAction()) return true;
            cout << endl;
            continue;
        }

        // Chamada COM action
        auto currentUser = selectedMenuItem.getUser();

        if (currentUser == nullptr) {
            if (controller->runAction(controllerAction)) return true;
            cout << endl;
            continue;
        }

        // Chamada COM action + usuario
        if (controller->runAction(controllerAction, currentUser)) return true;
        cout << endl;

    } while (true);
}

#endif
