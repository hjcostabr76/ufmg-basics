#pragma once

#include <stdlib.h>
#include <fstream>

using namespace std;

/**
 * =================================================
 * -- CONSTANT -------------------------------------
 * =================================================
 */

#define DEBUG_ENABLE true

#define CARDS_COUNT 5
#define CARD_SUIT_SPADES 'E'
#define CARD_SUIT_HEARTS 'C'
#define CARD_SUIT_CLUBS 'P'
#define CARD_SUIT_DIAMONDS 'O'

/**
 * =================================================
 * -- ABSTRACT -------------------------------------
 * =================================================
 */

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


/**
 * =================================================
 * -- HEADERS --------------------------------------
 * =================================================
 */

Play readPlay(ifstream &inputStream);
Round readRound(ifstream &inputStream);
Game readGame(ifstream &inputStream);