#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <exception>
#include <fstream>
#include <sstream>

#include "../include/common.h"

const string filePath = "src/entrada.txt";

// Play readPlay(ifstream &inputStream) {

//     string aux;
//     string line;
//     getline(inputStream, line);
//     stringstream lineStream(line);


//     cout << "readPlay" << endl;

//     Play play;
//     getline(lineStream, play.playerName, ' ');
//     getline(lineStream, aux, ' ');
//     play.bid = stoi(aux);

//     for (int i = 0; i < CARDS_COUNT; i++) {

//         cout << "read card..." << endl;

//         getline(lineStream, aux, ' ');
//         // play.cards[i].suit = aux[aux.length() - 1];
//         // play.cards[i].number = stoi(aux.substr(0, aux.length() - 1));
//     }

//     cout << "readPlay 2..." << endl;
//     return play;
// }

Round readRound(ifstream &inputStream) {

    string aux;
    string line;
    getline(inputStream, line);
    stringstream lineStream(line);

    // Read round parameters
    Round round;
    getline(lineStream, aux, ' ');
    round.nPlays = stoi(aux);
    getline(lineStream, aux, ' ');
    round.blind = stoi(aux);

    // Read round plays
    round.plays = (Play*)malloc(round.nPlays * sizeof(Play));
    // round.plays[0] = readPlay(inputStream);
    // for (int i = 0; i < round.nPlays; i++)
    //     round.plays[i] = *readPlay(inputStream);

    for (int i = 0; i < round.nPlays; i++) {
        getline(inputStream, line);
        lineStream = stringstream(line);

        Play play;
        getline(lineStream, play.playerName, ' ');
        getline(lineStream, aux, ' ');
        play.bid = stoi(aux);

        for (int i = 0; i < CARDS_COUNT; i++) {
            getline(lineStream, aux, ' ');
            play.cards[i].suit = aux[aux.length() - 1];
            play.cards[i].number = stoi(aux.substr(0, aux.length() - 1));
        }

        round.plays[i] = play;   
    }
    
    return round;
}

Game readGame(ifstream &inputStream) {

    string aux;
    string line;
    getline(inputStream, line);
    stringstream lineStream(line);

    // Read game parameters
    Game game;
    getline(lineStream, aux, ' ');
    game.nRounds = stoi(aux);
    getline(lineStream, aux, ' ');
    game.initialAmount = stoi(aux);

    // Read rounds
    game.rounds = (Round*)malloc(game.nRounds * sizeof(Round));
    for (int i = 0; i < game.nRounds; i++)
        game.rounds[i] = readRound(inputStream);

    return game;
}

// int main(int argc, char const *argv[]) {
int main() {

    std::cout << endl << "-- POKER system --" << endl << endl;

    ifstream readingStream;
    bool statusOK = true;

    try {
        readingStream = ifstream(filePath);
        if (!readingStream.good())
            throw runtime_error("Failure as trying to read input file");

        Game game = readGame(readingStream);
        dbgPrintGame(game);

        cout << endl << "FIM" << endl;

    } catch (exception &error) {
        statusOK = false;
        cout << endl << "-- Ops! Something wrong isn't right... --" << endl;
        if (DEBUG_ENABLE)
            cout << error.what() << endl;
        cout << endl;
    }

    if (readingStream.is_open())
        readingStream.close();

    // Fim da execucao
    return statusOK ? EXIT_SUCCESS : EXIT_FAILURE;

    // if (this->writingStream.is_open()) {
    //     this->writingStream.close();
    //     return;
    // }

    // if (!this->writingStream.good())
    //     throw runtime_error("Falha ao tentar abrir arquivo de armazenamento para escrita (" + this->getStorageFileName() + ")");


    // // Prepara controller de usuarios
    // auto rejTypeService = make_shared<RejectTypeService>();
    // auto regTypeDao = make_shared<RejectTypeDAO>(rejTypeService);
    // auto userService = make_shared<UserService>(regTypeDao);
    // auto userDao = make_shared<UserDAO>(userService);
    // auto userController = make_shared<UserController>(userDao, userService, rejTypeService, regTypeDao);

    // // Exibir menu principal
    // vector<MenuItemSet> menuItems;

    // menuItems.push_back(MenuItemSet("Login", make_shared<LoginController>(userDao, userService)));
    // menuItems.push_back(MenuItemSet("Cadastro", userController, ControllerActionEnum::CREATE));
    // menuItems.push_back(MenuItemSet("Sair", nullptr));

    // MenuController menuController("Menu Inicial", menuItems);
    // menuController.runAction();
}