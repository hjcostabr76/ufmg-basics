#pragma once

#include <stdlib.h>
#include <fstream>

#include "types.h"

using namespace std;

/** -- Hand parsers --------------- */

bool isRoyalStraightFlush(const Card cards[CARDS_PER_HAND], char *suit);
bool isStraightFlush(const Card cards[CARDS_PER_HAND], char *suit);
bool isFourOfKind(const Card cards[CARDS_PER_HAND], int *fourOfKindNumber);
bool isFullHouse(const Card cards[CARDS_PER_HAND], int *threeOfKindNumber, int *pairNumber);
bool isFlush(const Card cards[CARDS_PER_HAND], char *suit);
bool isStraight(const Card cards[CARDS_PER_HAND]);
bool isThreeOfKind(const Card cards[CARDS_PER_HAND], int *threeOfKindNumber);
bool isTwoPairs(const Card cards[CARDS_PER_HAND], int *pairNumber, int *pairNumber2);
bool isOnePair(const Card cards[CARDS_PER_HAND], int *pairCard);

/** -- Game actions  -------------- */

Hand getEmptyHand(void);
void detectHand(Hand &hand);
void parseRound(Round &round, Player* players, const int nPlayers);

/** -- Input parsers -------------- */

Play readPlay(ifstream &inputStream);
Round readRound(ifstream &inputStream);
Game readGame(ifstream &inputStream);
void readGamePlayers(const Game game, Player players[MAX_PLAYERS], int *nPlayers);