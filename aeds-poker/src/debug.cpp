#include <iostream>
#include "../include/debug.h"

using namespace std;

string dbgGetCardsPrint(const Card* cards, const int nCards) {
    
    string print = "";
    for (int i = 0; i < nCards; i++) {
        
        string suit;
        suit += cards[i].suit;
        print += "\t[card] suit: '" + suit + "'; number: '" + to_string(cards[i].number) + "';";
        
        if (nCards > 1)
            print += "\n";
    }
    
    return print;
}

string dbgGetPlayPrint(const Play play) {
    string print = "[play] bid: '" + to_string(play.bid) + "'; playerName: '" + play.playerName + "'; ";
    print += "hand: '" + HAND_NAMES[play.hand.type] + " (" + to_string(play.hand.score) + ");' cards:";
    for (int i = 0; i < CARDS_PER_HAND; i++)
        print += "\n\t\t" + dbgGetCardsPrint(&play.hand.cards[i], 1);
    return print;    
}

string dbgGetRoundPrint(const Round round) {
    
    string print = "[round] blind: '" + to_string(round.blind) + "'; nPlays: '" + to_string(round.nPlays) + "'; pot: '" + to_string(round.pot) + "'; ";
    
    if (round.nWinners) {
        print += "nWinners: '" + to_string(round.nWinners) + "'; winners: ";
        for (int i = 0; i < round.nWinners; i++)
            print += "'" + round.winners[i] + "', ";
    }

    print += "plays:";
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

string dbgGetPlayerPrint(const Player player) {
    return "[player] name: '" + player.name + "'; money: '" + to_string(player.money) + "';";
}

void dbgPrintPlayer(const Player player) {
    if (DEBUG_ENABLE) {
        cout << "---------- DBG: Player --------" << endl;
        cout << dbgGetPlayerPrint(player);
        cout << endl;
        cout << "---------- || --- || ----------" << endl;
    }
}

void dbgPrintCards(const Card* cards, const int nCards) {
    if (DEBUG_ENABLE) {
        cout << "---------- DBG: Cards ---------" << endl;
        cout << dbgGetCardsPrint(cards, nCards);
        cout << endl;
        cout << "---------- || --- || ----------" << endl;
    }
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
        cout << "[log] " << msg << endl;
}
