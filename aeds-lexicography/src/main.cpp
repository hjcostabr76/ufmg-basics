#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <map>
#include <regex.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>

#define ASCII_NUM_FIRST 48
#define ASCII_NUM_LAST 57

#define ASCII_CHAR_LC_FIRST 97
#define ASCII_CHAR_LC_LAST 122
#define ASCII_CHAR_UC_FIRST 65
#define ASCII_CHAR_UC_LAST 90

#define ASCII_CHAR_UC_SPECIAL_A_FIRST 192
#define ASCII_CHAR_UC_SPECIAL_A_LAST 198
#define ASCII_CHAR_UC_SPECIAL_E_FIRST 200
#define ASCII_CHAR_UC_SPECIAL_E_LAST 203
#define ASCII_CHAR_UC_SPECIAL_I_FIRST 204
#define ASCII_CHAR_UC_SPECIAL_I_LAST 207
#define ASCII_CHAR_UC_SPECIAL_O_FIRST 210
#define ASCII_CHAR_UC_SPECIAL_O_LAST 214
#define ASCII_CHAR_UC_SPECIAL_U_FIRST 217
#define ASCII_CHAR_UC_SPECIAL_U_LAST 220

#define ASCII_CHAR_LC_SPECIAL_A_FIRST 224
#define ASCII_CHAR_LC_SPECIAL_A_LAST 230
#define ASCII_CHAR_LC_SPECIAL_E_FIRST 232
#define ASCII_CHAR_LC_SPECIAL_E_LAST 235
#define ASCII_CHAR_LC_SPECIAL_I_FIRST 236
#define ASCII_CHAR_LC_SPECIAL_I_LAST 239
#define ASCII_CHAR_LC_SPECIAL_O_FIRST 242
#define ASCII_CHAR_LC_SPECIAL_O_LAST 246
#define ASCII_CHAR_LC_SPECIAL_U_FIRST 249
#define ASCII_CHAR_LC_SPECIAL_U_LAST 252

#define DEBUG_ENABLE true

using namespace std;

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

void comLogErrorAndDie(char *msg) {

	if (DEBUG_ENABLE) {
		if (errno) {
			char *descSuffix = (char *)("\n\tWhat: ");
			char errMsg[strlen(msg) + strlen(descSuffix)];
			strcpy(errMsg, msg);
			strcat(errMsg, descSuffix);
			perror(errMsg);
		} else
			fprintf(stderr, "\n%s\n", msg);
	}

	exit(EXIT_FAILURE);
}

