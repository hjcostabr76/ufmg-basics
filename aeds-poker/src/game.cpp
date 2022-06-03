#include <stdlib.h>
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
            (prevNumber != 13 && currentNumber == (prevNumber + 1))
            || (prevNumber == 13 && currentNumber == 1) // Considers the ace as the last card
        );
        
        if (!isValidNumber)
            return false;
    }

    return true;
}

bool isSameSuitSequence(const Card cards[CARDS_PER_HAND], char &suit) {

    if (!isSequence(cards))
        return false;

    suit = cards[0].suit;
    for (int i = 1; i < CARDS_PER_HAND; i++) {
        if (cards[i].suit != suit)
            return false;
    }

    return true;
}

int getHandScore(const Hand hand) {
    return (
        hand.type
        + 5*hand.fourOfKindNumber
        + 4*hand.threeOfKindNumber
        + 3*hand.pairNumber1
        + 2*hand.pairNumber2
        + 1*hand.highest
    );
}

Hand getEmptyHand(void) {
    return { HAND_HIGHER_CARD, ' ', 0, 0, 0, 0, 0, 0 };
}

Hand getHand(const Card cards[CARDS_PER_HAND]) {

    Hand hand = getEmptyHand();

    char suit;
    if (isRoyalStraightFlush(cards, suit)) {
        hand.type = HAND_ROYAL_STRAIGHT_FLUSH;
        hand.suit = suit;
    }

    // if (isStraightFlush(cards))
    //     return HAND_STRAIGHT_FLUSH;

    // int fourOfKindNumber = 0;
    // if (isFourOfKind(cards, &fourOfKindNumber))
    //     return HAND_4_KIND;

    // int threeOfKindNumber = 0;
    // int pairNumber1 = 0;
    // if (isFullHouse(cards, &threeOfKindNumber, &pairNumber1))
    //     return HAND_FULL_HOUSE;

    // if (isFlush(cards, &suit))
    //     return HAND_FLUSH;

    // if (isStraight(cards))
    //     return HAND_STRAIGHT;

    // if (isThreeOfKind(cards, &threeOfKindNumber))
    //     return HAND_3_KIND;

    // int pairNumber2 = 0;
    // if (isTwoPairs(cards, &pairNumber1, &pairNumber2))
    //     return HAND_2_PAIRS;

    // if (isOnePair(cards, pairNumber1))
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
bool isRoyalStraightFlush(const Card cards[CARDS_PER_HAND], char &suit) {
    int firstNumber = cards[0].number;
    return firstNumber == 10 && isSameSuitSequence(cards, suit);
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