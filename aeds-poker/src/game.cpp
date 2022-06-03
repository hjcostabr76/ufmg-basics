#include <stdlib.h>
#include <string.h>
#include <memory>
#include <sstream>

#include "../include/game.h"
#include "../include/debug.h"

/**
 * ------------------------------------------------
 * == HAND PARSING HELPERS ========================
 * ------------------------------------------------
 */

bool isSequence(const Card cards[CARDS_PER_HAND]) {
    
    for (int i = 1; i < CARDS_PER_HAND; i++) {

        int prevNumber = cards[i - 1].number;
        int currentNumber = cards[i].number;
        
        bool isValidNumber = (
            (prevNumber != CARD_NUM_KING && currentNumber == (prevNumber + 1))
            || (prevNumber == CARD_NUM_KING && currentNumber == CARD_NUM_ACE) // Considers the ace as the last card
        );
        
        if (!isValidNumber)
            return false;
    }

    return true;
}

bool isSameSuitSequence(const Card cards[CARDS_PER_HAND], char *suit) {

    if (!isSequence(cards))
        return false;

    if (suit == NULL)
        suit = (char*)malloc(sizeof(char));
    
    *suit = cards[0].suit;
    for (int i = 1; i < CARDS_PER_HAND; i++) {
        if (cards[i].suit != *suit)
            return false;
    }

    return true;
}

void sortCards(Card cards[CARDS_PER_HAND]) {
    
    // Do the regular sort
    for (int i = 0; i < CARDS_PER_HAND; i++) {
        for (int j = 1; j < CARDS_PER_HAND; j++) {
            Card prev = cards[j - 1];
            Card current = cards[j];
            if (current.number < prev.number) {
                cards[j - 1] = current;
                cards[j] = prev;
            }
        }
    }

    // Handle ace conditional position
    int lastIdx = CARDS_PER_HAND - 1;
    bool isAceSpecialCase = cards[lastIdx].number == CARD_NUM_KING && cards[0].number == CARD_NUM_ACE;
    if (!isAceSpecialCase)
        return;

    Card ace = cards[0];

    for (int i = 1; i < CARDS_PER_HAND; i++) {
        Card prev = cards[i - 1];
        Card current = cards[i];
        cards[i - 1] = current;
        cards[i] = prev;
    }

    cards[lastIdx] = ace;
}

int getHandScore(const Hand hand) {
    return (
        hand.type
        + 5*hand.fourOfKindNumber
        + 4*hand.threeOfKindNumber
        + 3*hand.pairNumber
        + 2*hand.pairNumber2
        + 1*hand.highest
    );
}

void countCards(const Card cards[CARDS_PER_HAND], int counts[CARDS_PER_SUIT]) {
    for (int i = 0; i < CARDS_PER_HAND; i++)
        counts[cards[i].number - 1]++;
}

bool hasNOfAKind(const int n, const Card cards[CARDS_PER_HAND], int *matchedNumber, char *matchedSuit, int counts[CARDS_PER_SUIT]) {

    // Set each number occurrences count
    if (counts == NULL)
        counts = (int*)malloc(CARDS_PER_SUIT * sizeof(int));
    memset(counts, 0, CARDS_PER_SUIT * sizeof(int));
    countCards(cards, counts);

    // Check if we have the exact counting we're looking for
    if (matchedNumber == NULL)
        matchedNumber = (int*)malloc(sizeof(int));
    *matchedNumber = 0;
    
    if (matchedSuit == NULL)
        matchedSuit = (char*)malloc(sizeof(char));
    *matchedSuit = ' ';
    
    int bestCount = 0;
    for (int i = 0; i < CARDS_PER_HAND; i++) {

        if (!cards[i].number)
            continue;

        int thisCount = counts[cards[i].number - 1];
        if (thisCount > bestCount) {
            bestCount = thisCount;
            *matchedSuit = cards[i].suit;
            *matchedNumber = cards[i].number;
        }
    }

    return bestCount == n;
}

void removeCardFromHand(Card cards[CARDS_PER_HAND], const int numberToRemove) {
    for (int i = 0; i < CARDS_PER_HAND; i++) {
        if (cards[i].number == numberToRemove)
            cards[i].number = 0;
    }
}

Hand getEmptyHand(void) {
    return { HAND_HIGHER_CARD, ' ', 0, 0, 0, 0, 0, 0 };
}

