#include <iostream>
#include <string.h>

#include "../include/game.h"
#include "../include/debug.h"

using namespace std;

typedef enum {
    HAND_ROYAL_STRAIGHT_FLUSH,
    HAND_STRAIGHT_FLUSH,
    HAND_4_KIND,
    HAND_FULL_HOUSE,
    HAND_FLUSH,
    HAND_STRAIGHT,
    HAND_3_KIND,
    HAND_2_PAIRS,
    HAND_PAIR,
    HAND_HIGHER_CARD
} HandEnum;

bool isValidCardNumber(const int number) {
    return number >= 1 && number <= 13;
}

bool isValidSuit(const char suit) {
    char validSuits[SUITS_COUNT] = { CARD_SUIT_CLUBS, CARD_SUIT_SPADES, CARD_SUIT_HEARTS, CARD_SUIT_DIAMONDS };
    for (int i = 0; i < SUITS_COUNT; i++) {
        if (suit == validSuits[i])
            return true;
    }
    return false;
}

bool isSequence(const Card cards[CARDS_COUNT]) {
    
    for (int i = 1; i < CARDS_COUNT; i++) {

        int prevNumber = cards[i - 1].number - 1;
        int currentNumber = cards[i].number;
        
        bool isValidNumber = (
            (prevNumber != 13 & currentNumber == (prevNumber + 1))
            || (prevNumber == 13 & currentNumber == 1) // Considers the ace as the last card
        );
        
        if (!isValidNumber)
            return false;
    }

    return true;
}

bool isSameSuitSequence(const Card cards[CARDS_COUNT]) {

    if (!isSequence(cards))
        return false;

    char suit = cards[0].suit;
    for (int i = 1; i < CARDS_COUNT; i++) {
        if (cards[i].suit != suit)
            return false;
    }

    return true;
}

void countCards(const Card cards[CARDS_COUNT], int counts[CARDS_PER_SUIT]) {
    for (int i = 0; i < CARDS_COUNT; i++)
        counts[cards[i].number - 1]++;
}

bool hasNOfAKind(const int n, const Card cards[CARDS_COUNT], int *matchedNumber, int counts[CARDS_PER_SUIT]) {

    // Set each number occurrences count
    if (counts == NULL)
        counts = (int*)malloc(CARDS_PER_SUIT * sizeof(int));
    countCards(cards, counts);

    // Check if we have the exact counting we're looking for
    if (matchedNumber == NULL)
        matchedNumber = (int*)malloc(sizeof(int));
    *matchedNumber = 0;

    int bestCount = 0;
    for (int i = 0; i < CARDS_COUNT; i++) {
        int thisCount = counts[cards[i].number - 1];
        if (thisCount > bestCount) {
            bestCount = thisCount;
            *matchedNumber = cards[i].number;
        }
    }

    return bestCount == n;
}

int getMatchedCountNumber(const int counts[CARDS_PER_SUIT], const int n) {
    for (int i = 0; i < CARDS_PER_SUIT; i++) {
        if (counts[i] == n)
            return i + 1;
    }
    return 0;
}

/** Returns a copy of a hand removing specific number 'n' (in case it's in the hand). */
Card* getCardsWithoutN(const Card cards[CARDS_COUNT], const int n) {
    Card cardsCopy[CARDS_COUNT] = { 0 };
    for (int i = 0; i < CARDS_PER_SUIT; i++) {
        cardsCopy[i] = cards[i];
        if (cardsCopy[i].number == n)
            cardsCopy[i].number = 0;
    }
    return cardsCopy;
}

/** 05 cards of the same suit in row counting from 10 to Aces. */
bool isRoyalStraightFlush(const Card cards[CARDS_COUNT]) {
    int firstNumber = cards[0].number;
    return firstNumber == 10 && isSameSuitSequence(cards);
}

/** 05 cards of the same suit in a row NOT counting from 10 to Ace (!= RSF). */
bool isStraightFlush(const Card cards[CARDS_COUNT]) {
    int firstNumber = cards[0].number;
    return firstNumber < 10 && isSameSuitSequence(cards); // 1st number >= 10 would be RSF or nothing at all
}

/**
 * 04 equal cards.
 * - In case of a tie the higher number hand wins;
 * - If it remains tied the one with the higher fifth card wins;
 */
bool isFourOfKind(const Card cards[CARDS_COUNT], int *fourOfKindNumber) {
    bool isHigherHand = isRoyalStraightFlush(cards) || isStraightFlush(cards);
    return !isHigherHand && hasNOfAKind(4, cards, fourOfKindNumber, NULL);
}

/**
 * 01 pair + 03 of a kind.
 * - In case of a tie, the higher 03 of a kind wins;
 * - If it remains tied, the higher pair wins;
 */
bool isFullHouse(const Card cards[CARDS_COUNT], int *threeOfKindNumber, int *pairNumber) {

    threeOfKindNumber = 0;
    pairNumber = 0;

    bool isHigherHand = isRoyalStraightFlush(cards) || isStraightFlush(cards) || isFourOfKind(cards, NULL);
    if (isHigherHand)
        return false;

    // Check the 03 of a kind part
    int counts[CARDS_PER_SUIT] = { 0 };
    if (!hasNOfAKind(3, cards, threeOfKindNumber, counts))
        return false;

    // Check the pair part
    Card* cardsCopy = getCardsWithoutN(cards, *threeOfKindNumber);
    return hasNOfAKind(2, cardsCopy, pairNumber, NULL);
}