void comDbgStep(const char *text) {
	if (DEBUG_ENABLE)
		printf("[log] %s\n", text);
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

bool strIsAlphaNumericChar(const char c) {
	return (
		(c >= ASCII_NUM_FIRST && c <= ASCII_NUM_LAST)
		|| (c >= ASCII_CHAR_LC_FIRST && c <= ASCII_CHAR_LC_LAST)
		|| (c >= ASCII_CHAR_UC_FIRST && c <= ASCII_CHAR_UC_LAST)
		|| c == ' '
	);
}

char** strSplit(const char* source, const char *delimiter, const int maxTokens, int *tokensCount) {
    
	const bool isCounterNull = tokensCount == NULL;
	if (isCounterNull)
    	tokensCount = (int *)malloc(sizeof(int));
    *tokensCount = 0;
    
	char** tokens = (char **)malloc(maxTokens * sizeof(char*));
	char *aux = (char *)malloc(strlen(source) + 1);
    memset(aux, 0, strlen(source) + 1);
	strcpy(aux, source);
	
	char *token = strtok(aux, delimiter);
	if (token == NULL)
        return tokens;

    while (token != NULL && *tokensCount < maxTokens) {
		const size_t allocSize = strlen(token) + 1;
        tokens[*tokensCount] = (char *)malloc(allocSize);
        tokens[*tokensCount][0] = '\0';
        strcpy(tokens[*tokensCount], token);
        *tokensCount = *tokensCount + 1;
        token = strtok(NULL, delimiter);
    }

    free(aux);
	if (isCounterNull)
		free(tokensCount);
    return tokens;
}

void strRemoveAccents(char *str) {
    /**
     * 
     * == How each accented char lengths: ==
	 * 
     * á/2;  ã/2;  â/2;
     * é/2;  è/2;  ê/2;  ẽ/3;
     * í/2;  ì/2;
     * ó/2;  ò/2;  ô/2;  õ/2;
     * ú/2;  ù/2;  û/2;
     * ç/2;
     * 
     * Á/2;  À/2;  Ã/2;  Â/2;
     * É/2;  È/2;  Ê/2;  Ẽ/3;
     * Í/2;  Ì/2;
     * Ó/2;  Ò/2;  Ô/2;  Õ/2;
     * Ú/2;  Ù/2;  Û/2;
     * Ç/2;
     * 
     */
    
    char lowerRaw[] = "áàãâéèêẽíìóòôõúùûç";
    char upperRaw[] = "ÁÀÃÂÉÈÊẼÍÌÓÒÔÕÚÙÛÇ";

    char lowerFixed[] = "aaaaaaaaeeeeeeeeeiiiioooooooouuuuuucc";
    char upperFixed[] = "AAAAAAAAEEEEEEEEEIIIIOOOOOOOOUUUUUUCC";

    for (int i = 0; str[i] != '\0'; i++ ) {
        
        int j = 0;
        const char c = str[i];
        bool isFound = false;

        // Try for lowercase chars
        for (j = 0; lowerRaw[j] != '\0'; j++ ) {
            if (c == lowerRaw[j]) {
                str[i] = lowerFixed[j];
                isFound = true;
                break;
            }
        }

        // Try for uppercase chars
		if (isFound)
			continue;
			
		for (j = 0; upperRaw[j] != '\0'; j++ ) {
			if (c == upperRaw[j]) {
				str[i] = upperFixed[j];
				isFound = true;
				break;
			}
		}
    }
}

char* strStripRepeatedChar(const char* input, const char target) {
	
	int i = 0;
	char* cleanInput = (char*)malloc(strlen(input) + 1);

    bool isFound = false;
	for (size_t j = 0; j < strlen(input); j++) {
		
        char c = input[j];
        if (c == target) {
            if (isFound) {
                isFound = false;
                continue;
            }
            isFound = true;
        } else
            isFound = false;

        cleanInput[i++] = c;
	}
	
	cleanInput[i] = '\0';
	return cleanInput;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

const string ID_SEQ_ORDER = "#ORDEM";
const string ID_SEQ_TXT = "#TEXTO";
const string ID_SEQ_END = "#FIM";

const string MODE_NONE = "[__NO MODE__]";
const string MODE_TEXT = "[text mode]";
const string MODE_ORDER = "[order mode]";

int m;
int nWords = 0;
int minPartition;
char **words;

map<char, int> lexicography;
map<string, int> occurrenceMap;

//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq

void printWords() {
    if (DEBUG_ENABLE) {
        printf("\n\nHere comes our words as list:\n\t");
        for (int i = 0; i < nWords; i++)
            printf("'%s';\t", words[i]);
    }
}

void printLexicography() {
    if (DEBUG_ENABLE) {
        printf("\n\nHere comes our alphabet:\n");
        map<char, int>::iterator itr;
        for (itr = lexicography.begin(); itr != lexicography.end(); ++itr)
            printf("\n\t'%c': %d;", itr->first, itr->second);
    }
}

// void printWords(map<string, int> wordsMap, char **wordsList) {
void printOccurrences() {
    if (DEBUG_ENABLE) {
        printf("\n\nHere comes our words occurrences:\n");
        map<string, int>::iterator itr;
        for (itr = occurrenceMap.begin(); itr != occurrenceMap.end(); ++itr)
            printf("\n\t'%s': '%d';", itr->first.c_str(), itr->second);
    }
}

//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq

void swap(char str1[], char str2[]) {
    if (str1 != str2) {
        const size_t maxLength = max(strlen(str1), strlen(str2));
        char *temp = (char *)malloc(maxLength * sizeof(char) + 1);
        temp[0] = '\0';
        strcpy(temp, str1);
        strcpy(str1, str2);
        strcpy(str2, temp);
        free(temp);
    }
}

int compareWords(const char *str1, const char *str2) {
    
    const int len1 = (int)strlen(str1);
    const int len2 = (int)strlen(str2);
    const int minLength = len1 <= len2 ? len1 : len2;
    
    for (int i = 0; i < minLength; i++) {
        char c1 = str1[i], c2 = str2[i];
        bool isMapTest = lexicography.count(c1) > 0 && lexicography.count(c2) > 0;
        int delta = isMapTest ? lexicography.at(c1) - lexicography.at(c2) : c1 - c2;
        if (delta != 0) return delta;
    }

    return len1 == len2 ? 0 : (len1 > len2 ? 1 : -1);
}

void sortByMedianOfM(const int low, const int high, const bool dbg) {

    if (m > (high - low) || m < 2)
        return;

    // Determine which points are we gonna work on
	const int step = (high - low) / (m - 1);
	int *points = (int *)malloc(m * sizeof(int));
    int aux = 0;
	for (int i = low; i <= high - 1 && aux < (m - 1); i += step) {
		points[aux++] = i;
	}
	points[aux] = high;

	if (dbg) {
		for (int i = 0; i < m; i++)
			// printf("\n edgePoints[%d] = '%d' --> '%d'", i, points[i], array[points[i]]);
			printf("\n edgePoints[%d] = '%d' --> '%s'", i, points[i], words[points[i]]);
	}

    // Calculate the net distance among each other
	int *diffs = (int *)malloc(m * sizeof(int));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (i != j)
				// diffs[i] += array[points[i]] - array[points[j]];
				diffs[i] += compareWords(words[points[i]], words[points[j]]);
		}
	}

	if (dbg) {
		for (int i = 0; i < m; i++)
			printf("\nDIFFs[%d]: '%d'", i, diffs[i]);
	}

    // Sort these members among each other
    int temp = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (compareWords(words[points[i]], words[points[j]]) < 0)
                swap(words[points[i]], words[points[j]]);
        }
    }

	free(points);
	free(diffs);
}

