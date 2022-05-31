#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <exception>
#include <fstream>
#include <sstream>

#define DEBUG_ENABLE true

#define CARDS_COUNT 5
#define CARD_SUIT_SPADES 'E'
#define CARD_SUIT_HEARTS 'C'
#define CARD_SUIT_CLUBS 'P'
#define CARD_SUIT_DIAMONDS 'O'

using namespace std;

const string filePath = "src/entrada.txt";

typedef struct {
    char suit;
    int number;
} Card;

typedef struct {
    int bid;
    string playerName;
    Card cards[CARDS_COUNT];
} Play;

typedef struct {
    int money;
    string name;
    Play* plays;
} Player;

typedef struct {
    int blind;
    int nPlays;
    Play* plays;
} Round;

typedef struct {
    int nRounds;
    int initialAmount;
    Round* rounds;
} Game;


string dbgGetCardPrint(const Card card) {
    string suit;
    suit += card.suit;
    return "[card] suit: '" + suit + "'; number: '" + to_string(card.number) + "';";
}

string dbgGetPlayPrint(const Play play) {
    string print = "[play] bid: '" + to_string(play.bid) + "'; playerName: '" + play.playerName + "'; cards:";
    for (int i = 0; i < CARDS_COUNT; i++)
        print += "\n\t\t\t" + dbgGetCardPrint(play.cards[i]);
    return print;    
}

string dbgGetRoundPrint(const Round round) {
    string print = "[round] blind: '" + to_string(round.blind) + "'; nPlays: '" + to_string(round.nPlays) + "'; plays:";
    for (int i = 0; i < round.nPlays; i++)
        print += "\n\t\t" + dbgGetPlayPrint(round.plays[i]);
    return print;
}


string dbgGetGamePrint(const Game game) {
    string print = "[game] nRounds: '" + to_string(game.nRounds) + "'; initialAmount: '" + to_string(game.initialAmount) + "'; rounds:";
    for (int i = 0; i < game.nRounds; i++)
        print += "\n\t" + dbgGetRoundPrint(game.rounds[i]);
    return print;
}

void dbgPrintGame(const Game game) {
    if (DEBUG_ENABLE) {
        cout << "---------- DBG: Game ----------" << endl;
        cout << dbgGetGamePrint(game);
        cout << endl;
        cout << "---------- || --- || ----------" << endl;
    }
}

void dbgPrintRound(const Round round) {
    if (DEBUG_ENABLE) {
        cout << "---------- DBG: Round ---------" << endl;
        cout << dbgGetRoundPrint(round);
        cout << endl;
        cout << "---------- || --- || ----------" << endl;
    }
}

void dbgPrintPLay(const Play play) {
    if (DEBUG_ENABLE) {
        cout << "---------- DBG: Play ----------" << endl;
        cout << dbgGetPlayPrint(play);
        cout << endl;
        cout << "---------- || --- || ----------" << endl;
    }
}

void dbgStep(string msg) {
    if (DEBUG_ENABLE)
        cout << msg << endl;
}

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

int main(int argc, char const *argv[]) {

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