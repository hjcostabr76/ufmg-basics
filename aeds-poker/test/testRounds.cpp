#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

#include "../include/types.h"
#include "../include/game.h"
#include "../include/debug.h"

using namespace std;

#define N_ROUNDS 1
#define N_PLAYERS 11

const int BID = 50;
const int POT = N_PLAYERS*BID + 100*(1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10);
const int CASH_INIT = 2000;
const string FILE_INPUT = "./test/tst_input_round.txt";

// E2 P9 O4 C5 E6 // HAND_HIGHER_CARD
// E2 P2 O4 C5 E6 // HAND_PAIR
// E2 P2 O4 C4 E6 // HAND_2_PAIRS
// E2 P2 O2 C4 E6 // HAND_3_KIND
// E2 P3 O4 C5 E6 // HAND_STRAIGHT
// E2 E3 E9 E7 E5 // HAND_FLUSH
// E2 P2 O2 C7 E7 // HAND_FULL_HOUSE
// E2 P2 O2 C2 E7 // HAND_4_KIND
// C1 C2 C3 C4 C5 // HAND_STRAIGHT_FLUSH
// C10 C11 C12 C13 C1 // HAND_ROYAL_STRAIGHT_FLUSH

Player getPlayerForTesting(const int n) {
    Player p;
    p.money = CASH_INIT;
    p.name = "Player ";
    if (n < 9)
        p.name += "0";
    p.name += to_string(n + 1);
    return p;
}

int main(void) {
    
    cout << endl << "-- <<< TEST >>> <<< TEST >>> <<< TEST >>> --" << endl << endl;

    ifstream readingStream;
    bool statusOK = true;

    // Set players list
    Player initialPlayers[N_PLAYERS];
    for (int i = 0; i < N_PLAYERS; i++)
        initialPlayers[i] = getPlayerForTesting(i);

    Player players[N_PLAYERS];
    memcpy(players, initialPlayers, N_PLAYERS * sizeof(Player));

    // cout << "-- <<< Players (initial) >>> --" << endl << endl;
    // for (int i = 0; i < N_PLAYERS; i++)
    //     dbgPrintPlayer(players[i]);

    try {

        // Read input data
        readingStream = ifstream(FILE_INPUT);
        if (!readingStream.good())
            throw runtime_error("Failure as trying to read input file");

        // Parse round
        Round round = readRound(readingStream);
        parseRound(round, players, N_PLAYERS);
        // dbgPrintRound(round);

        for (int i = 0; i < N_PLAYERS; i++) {
            
            int playerNumber = i + 1;
            int expectedMoney = CASH_INIT - BID;
            
            bool havePlayed = playerNumber != N_PLAYERS;
            if (havePlayed)
                expectedMoney -= playerNumber*100;
            
            bool isWinner = playerNumber == 10;
            if (isWinner)
                expectedMoney += POT;

            bool isOK = players[i].money == expectedMoney;

            cout << endl << players[i].name << (isOK ? ": OK..." : ": Error!") << " [expected: " << to_string(expectedMoney) << "]" << endl;
            // dbgPrintPlayer(players[i]);
        }

        cout << endl << "-- THE END --" << endl;

    } catch (exception &error) {
        statusOK = false;
        cout << "-- Ops! Something wrong isn't right... --" << endl;
        cout << "What went wrong: '" << error.what() << "'" << endl;
        cout << endl;
    }

    if (readingStream.is_open())
        readingStream.close();

    return statusOK ? EXIT_SUCCESS : EXIT_FAILURE;
}