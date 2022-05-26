#ifndef _CONTROLLER_CPP_
#define _CONTROLLER_CPP_

#include <string>
#include <iostream>
#include <functional>
#include "../../../header/common/class/Controller.h"
#include "../../../header/common/interface/IModel.h"
#include "../../../header/module/user/UserModel.h"

using namespace std;

void Controller::throwBadFunctionCall(void) const {
    throw bad_function_call();
}

int Controller::getNumberFromStdIO(string presentationMsg, string invalidInputMsg) const {

    bool reapeat = false;
    bool tried = false;
    string readInput;
    int number;

    do {

        // Notifica tentativa invalida (se necessario)
        if (tried) cout << invalidInputMsg << "'" << readInput << "'!" << endl << endl;
        tried = true;

        // Captura entrada
        cout << presentationMsg << ": ";
        cin >> readInput;
        cin.ignore();

        try {
            number = stoi(readInput);
            reapeat = false;

        } catch (exception error) {
            reapeat = true;
        }

    } while (reapeat);

    return number;
};

bool Controller::aksYesOrNoQuestionThroughStdIO(string presentationMsg) const {
    cout << presentationMsg << " (s/n): ";
    string answer;
    cin >> answer;
    cout << endl;
    return (answer == "s");
};

string Controller::getStringFromStdIO(const string presentationMsg) {
    cout << presentationMsg;
    char readInput[100];
    cin.clear();
    cin.ignore();
    cin.getline(readInput, sizeof(readInput));
    return string(readInput);
}

bool Controller::runAction(void) {
    this->throwBadFunctionCall();
};

bool Controller::runAction(const int action) {
    this->throwBadFunctionCall();
}

bool Controller::runAction(const int action, const shared_ptr<UserModel> currentUser) {
    this->throwBadFunctionCall();
}

#endif