Hand getHand(const Card handCards[CARDS_PER_HAND]) {

    // Make a sorted copy of provided cards
    Card cards[CARDS_PER_HAND];
    memcpy(cards, handCards, CARDS_PER_HAND * sizeof(Card));
    sortCards(cards);

    // Detect hand
    Hand hand = getEmptyHand();
    
    char suit;
    int pairNumber = 0;
    int fourOfKindNumber = 0;
    int threeOfKindNumber = 0;

    if (isRoyalStraightFlush(cards, &suit)) {
        hand.type = HAND_ROYAL_STRAIGHT_FLUSH;
        hand.suit = suit;

    } else if (isStraightFlush(cards, &suit)) {
        hand.type = HAND_STRAIGHT_FLUSH;
        hand.suit = suit;

    } if (isFourOfKind(cards, &fourOfKindNumber, &suit)) {
        hand.type =  HAND_4_KIND;
        hand.suit =  suit;
        hand.fourOfKindNumber =  fourOfKindNumber;

    } if (isFullHouse(cards, &threeOfKindNumber, &pairNumber)) {
        hand.type = HAND_FULL_HOUSE;
        hand.pairNumber =  pairNumber;
        hand.threeOfKindNumber =  threeOfKindNumber;
    }

    // if (isFlush(cards, &suit))
    //     return HAND_FLUSH;

    // if (isStraight(cards))
    //     return HAND_STRAIGHT;

    // if (isThreeOfKind(cards, &threeOfKindNumber))
    //     return HAND_3_KIND;

    // int pairNumber2 = 0;
    // if (isTwoPairs(cards, &pairNumber, &pairNumber2))
    //     return HAND_2_PAIRS;

    // if (isOnePair(cards, pairNumber))
    //     return HAND_PAIR;

    hand.score = getHandScore(hand);
    return hand;
}

/**
 * ------------------------------------------------
 * == HAND PARSERS ================================
 * ------------------------------------------------
 */

/** 05 cards of the same suit in row counting from 10 to Ace. */
bool isRoyalStraightFlush(const Card cards[CARDS_PER_HAND], char *suit) {
    int firstNumber = cards[0].number;
    return firstNumber == 10 && isSameSuitSequence(cards, suit);
}

/** 05 cards of the same suit in a row NOT counting from 10 to Ace (!= RSF). */
bool isStraightFlush(const Card cards[CARDS_PER_HAND], char *suit) {
    int firstNumber = cards[0].number;
    return firstNumber < 10 && isSameSuitSequence(cards, suit); // 1st number >= 10 would be RSF or nothing at all
}

/**
 * 04 equal cards.
 * - In case of a tie the higher number hand wins;
 * - If it remains tied the one with the higher fifth card wins;
 */
bool isFourOfKind(const Card cards[CARDS_PER_HAND], int *fourOfKindNumber, char *suit) {
    bool isHigherHand = isRoyalStraightFlush(cards, NULL) || isStraightFlush(cards, NULL);
    return !isHigherHand && hasNOfAKind(4, cards, fourOfKindNumber, suit, NULL);
}

/**
 * 01 pair + 03 of a kind.
 * - In case of a tie, the higher 03 of a kind wins;
 * - If it remains tied, the higher pair wins;
 */
bool isFullHouse(const Card cards[CARDS_PER_HAND], int *threeOfKindNumber, int *pairNumber) {

    *threeOfKindNumber = 0;
    *pairNumber = 0;

    bool isHigherHand = isRoyalStraightFlush(cards, NULL) || isStraightFlush(cards, NULL) || isFourOfKind(cards, NULL, NULL);
    if (isHigherHand)
        return false;

    // Check the 03 of a kind part
    int counts[CARDS_PER_SUIT] = { 0 };
    if (!hasNOfAKind(3, cards, threeOfKindNumber, NULL, counts))
        return false;

    // Check the pair part
    Card cardsCopy[CARDS_PER_HAND];
    memcpy(cardsCopy, cards, CARDS_PER_HAND * sizeof(Card));
    removeCardFromHand(cardsCopy, *threeOfKindNumber);

    // return hasNOfAKind(2, cardsCopy, pairNumber, NULL, NULL);
    bool dbg = hasNOfAKind(2, cardsCopy, pairNumber, NULL, NULL);
    return dbg;
}

/**
 * ------------------------------------------------
 * == INPUT PARSERS ===============================
 * ------------------------------------------------
 */

Play readPlay(ifstream &inputStream) {

    string aux;
    string line;
    getline(inputStream, line);
    stringstream lineStream(line);

    Play play;
    getline(lineStream, play.playerName, ' ');
    getline(lineStream, aux, ' ');
    play.bid = stoi(aux);

    for (int i = 0; i < CARDS_PER_HAND; i++) {
        getline(lineStream, aux, ' ');
        play.cards[i].suit = aux[aux.length() - 1];
        play.cards[i].number = stoi(aux.substr(0, aux.length() - 1));
    }
    
    return play;
}

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
    for (int i = 0; i < round.nPlays; i++) {
        Play play = readPlay(inputStream);
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