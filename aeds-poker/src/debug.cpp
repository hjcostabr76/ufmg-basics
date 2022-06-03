#include <iostream>
#include "../include/debug.h"

using namespace std;

string dbgGetCardsPrint(const Card* cards, const int nCards) {
    
    string print = "";
    for (int i = 0; i < nCards; i++) {
        
        string suit;
        suit += cards[i].suit;
        print += "\t[card] suit: '" + suit + "'; number: '" + to_string(cards[i].number) + "';";
        
        if (i > 0)
            print += "\n";
    }
    
    return print;
}

string dbgGetPlayPrint(const Play play) {
    string print = "[play] bid: '" + to_string(play.bid) + "'; playerName: '" + play.playerName + "'; cards:";
    for (int i = 0; i < CARDS_PER_HAND; i++)
        print += "\n\t\t" + dbgGetCardsPrint(&play.cards[i], 1);
    return print;    
}

string dbgGetRoundPrint(const Round round) {
    string print = "[round] blind: '" + to_string(round.blind) + "'; nPlays: '" + to_string(round.nPlays) + "'; plays:";
    for (int i = 0; i < round.nPlays; i++)
        print += "\n\t\t" + dbgGetPlayPrint(round.plays[i]);
    return print;
}


string dbgGetGamePrint(const Game game) {
    string print = "[game] nRounds: '" + to_string(game.nRounds) + "'; initialAmount: '" + to_string(game.initialAmount) + "'; rounds:";
    for (int i = 0; i < game.nRounds; i++)
        print += "\n\t" + dbgGetRoundPrint(game.rounds[i]);
    return print;
}

void dbgPrintGame(const Game game) {
    if (DEBUG_ENABLE) {
        cout << "---------- DBG: Game ----------" << endl;
        cout << dbgGetGamePrint(game);
        cout << endl;
        cout << "---------- || --- || ----------" << endl;
    }
}

void dbgPrintRound(const Round round) {
    if (DEBUG_ENABLE) {
        cout << "---------- DBG: Round ---------" << endl;
        cout << dbgGetRoundPrint(round);
        cout << endl;
        cout << "---------- || --- || ----------" << endl;
    }
}

void dbgPrintPLay(const Play play) {
    if (DEBUG_ENABLE) {
        cout << "---------- DBG: Play ----------" << endl;
        cout << dbgGetPlayPrint(play);
        cout << endl;
        cout << "---------- || --- || ----------" << endl;
    }
}

void dbgStep(string msg) {
    if (DEBUG_ENABLE)
        cout << msg << endl;
}
