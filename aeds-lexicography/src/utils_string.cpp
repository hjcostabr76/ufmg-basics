#include "../include/utils_debug.h"
#include "../include/utils_string.h"

// #include <stdio.h>
#include <stdlib.h>
// #include <stdbool.h>
// #include <sys/types.h>
// #include <arpa/inet.h>
#include <string.h>
#include <regex.h>
// #include <errno.h>
#include <ctype.h>
// #include <netdb.h>
// #include <netinet/in.h>

/**
 * ------------------------------------------------
 * == CONSTS ======================================
 * ------------------------------------------------
 */


/**
 * ------------------------------------------------
 * == STRING ======================================
 * ------------------------------------------------
 */

bool strIsNumeric(const char *string, const bool *isIntOnly) {
	if (isIntOnly != NULL && *isIntOnly)
		return strRegexMatch("^[0-9]+$", string, NULL);
	return strRegexMatch("^[0-9]+(\\.[0-9]+)?$", string, NULL);
}

bool strIsAlphaNumericChar(const char c) {
	return (
		(c >= ASCII_NUM_FIRST && c <= ASCII_NUM_LAST)
		|| (c >= ASCII_CHAR_LC_FIRST && c <= ASCII_CHAR_LC_LAST)
		|| (c >= ASCII_CHAR_UC_FIRST && c <= ASCII_CHAR_UC_LAST)
		|| c == ' '
	);
}

bool strReadFromStdIn(char *buffer, size_t buffLength) {
    if (!fgets(buffer, buffLength, stdin))
		return false; // Error...
	int lastCharIdx = strcspn(buffer, "\n");
	buffer[lastCharIdx] = '\0';
	return true;
}

bool strStartsWith(const char *target, const char *prefix) {
	size_t targetLength = strlen(target);
    size_t prefixLength = strlen(prefix);
	if (prefixLength > targetLength)
        return false;
   return strncmp(target, prefix, strlen(prefix)) == 0;
}

bool strEndsWith(const char *target, const char *suffix) {
	size_t targetLength = strlen(target);
    size_t suffixLength = strlen(suffix);
	if (suffixLength > targetLength)
        return false;
    return strncmp(target + targetLength - suffixLength, suffix, suffixLength) == 0;
}

void strSubstring(const char *src, char *dst, size_t start, size_t end) {
	
	if (start > end) {
		char aux[100] = "";
		sprintf(aux, "strSubstring: 'start' / 'end' (%ld / %ld) nonsense...", start, end);
		comLogErrorAndDie(aux);
	}
	
	strncpy(dst, src + start, end - start);
	dst[end - start] = '\0';
}

bool strSetDelimitedTextBounds(const char* src, const char *delimiter, int *begin, int *end) {

    // Validate
	const int msgSize = strlen(src);
    const int delimiterSize = strlen(delimiter);

    if (!msgSize || !delimiterSize || delimiterSize > msgSize) {
        char msg[60] = "";
        sprintf(msg, "[Error!] 'msgSize' / 'delimiterSize' nonsense (%d / %d)...", msgSize, delimiterSize);
        comDbgStep(msg);
        return false;
    }

	const bool noBegin = begin == NULL;
	if (noBegin)
		begin = (int *)malloc(sizeof(int));
	const bool noEnd = end == NULL;
	if (noEnd)
		end = (int *)malloc(sizeof(int));

    // Seek for the message we're looking for
    *begin = -1;
    *end = -1;

    int i = 0;
    char *temp = (char *)malloc(msgSize + 1);
    temp[0] = '\0';

    do {

        // Check for a match
        strSubstring(src, temp, i, msgSize);
        
        const bool isMatch = strStartsWith(temp, delimiter);
        if (!isMatch) {
            i += 1;
            continue;
        }
        
        // Update search state
        if (*begin >= 0) {
            *end = i;
            break;
        }
        
        i += delimiterSize;
        *begin = i;

    } while (i < msgSize);

    const bool isSuccess = (*begin >= 0 && *end > *begin);

	// Free some memory
	if (noBegin)
		free(begin);
	if (noEnd)
		free(end);

	// We're good
	return isSuccess;
}

