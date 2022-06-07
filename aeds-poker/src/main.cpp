#include <iostream>
#include <string.h>
#include <fstream>

#include "../include/types.h"
#include "../include/game.h"
#include "../include/debug.h"

using namespace std;

const string OUT_FILE = "saida.txt";

int main(int argc, char const *argv[]) {
    
    cout << endl << "-- POKER system --" << endl << endl;

    ifstream inputStream;
    ofstream outputStream;
    bool statusOK = true;

    try {

        // Read file
        if (argc != 2)
            throw invalid_argument("Invalid parameters number");

        const string filePath = argv[1];
        inputStream = ifstream(filePath);
        if (!inputStream.good())
            throw runtime_error("Failure as trying to read input file");

        // Parse game
        Game game = readGame(inputStream);
        consolidateRounds(game);
        sortPlayers(game.players, game.nPlayers);

        // Build output
        outputStream = ofstream(OUT_FILE);
        if (!outputStream.good())
            throw runtime_error("Failure as trying to write output file");

        writeResult(game, outputStream);

        // All good
        cout << endl << "-- The End --" << endl;

    } catch (invalid_argument &error) {
        cout << "Invalid command!" << endl;
        cout << "Input format: ./poker [input-file-path]" << endl << endl;
    
    } catch (exception &error) {
        statusOK = false;
        cout << "-- Ops! Something wrong isn't right... --" << endl;
        if (DEBUG_ENABLE)
            cout << "What went wrong: '" << error.what() << "'" << endl;
        cout << endl;
    }

    if (inputStream.is_open())
        inputStream.close();
    if (outputStream.is_open())
        outputStream.close();

    // Fim da execucao
    return statusOK ? EXIT_SUCCESS : EXIT_FAILURE;
}