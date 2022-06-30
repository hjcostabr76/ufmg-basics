#include "../include/utils_debug.h"
#include "../include/utils_string.h"

#include <iostream>
// #include <stdlib.h>
#include <string.h>
// #include <memory>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

const string ID_SEQ_ORDER = "#ORDEM";
const string ID_SEQ_TXT = "#TEXTO";

const string MODE_NONE = "[__NO MODE__]";
const string MODE_TEXT = "[text mode]";
const string MODE_ORDER = "[order mode]";

char* getClearedInput(const char* input) {
	
	int i = 0;
	char* cleanInput = (char*)malloc(strlen(input) + 1);

	for (size_t j = 0; j < strlen(input); j++) {
        char c = input[j];
        if (strIsAlphaNumericChar(c))
            cleanInput[i++] = ::tolower(c);
	}
	
	cleanInput[i] = '\0';
	return cleanInput;
}

int main() {
    
    bool statusOK = true;

    ifstream inputStream;
    try {
        
        // const string filePath = argv[1];
        inputStream = ifstream("src/__test_1.i");
        if (!inputStream.good())
            throw runtime_error("Failure as trying to read input file");

        string line;
        string mode = MODE_NONE;
        map<char, int> lexicographyMap;

        int i = 0;
        while (getline(inputStream, line)) {
            i++;

            if (line == "") {
                printf("\n line [%d] is EMPTY!! ['%s']", i, line.c_str());
                continue;
            }

            printf("\n line [%d]: '%s'", i, line.c_str());

            char *lineWithNoDoubleSpace = strStripRepeatedChar(line.c_str(), ' ');
            const bool isOrder = strcmp(lineWithNoDoubleSpace, ID_SEQ_ORDER.c_str()) == 0;
            bool isText = false;
            
            if (isOrder) {
                mode = MODE_ORDER;

            } else if (strcmp(lineWithNoDoubleSpace, ID_SEQ_TXT.c_str()) == 0) {
                isText = true;
                mode = MODE_TEXT;
            }

            printf("\n\t > '%s'", mode.c_str());
            if (isOrder || isText)
                continue;

            char *lineCleared = getClearedInput(lineWithNoDoubleSpace);
            printf("\n\t > '%s'", lineCleared);

            if (mode != MODE_ORDER)
                continue;

            int count = 0;
            const int nLetters = 26;
            char **letters = strSplit(lineCleared, " ", nLetters, 1, &count);

            printf("\n\nHere comes the alphabet:\n");
            for (int j = 0; j < count; j++) {
                printf("'%s' (%d); ", letters[j], j);
                lexicographyMap.insert(pair<char, int>(letters[j][0], j));
            }
        }

        printf("\n");
        printf("\nTesting map for '%c': '%d'\n", 'a', lexicographyMap.at('a'));
        printf("\nTesting map for '%c': '%d'\n", 'x', lexicographyMap.at('x'));
        printf("\nTesting map for '%c': '%d'\n", 'p', lexicographyMap.at('p'));

        cout << endl;
        cout << "-- The End --" << endl;

    } catch (exception &error) {
        statusOK = false;
        cout << "-- Ops! Something wrong isn't right... --" << endl;
        if (DEBUG_ENABLE)
            cout << "What went wrong: '" << error.what() << "'" << endl;
        cout << endl;
    }

    if (inputStream.is_open())
        inputStream.close();

    return statusOK ? EXIT_SUCCESS : EXIT_FAILURE;
}