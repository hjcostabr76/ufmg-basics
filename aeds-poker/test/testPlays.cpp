#include <iostream>
#include <fstream>
#include <sstream>

#include "../include/types.h"
#include "../include/game.h"

using namespace std;

#define N_LINES 3
const string FILE_INPUT = "./test/tst_input_play.txt";

int main(void) {
    
    cout << endl << "-- <<< TEST >>> <<< TEST >>> <<< TEST >>> --" << endl << endl;

    ifstream readingStream;
    bool statusOK = true;

    try {

        readingStream = ifstream(FILE_INPUT);
        if (!readingStream.good())
            throw runtime_error("Failure as trying to read input file");

        // TODO...
        for (int i = 0; i < N_LINES; i++) {
            Play play = readPlay(readingStream);
            cout << "One play read..." << endl;
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