#include "../include/utils_debug.h"
#include "../include/utils_string.h"
#include "../include/quick_sort.h"

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

void parseInput(ifstream &inputStream, map<char, int> &lexicographyMap, map<string, int> &wordsMap);

int compareWords(const string str1, const string str2, const map<char, int> lexicography) {
    
    const ssize_t minLength = min(str1.size(), str2.size());
    const auto mapEnd = lexicography.end();
    
    for (int i = 0; i < minLength; i++) {
        char c1 = str1[i], c2 = str2[i];
        bool isMapTest = lexicography.find(c1) != mapEnd && lexicography.find(c2) != mapEnd;
        int delta = isMapTest ? lexicography.at(c1) - lexicography.at(c2) : c1 - c2;
        if (delta < 0) return -1;
        if (delta > 0) return 1;
    }
    
    return 0;
}


void testWordsComparison(const string s1, const string s2, const map<char, int> lexicographyMap) {
    int cmp = compareWords(s1, s2, lexicographyMap);
    if (cmp > 0)
        cout << s1 << " > " << s2 << endl;
    else if (cmp < 0)
        cout << s2 << " > " << s1 << endl;
    else
        cout << s1 << " == " << s2 << endl;
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
        // testSimpleSorters();
        
        // int cmp = compareWords(wordsMap.at('adidas'), wordsMap.at('de'), lexicographyMap);
        
        cout << endl;
        testWordsComparison("adidas", "de", lexicographyMap);
        testWordsComparison("adidas", "adidas", lexicographyMap);
        testWordsComparison("zebra", "zebra", lexicographyMap);
        testWordsComparison("adidas", "zebra", lexicographyMap);
        testWordsComparison("adidas", "zebra", lexicographyMap);
        testWordsComparison("zebra", "zebr0", lexicographyMap);
        

        

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

void testSimpleSorters() {
    
    // Test quick sort
    // int data[] = {8, 7, 6, 1, 0, 9, 2};
    // int data[] = {1, 2, 3, 4, 5};
    int n = 0;
    const int m = 3;
    const int minPartition = 5;
    
    int data[] = {7, 8, 10, 2, 26, 4, 19, 5, 3, 16, 11, 6, 13, 12};
    int dataAlt[] = {7, 8, 10, 2, 26, 4, 19, 5, 3, 16, 11, 6, 13, 12};
    n = sizeof(data) / sizeof(data[0]);
    
    // selectionSort(data, n);
    quickSort(data, 0, n - 1, m, NULL);
    cout << endl << "repeating..." << endl;
    quickSort(dataAlt, 0, n - 1, m, &minPartition);
    cout << endl << "------------" << endl;

    int data1[] = {19, 18, 16, 15, 13, 12, 21, 22, 25, 26, 16};
    int data1Alt[] = {19, 18, 16, 15, 13, 12, 21, 22, 25, 26, 16};
    n = sizeof(data1) / sizeof(data1[0]);
    
    // selectionSort(data1, n);
    quickSort(data1, 0, n - 1, m, NULL);
    cout << endl << "repeating..." << endl;
    quickSort(data1Alt, 0, n - 1, m, &minPartition);

    int data2[] = {1, 11, 4, 2, 13, 123, 63, 92};
    int data2Alt[] = {1, 11, 4, 2, 13, 123, 63, 92};
    n = sizeof(data2) / sizeof(data2[0]);
    
    // selectionSort(data2, n);
    quickSort(data2, 0, n - 1, m, NULL);
    cout << endl << "repeating..." << endl;
    quickSort(data2Alt, 0, n - 1, m, &minPartition);
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