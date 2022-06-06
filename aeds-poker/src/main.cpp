#include <iostream>
#include <string.h>

#include "../include/types.h"
#include "../include/game.h"
#include "../include/debug.h"

using namespace std;

/**
 * TODO: 2022-06-03 - ADD Hand detection tests
 * TODO: 2022-06-03 - ADD Tied hands comparison
 * TODO: 2022-06-03 - ADD Round sanity checks test
 */

int main(int argc, char const *argv[]) {
    
    cout << endl << "-- POKER system --" << endl << endl;

    ifstream readingStream;
    bool statusOK = true;

    try {

        // Read file
        if (argc != 2)
            throw invalid_argument("Invalid parameters number");

        const string filePath = argv[1];
        readingStream = ifstream(filePath);
        if (!readingStream.good())
            throw runtime_error("Failure as trying to read input file");

        // Build game
        Game game = readGame(readingStream);
        dbgPrintGame(game);

        // All good
        cout << endl << "FIM" << endl;

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

    if (readingStream.is_open())
        readingStream.close();

    // Fim da execucao
    return statusOK ? EXIT_SUCCESS : EXIT_FAILURE;
}