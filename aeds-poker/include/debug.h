#pragma once

#include <stdlib.h>
#include "types.h"

using namespace std;

/**
 * =================================================
 * -- HEADERS --------------------------------------
 * =================================================
 */

string dbgGetCardsPrint(const Card* cards, const int nCards);
string dbgGetPlayPrint(const Play play);
string dbgGetRoundPrint(const Round round);
string dbgGetGamePrint(const Game game);
string dbgGetPlayerPrint(const Player player);

void dbgPrintCards(const Card* cards, const int nCards);
void dbgPrintGame(const Game game);
void dbgPrintRound(const Round round);
void dbgPrintPLay(const Play play);
void dbgStep(string msg);
void dbgPrintPlayer(const Player player);