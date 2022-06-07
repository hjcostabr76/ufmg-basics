#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

#include "../include/types.h"
#include "../include/game.h"
#include "../include/debug.h"

using namespace std;

#define N_PLAYERS 12
const int CASH_INIT = 2000;

const string FILE_INPUT = "./test/tst_input_game.txt";

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
        
        // Build game
        int nPlayers = 0;
        Game game = readGame(readingStream);
        
        Player players[MAX_PLAYERS];
        readGamePlayers(game, players, &nPlayers);

        isTestOK = nPlayers == N_PLAYERS;
        for (int i = 0; i < nPlayers; i++) {
            isTestOK = isTestOK && (players[i].money == CASH_INIT);
            // dbgPrintPlayer(players[i]);
        }

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