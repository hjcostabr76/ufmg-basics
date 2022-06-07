#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

#include "../include/types.h"
#include "../include/game.h"
#include "../include/debug.h"

using namespace std;

#define N_ROUNDS 1
#define N_PLAYERS 13

const int BID = 50;
const int POT = N_PLAYERS*BID + 100*(1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 + 11 + 12);
const int CASH_INIT = 2000;
const string FILE_INPUT = "./test/tst_input_round.txt";

Player getPlayerForTesting(const int n) {
    Player p;
    p.money = CASH_INIT;
    p.name = "Player ";
    if (n < 9)
        p.name += "0";
    p.name += to_string(n + 1);
    return p;
}

bool testRoundOK(Round round) {

    Player players[N_PLAYERS];
    for (int i = 0; i < N_PLAYERS; i++)
        players[i] = getPlayerForTesting(i);
    
    parseRound(round, players, N_PLAYERS);
    // dbgPrintRound(round);
    
    bool isTestOK = round.nWinners == 3 && round.winningHand == HAND_ROYAL_STRAIGHT_FLUSH && round.pot == POT;

    for (int i = 0; i < N_PLAYERS; i++) {
        
        int playerNumber = i + 1;
        int expectedMoney = CASH_INIT - BID;
        
        bool havePlayed = playerNumber != N_PLAYERS;
        if (havePlayed)
            expectedMoney -= playerNumber*100;
        
        bool isWinner = playerNumber == 10 || playerNumber == 11 || playerNumber == 12;
        if (isWinner)
            expectedMoney += POT / 3;

        bool isOK = players[i].money == expectedMoney;
        isTestOK = isTestOK && isOK;

        cout << endl << "[test]" << players[i].name << (isOK ? ": OK..." : ": Error!") << " [expected: " << to_string(expectedMoney) << "]" << endl;
        // dbgPrintPlayer(players[i]);
    }

    return isTestOK;
}

bool testSanitizationError(Round round) {
    
    Player players[N_PLAYERS];
    for (int i = 0; i < N_PLAYERS; i++)
        players[i] = getPlayerForTesting(i);   

    bool isTestOK = false;
    players[11].money = 0;

    try {
        parseRound(round, players, N_PLAYERS);

    } catch (range_error &error) {
        isTestOK = true;
        cout << "[test] Error (what we expect): '" << error.what() << "'" << endl;
    }

    return isTestOK;
}

int main(void) {
    
    cout << endl
        << "--------------------------------------------" << endl
        << "-- <<< TEST >>> <<< TEST >>> <<< TEST >>> --" << endl
        << endl;

    ifstream readingStream;
    
    bool statusOK = true;
    bool isTestOK = true;

    try {

        // Read input data
        readingStream = ifstream(FILE_INPUT);
        if (!readingStream.good())
            throw runtime_error("Failure as trying to read input file");
        
        Round roundRaw = readRound(readingStream);

        // Test valid round input
        Round round1;
        memcpy(&round1, &roundRaw, sizeof(Round));
        isTestOK = isTestOK && testRoundOK(round1);

        Round round2;
        memcpy(&round2, &roundRaw, sizeof(Round));
        isTestOK = isTestOK && testSanitizationError(round2);
        

    } catch (exception &error) {
        statusOK = false;
        cout << "-- Ops! Something wrong isn't right... --" << endl;
        cout << "What went wrong: '" << error.what() << "'" << endl;
        cout << endl;
    }

    if (readingStream.is_open())
        readingStream.close();

    // Finish testing...
    cout << endl << "--------------------------------------------" << endl;
    if (isTestOK)
        cout << "-- <<< TEST OK >>> TEST OK <<< TEST OK >>> --" << endl;
    else
        cout << "-- <<< TESTS FAILED >>> <<< TESTS FAILED >>> --" << endl;
    cout << endl << "--------------------------------------------" << endl;

    return statusOK ? EXIT_SUCCESS : EXIT_FAILURE;
}