#pragma once

#include <stdlib.h>
#include <fstream>

#include "types.h"

using namespace std;

/** -- Hand parsers --------------- */

bool isRoyalStraightFlush(const Card cards[CARDS_PER_HAND], char &suit);
// bool isStraightFlush(const Card cards[CARDS_PER_HAND]);
// bool isFourOfKind(const Card cards[CARDS_PER_HAND], int *fourOfKindNumber);
// bool isFullHouse(const Card cards[CARDS_PER_HAND], int *threeOfKindNumber, int *pairNumber);
// bool isFlush(const Card cards[CARDS_PER_HAND], char *suit);
// bool isStraight(const Card cards[CARDS_PER_HAND]);
// bool isThreeOfKind(const Card cards[CARDS_PER_HAND], int *threeOfKindNumber);
// bool isTwoPairs(const Card cards[CARDS_PER_HAND], int *pairNumber1, int *pairNumber2);
// bool isOnePair(const Card cards[CARDS_PER_HAND], int &pairCard);

Hand getEmptyHand(void);
Hand getHand(const Card cards[CARDS_PER_HAND]);

/** -- Input parsers -------------- */

Play readPlay(ifstream &inputStream);
Round readRound(ifstream &inputStream);
Game readGame(ifstream &inputStream);