/**
 * 05 cards of the same suit (without being in a row).
 * - In case of a tie the one with the highest card wins;
 */
bool isFlush(const Card cards[CARDS_COUNT], char *suit) {

    bool isHigherHand = (
        isRoyalStraightFlush(cards)
        || isStraightFlush(cards)
        || isFourOfKind(cards, NULL)
        || isFullHouse(cards, NULL, NULL)
    );

    if (isHigherHand)
        return false;

    if (suit == NULL)
        suit = (char*)malloc(sizeof(char));
    *suit = cards[0].suit;

    for (int i = 1; i < CARDS_COUNT; i++) {
        if (cards[i].suit != *suit)
            return false;
    }
    return true;
}

/**
 * 05 cards in a row not caring about the suit.
 * - In case of a tie, the one with highest card wins;
 */
bool isStraight(const Card cards[CARDS_COUNT]) {

    bool isHigherHand = (
        isRoyalStraightFlush(cards)
        || isStraightFlush(cards)
        || isFourOfKind(cards, NULL)
        || isFullHouse(cards, NULL, NULL)
        || isFlush(cards, NULL)
    );

    return !isHigherHand && isSequence(cards);
}

/**
 * 03 equal cards + 02 different ones.
 * - In case of a tie, the one with the highest 03 of a kind card wins;
 * - If it remains, the one with the highest card wins;
 */
bool isThreeOfKind(const Card cards[CARDS_COUNT], int *threeOfKindNumber) {

    bool isHigherHand = (
        isRoyalStraightFlush(cards)
        || isStraightFlush(cards)
        || isFourOfKind(cards, NULL)
        || isFullHouse(cards, NULL, NULL)
        || isFlush(cards, NULL)
        || isStraight(cards)
    );

    if (isHigherHand)
        return false;

    int counts[CARDS_PER_SUIT] = { 0 };
    return hasNOfAKind(3, cards, threeOfKindNumber, counts);
}

/**
 * 02 pairs.
 * - In case of a tie, the one with the highest pair card wins;
 * - If it remains, the one with the highest lowest pair card wins;
 * - If it remains, the one with the highest card wins;
 */
bool isTwoPairs(const Card cards[CARDS_COUNT], int *pairNumber1, int *pairNumber2) {
    
    bool isHigherHand = (
        isRoyalStraightFlush(cards)
        || isStraightFlush(cards)
        || isFourOfKind(cards, NULL)
        || isFullHouse(cards, NULL, NULL)
        || isFlush(cards, NULL)
        || isStraight(cards)
        || isThreeOfKind(cards, NULL)
    );

    if (isHigherHand)
        return false;

    // Check if we have any pairs
    int counts[CARDS_PER_SUIT] = { 0 };
    if (!hasNOfAKind(2, cards, pairNumber1, counts))
        return false;
    
    // Check if we have a 2nd pair
    Card* cardsCopy = getCardsWithoutN(cards, *pairNumber1);
    return hasNOfAKind(2, cardsCopy, pairNumber2, NULL);
}

/**
 * 01 pair.
 * - In case of a tie, the one with the highest pair card wins;
 * - If it remains, the one with the highest lowest pair card wins;
 * - If it remains, the one with the highest card wins;
 */
bool isOnePair(const Card cards[CARDS_COUNT], int &pairCard) {

    bool isHigherHand = (
        isRoyalStraightFlush(cards)
        || isStraightFlush(cards)
        || isFourOfKind(cards, NULL)
        || isFullHouse(cards, NULL, NULL)
        || isFlush(cards, NULL)
        || isStraight(cards)
        || isThreeOfKind(cards, NULL)
        || isTwoPairs(cards, NULL, NULL)
    );

    if (isHigherHand)
        return false;

    pairCard = 0;
    return hasNOfAKind(2, cards, &pairCard, NULL);
}

HandEnum getHand(const Card cards[CARDS_COUNT]) {

    if (isRoyalStraightFlush(cards))
        return HAND_ROYAL_STRAIGHT_FLUSH;

    if (isStraightFlush(cards))
        return HAND_STRAIGHT_FLUSH;

    int fourOfKindNumber = 0;
    if (isFourOfKind(cards, &fourOfKindNumber))
        return HAND_4_KIND;

    int threeOfKindNumber = 0;
    int pairNumber1 = 0;
    if (isFullHouse(cards, &threeOfKindNumber, &pairNumber1))
        return HAND_FULL_HOUSE;

    char suit = ' ';
    if (isFlush(cards, &suit))
        return HAND_FLUSH;

    if (isStraight(cards))
        return HAND_STRAIGHT;

    if (isThreeOfKind(cards, &threeOfKindNumber))
        return HAND_3_KIND;

    int pairNumber2 = 0;
    if (isTwoPairs(cards, &pairNumber1, &pairNumber2))
        return HAND_2_PAIRS;

    if (isOnePair(cards, pairNumber1))
        return HAND_PAIR;

    return HAND_HIGHER_CARD;
}

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