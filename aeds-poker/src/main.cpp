#include <iostream>
#include <string.h>

#include "../include/types.h"
#include "../include/game.h"
#include "../include/debug.h"

using namespace std;





int getMatchedCountNumber(const int counts[CARDS_PER_SUIT], const int n) {
    for (int i = 0; i < CARDS_PER_SUIT; i++) {
        if (counts[i] == n)
            return i + 1;
    }
    return 0;
}













/**
 * 01 pair.
 * - In case of a tie, the one with the highest pair card wins;
 * - If it remains, the one with the highest lowest pair card wins;
 * - If it remains, the one with the highest card wins;
 */
// bool isOnePair(const Card cards[CARDS_PER_HAND], int &pairCard) {

//     bool isHigherHand = (
//         isRoyalStraightFlush(cards)
//         || isStraightFlush(cards)
//         || isFourOfKind(cards, NULL)
//         || isFullHouse(cards, NULL, NULL)
//         || isFlush(cards, NULL)
//         || isStraight(cards)
//         || isThreeOfKind(cards, NULL)
//         || isTwoPairs(cards, NULL, NULL)
//     );

//     if (isHigherHand)
//         return false;

//     pairCard = 0;
//     return hasNOfAKind(2, cards, &pairCard, NULL);
// }

/**
 * TODO: 2022-06-03 - ADD Hand detection tests
 * TODO: 2022-06-03 - ADD Tied hands comparison
 * TODO: 2022-06-03 - ADD Round sanity checks test
 */

int main(int argc, char const *argv[]) {
    
    cout << endl << "-- POKER system --" << endl << endl;

    ifstream readingStream;
    bool statusOK = true;

    try {

        // Read file
        if (argc != 2)
            throw invalid_argument("Invalid parameters number");

        const string filePath = argv[1];
        readingStream = ifstream(filePath);
        if (!readingStream.good())
            throw runtime_error("Failure as trying to read input file");

        // Build game
        Game game = readGame(readingStream);
        dbgPrintGame(game);

        // All good
        cout << endl << "FIM" << endl;

    } catch (invalid_argument &error) {
        cout << "Invalid command!" << endl;
        cout << "Input format: ./poker [input-file-path]" << endl << endl;
    
    } catch (exception &error) {
        statusOK = false;
        cout << "-- Ops! Something wrong isn't right... --" << endl;
        if (DEBUG_ENABLE)
            cout << "What went wrong: '" << error.what() << "'" << endl;
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