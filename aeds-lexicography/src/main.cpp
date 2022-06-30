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
        map<string, int> wordsMap;

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

            int count = 0;
            if (mode == MODE_ORDER) {
                const int nLetters = 26;
                char **letters = strSplit(lineCleared, " ", nLetters, 1, &count);
                for (int j = 0; j < count; j++) {
                    const char c = letters[j][0];
                    lexicographyMap[c] = j;
                }
                continue;
            }

            const size_t maxLength = strlen(lineCleared);;
            char **words = strSplit(lineCleared, " ", maxLength, 1, &count);
            for (int j = 0; j < count; j++)
                wordsMap[words[j]]++;
        }

        printf("\n\nHere comes our alphabet:\n");
        map<char, int>::iterator itrAlpha;
        for (itrAlpha = lexicographyMap.begin(); itrAlpha != lexicographyMap.end(); ++itrAlpha) {
            printf("'%c' (%d); ", itrAlpha->first, itrAlpha->second);
        }

        printf("\n\nHere comes our words counted:\n");
        map<string, int>::iterator itrWords;
        for (itrWords = wordsMap.begin(); itrWords != wordsMap.end(); ++itrWords) {
            printf("\n\t'%s': '%d'", itrWords->first.c_str(), itrWords->second);
        }
        
        printf("\n");
        printf("\nTesting map for '%c': '%d'", 'a', lexicographyMap['a']);
        printf("\nTesting map for '%c': '%d'", 'x', lexicographyMap.at('x'));
        printf("\nTesting map for '%c': '%d'", 'p', lexicographyMap.at('p'));

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