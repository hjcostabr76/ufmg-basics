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

void printLexicography(map<char, int> lexicographyMap) {
    
    if (!DEBUG_ENABLE)
        return;
    
    printf("\n\nHere comes our alphabet:");
    map<char, int>::iterator itrAlpha;
    for (itrAlpha = lexicographyMap.begin(); itrAlpha != lexicographyMap.end(); ++itrAlpha) {
        printf("\n\t'%c': %d; ", itrAlpha->first, itrAlpha->second);
    }
}

void printWords(map<string, int> wordsMap) {
    
    if (!DEBUG_ENABLE)
        return;
    
    printf("\n\nHere comes our words counted:\n");
    map<string, int>::iterator itrWords;
    for (itrWords = wordsMap.begin(); itrWords != wordsMap.end(); ++itrWords) {
        printf("\n\t'%s': '%d'", itrWords->first.c_str(), itrWords->second);
    }
}

void parseInput(ifstream &inputStream, map<char, int> &lexicographyMap, map<string, int> &wordsMap);

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

/**
 * TODO: 2022-06-30 - Get file path from cli
 */
int main() {
    
    bool statusOK = true;

    ifstream inputStream;
    try {
        
        // const string filePath = argv[1];
        inputStream = ifstream("src/__test_1.i");
        if (!inputStream.good())
            throw runtime_error("Failure as trying to read input file");

        // Build maps
        map<char, int> lexicographyMap;
        map<string, int> wordsMap;
        parseInput(inputStream, lexicographyMap, wordsMap);
        
        printLexicography(lexicographyMap);
        printWords(wordsMap);

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

void parseInput(ifstream &inputStream, map<char, int> &lexicographyMap, map<string, int> &wordsMap) {
    
    string line;
    string mode = MODE_NONE;

    bool isText = false;
    bool isOrder = false;

    while (getline(inputStream, line)) {
        if (line == "")
            continue;

        // Parse input mode
        char *lineWithNoDoubleSpace = strStripRepeatedChar(line.c_str(), ' ');
        
        isText = false;
        isOrder = strcmp(lineWithNoDoubleSpace, ID_SEQ_ORDER.c_str()) == 0;
        if (isOrder)
            mode = MODE_ORDER;
        else if (strcmp(lineWithNoDoubleSpace, ID_SEQ_TXT.c_str()) == 0) {
            isText = true;
            mode = MODE_TEXT;
        }

        if (isOrder || isText)
            continue;

        if (mode == MODE_NONE)
            throw runtime_error("File reading mode undefined");

        // Parse letters order
        char *lineCleared = getClearedInput(lineWithNoDoubleSpace);
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

        // Compute words occurrences
        const size_t maxLength = strlen(lineCleared);;
        char **words = strSplit(lineCleared, " ", maxLength, 1, &count);
        for (int j = 0; j < count; j++)
            wordsMap[words[j]]++;
    }
}