#include <iostream>
#include <string.h>

#include "../include/types.h"
#include "../include/game.h"
#include "../include/debug.h"

using namespace std;

bool isValidCardNumber(const int number) {
    return number >= CARD_NUM_ACE && number <= CARD_NUM_KING;
}

/**
 * TODO: 2022-06-03 - Will we really need this?
 */
bool isValidSuit(const char suit) {
    char validSuits[SUITS_COUNT] = { SUIT_CLUBS, SUIT_SPADES, SUIT_HEARTS, SUIT_DIAMONDS };
    for (int i = 0; i < SUITS_COUNT; i++) {
        if (suit == validSuits[i])
            return true;
    }
    return false;
}



int getMatchedCountNumber(const int counts[CARDS_PER_SUIT], const int n) {
    for (int i = 0; i < CARDS_PER_SUIT; i++) {
        if (counts[i] == n)
            return i + 1;
    }
    return 0;
}









/**
 * 05 cards of the same suit (without being in a row).
 * - In case of a tie the one with the highest card wins;
 */
// bool isFlush(const Card cards[CARDS_PER_HAND], char *suit) {

//     bool isHigherHand = (
//         isRoyalStraightFlush(cards)
//         || isStraightFlush(cards)
//         || isFourOfKind(cards, NULL)
//         || isFullHouse(cards, NULL, NULL)
//     );

//     if (isHigherHand)
//         return false;

//     if (suit == NULL)
//         suit = (char*)malloc(sizeof(char));
//     *suit = cards[0].suit;

//     for (int i = 1; i < CARDS_PER_HAND; i++) {
//         if (cards[i].suit != *suit)
//             return false;
//     }
//     return true;
// }

/**
 * 05 cards in a row not caring about the suit.
 * - In case of a tie, the one with highest card wins;
 */
// bool isStraight(const Card cards[CARDS_PER_HAND]) {

//     bool isHigherHand = (
//         isRoyalStraightFlush(cards)
//         || isStraightFlush(cards)
//         || isFourOfKind(cards, NULL)
//         || isFullHouse(cards, NULL, NULL)
//         || isFlush(cards, NULL)
//     );

//     return !isHigherHand && isSequence(cards);
// }

/**
 * 03 equal cards + 02 different ones.
 * - In case of a tie, the one with the highest 03 of a kind card wins;
 * - If it remains, the one with the highest card wins;
 */
// bool isThreeOfKind(const Card cards[CARDS_PER_HAND], int *threeOfKindNumber) {

//     bool isHigherHand = (
//         isRoyalStraightFlush(cards)
//         || isStraightFlush(cards)
//         || isFourOfKind(cards, NULL)
//         || isFullHouse(cards, NULL, NULL)
//         || isFlush(cards, NULL)
//         || isStraight(cards)
//     );

//     if (isHigherHand)
//         return false;

//     int counts[CARDS_PER_SUIT] = { 0 };
//     return hasNOfAKind(3, cards, threeOfKindNumber, counts);
// }

/**
 * 02 pairs.
 * - In case of a tie, the one with the highest pair card wins;
 * - If it remains, the one with the highest lowest pair card wins;
 * - If it remains, the one with the highest card wins;
 */
// bool isTwoPairs(const Card cards[CARDS_PER_HAND], int *pairNumber, int *pairNumber2) {
    
//     bool isHigherHand = (
//         isRoyalStraightFlush(cards)
//         || isStraightFlush(cards)
//         || isFourOfKind(cards, NULL)
//         || isFullHouse(cards, NULL, NULL)
//         || isFlush(cards, NULL)
//         || isStraight(cards)
//         || isThreeOfKind(cards, NULL)
//     );

//     if (isHigherHand)
//         return false;

//     // Check if we have any pairs
//     int counts[CARDS_PER_SUIT] = { 0 };
//     if (!hasNOfAKind(2, cards, pairNumber, counts))
//         return false;
    
//     // Check if we have a 2nd pair
//     Card* cardsCopy = removeCardFromHand(cards, *pairNumber);
//     return hasNOfAKind(2, cardsCopy, pairNumber2, NULL);
// }

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