char** strSplit(const char* source, const char *delimiter, const int maxTokens, const int maxLength, int *tokensCount) {
    
	const bool isCounterNull = tokensCount == NULL;
	if (isCounterNull)
    	tokensCount = (int *)malloc(sizeof(int));
    *tokensCount = 0;
    
	char** tokens = (char **)malloc(maxTokens * sizeof(char*));
	char *aux = (char *)malloc(strlen(source));
	strcpy(aux, source);
	
	char *token = strtok(aux, delimiter);
	if (token == NULL)
        return tokens;

    while (token != NULL && *tokensCount < maxTokens) {

		const int allocSize = maxLength + 1;
        tokens[*tokensCount] = (char *)malloc(allocSize);
        memset(tokens[*tokensCount], 0, allocSize);
        strcpy(tokens[*tokensCount], token);
        
        *tokensCount = *tokensCount + 1;
        token = strtok(NULL, delimiter);
    }

    free(aux);
	if (isCounterNull)
		free(tokensCount);
    return tokens;
}

bool strRegexMatch(const char* pattern, const char* str, char errorMsg[100]) {

    regex_t regex;
	if (errorMsg != NULL) {
    	memset(errorMsg, 0, 100);
	}
    
    // Compile
    int regStatus = regcomp(&regex, pattern, REG_EXTENDED);
    if (regStatus != 0) {
        sprintf(errorMsg, "Compiling error");
        return false;
    }

    // Execute
    regStatus = regexec(&regex, str, 0, NULL, 0);
    
    bool isSuccess = regStatus == 0;
    if (errorMsg != NULL && !isSuccess && regStatus != REG_NOMATCH) { // Error
        char aux[100];
        regerror(regStatus, &regex, aux, 100);
        sprintf(errorMsg, "Match error: %s\n", aux);
    }

    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);
    return isSuccess;
}

// char* strTrim(const char* input) {

// 	// Left trim
// 	char* trimmed = (char *)malloc(strlen(input + 1));
//     while (isspace(*trimmed)) trimmed++;
    
// 	// Right trim
// 	char* back = trimmed + strlen(trimmed);
//     while (isspace(*--back));
//     *(back + 1) = '\0';

// 	return trimmed;
// }


char* strGetStringFromIntList(const int list[], const int length) {

	char* result = (char *)malloc(length + 1);
	char* aux = (char *)malloc(length + 1);
	result[0] = '\0';
	aux[0] = '\0';

	for (int i = 0; i < length; i++) {
		const int number = list[i];
		if (i == 0)
			sprintf(result, "%d", number);
		else {
			sprintf(result, "%s,%d", aux, number);
		}
		strcpy(aux, result);
	}

	free(aux);
	return result;
}

int* strGetIntListFromString(const char* string, int maxTokens, int *length) {

	const bool isLengthNull = length == NULL;
	if (isLengthNull)
		length = (int *)malloc(sizeof(int));
	*length = 0;

	bool isEmpty = string == NULL || !strlen(string);
	if (isEmpty)
		return NULL;

	char **strList = strSplit(string, ",", maxTokens, 2, length);
	int *intList = (int *)malloc(*length);
	for (int i = 0; i < *length; i++)
		intList[i] = atoi(strList[i]);
	
	if (isLengthNull)
		free(length);
	
	return intList;
}

int strGetIntBetweenDelimiter(const char *text, const char* delimiter) {

	int begin = 0;
    int end = 0;
	bool hasSomething = strSetDelimitedTextBounds(text, delimiter, &begin, &end);
	if (!hasSomething)
		return 0;

    char *temp = (char *)malloc(strlen(text) + 1);
    temp[0] = '\0';
	strSubstring(text, temp, begin, end);
	
	const int aux = atoi(temp);
	return aux > 0 ? aux : 0;
}