void setPartition(const int low, const int high, int &partition) {

    int i = low;
    char* pivot = words[high];
    sortByMedianOfM(low, high, false);

    for (int j = low; j < high; j++) {
        if (compareWords(words[j], pivot) <= 0)
            swap(words[i++], words[j]);
    }
    
    swap(words[i], words[high]);
    partition = i;
}

void selectionSort(const int start, const int end) {
    
	int i = start;
	int j = start;
	int idxMin = 0;
  
	// Move boundary of unsorted sub array
    for (; i < end; i++)  {
        
		// Find smaller in this sub array
		idxMin = i; 
        for (j = i + 1; j <= end; j++) {
            if (compareWords(words[j], words[idxMin]) < 0)
				idxMin = j;
		}
		swap(words[idxMin], words[i]); 
    } 
} 

void quickSort(const int start, const int end) {
	
	const int range = end - start;
	if (range < 2)
		return;

	if (minPartition && range < minPartition) {
		selectionSort(start, end);
		return;
	}

	int separator = 0;
	if (end - start >= 2) {
		setPartition(start, end, separator);
		quickSort(start, separator - 1);
		quickSort(separator + 1, end);
	}
}

char* getClearedInput(const char* input) {
	
	int i = 0;
	char* cleanInput = (char*)malloc(strlen(input) + 1);

	for (size_t j = 0; j < strlen(input); j++) {
        char c = input[j];
        if (strIsAlphaNumericChar(c) || c == '-')
            cleanInput[i++] = ::tolower(c);
	}
	
	cleanInput[i] = '\0';
	return cleanInput;
}

void parseInput(ifstream &inputStream) {
    
    string line = "";
    string mode = MODE_NONE;
    int maxLength = 0;

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
            char **letters = strSplit(lineCleared, " ", nLetters, &count);
            for (int j = 0; j < count; j++) {
                const char c = letters[j][0];
                lexicography[c] = j;
            }
            continue;
        }

        // Compute words occurrences
        const size_t lineLength = strlen(lineCleared);
        char **lineWords = strSplit(lineCleared, " ", lineLength, &count);
        for (int j = 0; j < count; j++) {
            const int wordSize = (int)strlen(lineWords[j]);
            occurrenceMap[lineWords[j]]++;
            if (wordSize > maxLength)
                maxLength = wordSize;
        }
    }

    // Set words list
    nWords = 0;
    words = (char **)malloc(occurrenceMap.size() * sizeof(char *));
    map<string, int>::iterator itrWords;

    for (itrWords = occurrenceMap.begin(); itrWords != occurrenceMap.end(); ++itrWords) {
        words[nWords] = (char *)malloc(maxLength + 1);
        strcpy(words[nWords], itrWords->first.c_str());
        nWords++;
    }
}


void writeResult(ofstream &outFile) { 
    
    string word = "";
    bool isFound = false;
    int wordOccurrences = 0;
    map<string, int>::iterator itr;

    for (int i = 0; i < nWords; i++) {
        
        for (itr = occurrenceMap.begin(); itr != occurrenceMap.end(); ++itr) {
            if (strcmp(words[i], itr->first.c_str()) == 0) {
                isFound = true;
                wordOccurrences = itr->second;
                break;
            }
        }

        if (!isFound) {
            printf("\n\nWord: '%s' not found in occurrences map!\n", words[i]);
            throw runtime_error("output building failure");
        }

        word = words[i];
        outFile << word << " " << to_string(wordOccurrences) << endl;
        isFound = false;
    }

    outFile << ID_SEQ_END;
}

int main(int argc, char const *argv[]) {
    
    bool statusOK = true;

    ifstream inputStream;
    ofstream outputStream;
    
    try {

        // Parse arguments
        string inputFile = "";
        string outputFile = "";
        // string inputFile = "__test.i";
        // string outputFile = "__test.o";
        
        string param = "";
        string value = "";
        for (int i = 1; i < argc - 1; i += 2) {
            
            param = argv[i];
            value = argv[i + 1];

            if (param == "-i" || param == "-I")
                inputFile = value;
            else if (param == "-o" || param == "-O")
                outputFile = value;
            else if ((param == "-s" || param == "-S") && value.size() == 1 && isdigit(value[0]))
                minPartition = atoi(value.c_str());
            else if ((param == "-m" || param == "-M") && value.size() == 1 && isdigit(value[0]))
                m = atoi(value.c_str());
        }

        inputStream = ifstream(inputFile);
        if (!inputStream.good())
            throw runtime_error("Failure as trying to read input file");


        parseInput(inputStream);
        
        // printf("\n\n ----------- BEFORE ---------------");
        // printLexicography();
        // printOccurrences();
        // printWords();
        
        // printf("\n\n ----------- AFTER ---------------");
        quickSort(0, nWords - 1);
        // printWords();

        // Build output        
        outputStream = ofstream(outputFile);
        if (!outputStream.good())
            throw runtime_error("Failure as trying to write output file");

        writeResult(outputStream);
        
        cout << endl;
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
    if (outputStream.is_open())
        outputStream.close();

    return statusOK ? EXIT_SUCCESS : EXIT_FAILURE;
}
