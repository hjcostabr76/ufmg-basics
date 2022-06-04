#pragma once

#include <stdlib.h>

using namespace std;

/**
 * =================================================
 * -- CONSTANT -------------------------------------
 * =================================================
 */

#define DEBUG_ENABLE true

#define HAND_COUNT 10

#define CARDS_PER_HAND 5
#define CARDS_PER_SUIT 13
#define CARD_NUM_ACE 1
#define CARD_NUM_KING 13

#define SUITS_COUNT 4
#define SUIT_CLUBS 'P'
#define SUIT_SPADES 'E'
#define SUIT_HEARTS 'C'
#define SUIT_DIAMONDS 'O'

const char SUITS_LIST[SUITS_COUNT] = { SUIT_CLUBS, SUIT_SPADES, SUIT_HEARTS, SUIT_DIAMONDS };

const string HAND_NAMES[HAND_COUNT] = {
    "Higher card",
    "Pair",
    "Two Pairs",
    "Three of a kind...",
    "Straight...",
    "Flush...",
    "Full House...",
    "Four of a kind...",
    "Straight Flush...",
    "Royal Straight Flush...",
};

/**
 * =================================================
 * -- ABSTRACT -------------------------------------
 * =================================================
 */

typedef enum {
    HAND_HIGHER_CARD,
    HAND_PAIR,
    HAND_2_PAIRS,
    HAND_3_KIND,
    HAND_STRAIGHT,
    HAND_FLUSH,
    HAND_FULL_HOUSE,
    HAND_4_KIND,
    HAND_STRAIGHT_FLUSH,
    HAND_ROYAL_STRAIGHT_FLUSH
} HandEnum;

typedef struct {
    char suit;
    int number;
} Card;

typedef struct {
    int bid;
    string playerName;
    Card cards[CARDS_PER_HAND];
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

typedef struct {
    HandEnum type;
    char suit;
    int fourOfKindNumber;
    int threeOfKindNumber;
    int pairNumber;
    int pairNumber2;
    int highest;
    int score;
} Hand;