char* strFromInt(const int number) {
	const char bigNumber[] = "999999999999";
	char *temp = (char *)malloc(strlen(bigNumber) + 1);
	sprintf(temp, "%d", number);
	const int size = strlen(temp);
	char *numeric = (char *)malloc(size + 1);
	strSubstring(temp, numeric, 0, size);
	free(temp);
	return numeric;
}

char* strFromFloat(const float number) {
	const char bigNumber[] = "999999999999";
	char *temp = (char *)malloc(strlen(bigNumber) + 1);
	sprintf(temp, "%.2f", number);
	const int size = strlen(temp);
	char *numeric = (char *)malloc(size + 1);
	strSubstring(temp, numeric, 0, size);
	free(temp);
	return numeric;
}

void strToLower(char *str) {
	const int lowToUpSpace = ASCII_CHAR_UC_FIRST - ASCII_CHAR_LC_FIRST;
	const ssize_t size = strlen(str);
	for (int i = 0; i < size; i++) {
		const bool isUpper = str[i] >= ASCII_CHAR_UC_FIRST && str[i] <= ASCII_CHAR_UC_LAST;
		if (isUpper)
			str[i] -= lowToUpSpace;
	}
}

void strToUpper(char *str) {
	const int lowToUpSpace = ASCII_CHAR_UC_FIRST - ASCII_CHAR_LC_FIRST;
	const ssize_t size = strlen(str);
	for (int i = 0; i < size; i++) {
		const bool isLower = str[i] >= ASCII_CHAR_LC_FIRST && str[i] <= ASCII_CHAR_LC_FIRST;		
		if (isLower)
			str[i] += lowToUpSpace;
	}
}

char* strReplace(char const *src, const char *target, const char *replacer) {

    // Validate
	const size_t srcSize = src != NULL ? strlen(src) : 0;
    const size_t targetSize = target != NULL ? strlen(target) : 0;
    const size_t replacerSize = replacer != NULL ? strlen(replacer) : 0;
    
    if (!srcSize || !targetSize || !replacerSize || targetSize > srcSize || replacerSize > srcSize)
        return NULL;
	
    // Seek for matches
    size_t resultMaxSize = replacerSize * srcSize;
    char *copy = (char *)malloc(resultMaxSize + 1);
    char *part1 = (char *)malloc(srcSize + 1);
    char *part2 = (char *)malloc(srcSize + 1);
    
    part1[0] = '\0';
    part2[0] = '\0';
    copy[0] = '\0';
    strcpy(copy, src);

    size_t begin = 0;
    size_t i = 0;

    do {
        
        const bool isMatch = strStartsWith(src + i, target);
        if (isMatch) {
            strSubstring(src, part1, begin, i);
            strSubstring(src, part2, i + targetSize, srcSize);
            sprintf(copy, "%s%s%s", part1, replacer, part2);
            begin = i;
        }

        i += isMatch ? targetSize : 1;

    } while (i < srcSize);

    free(part1);
    free(part2);
	return copy;
}

bool strHasSubstring(const char* src, const char *substring, int *nMatches) {

    // Validate
    const bool noMatchesCounter = nMatches == NULL;
	if (noMatchesCounter)
		nMatches = (int *)malloc(sizeof(int));
    *nMatches = 0;

	const size_t srcSize = src != NULL ? strlen(src) : 0;
    const size_t subSize = substring != NULL ? strlen(substring) : 0;
    
    if (!srcSize || !subSize || subSize > srcSize) {
        if (noMatchesCounter)
            free(nMatches);
        return false;
    }
	
    // Seek for matches
    size_t i = 0;

    do {
        const bool isMatch = strStartsWith(src + i, substring);
        if (isMatch)
            *nMatches = *nMatches + 1;
        i += isMatch ? subSize : 1;

    } while (i < srcSize);

    const bool isFound = *nMatches > 0;
	if (noMatchesCounter)
		free(nMatches);
	return isFound;
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