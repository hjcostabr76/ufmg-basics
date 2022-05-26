#ifndef _MENU_CONTROLLER_H_
#define _MENU_CONTROLLER_H_

#include <vector>
#include <memory>

#include "Controller.h"
#include "MenuItemSet.h"

/*
 * Controller do MENU PRINCIPAL do sistema
 * Trash Recycling System
 * 
 * @author hjcostabr
 */
class MenuController: public Controller {

private:

    /** Nome (titulo) do Menu. */
    string name;

    /** Lista de opcoes do Menu. */
    vector<MenuItemSet> menuItems;


    /**
     * Avalia se 01 item de menu informado pelo usuario corresponde a 01 item do menu valido.
     *
     * @param selectedCode Valor informado pelo usuario.
     * @return bool
     */
    bool isSelectedItemValid(int selectedCode);

    /** Exibe lista de opcoes do menu. */
    void showMenuOptions(void);

    /** Exibe opcoes do menu para capturar & retornar controller da opcao selecionada pelo usuario (se houver). */
    MenuItemSet showOptionsAndGetSelectedController(void);

public:

    /**
     * Construtor.
     *
     * @param name Nome (titulo) do menu.
     * @param menuItems Lista de opcoes do menu.
     */
    MenuController(string name, vector<MenuItemSet> menuItems) :
        name(name),
        menuItems(menuItems) {};

    /**
     * @inherit
     */
    virtual bool runAction(void) override;
};

#endif