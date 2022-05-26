#ifndef _MENU_ITEM_SET_CPP_
#define _MENU_ITEM_SET_CPP_

#include <string>
#include <memory>
#include "../../../header/common/class/Controller.h"
#include "../../../header/common/class/MenuItemSet.h"


string MenuItemSet::getMenuString(void) const {
    return this->menuString;
};

shared_ptr<Controller> MenuItemSet::getController(void) const {
    return this->controller;
};

int MenuItemSet::getControllerAction(void) const {
    return this->controllerAction;
}

shared_ptr<UserModel> MenuItemSet::getUser(void) const {
    return this->currentUser;
};

#endif