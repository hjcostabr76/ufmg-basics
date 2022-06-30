#pragma once

#include <stdbool.h>
#include <stdio.h>

/**
 * ------------------------------------------------
 * == CONSTS ======================================
 * ------------------------------------------------
 */

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

/**
 * ------------------------------------------------
 * == HEADERS =====================================
 * ------------------------------------------------
 */

// int comValidateLCaseString(const char *string, const int strLength);
bool strReadFromStdIn(char *buffer, size_t buffLength);
bool strRegexMatch(const char* pattern, const char* str, char errorMsg[100]);
bool strEndsWith(const char *target, const char *suffix);
bool strStartsWith(const char *target, const char *prefix);
bool strIsNumeric(const char *string, const bool *isIntOnly);
bool strIsAlphaNumericChar(const char c);
// char* strTrim(const char *string);
char** strSplit(const char* source, const char *delimiter, const int maxTokens, const int maxLength, int *tokensCount);
void strSubstring(const char *src, char *dst, size_t start, size_t end);
bool strSetDelimitedTextBounds(const char* src, const char *delimiter, int *begin, int *end);
char* strGetStringFromIntList(const int list[], const int listSize);
int strGetIntBetweenDelimiter(const char *text, const char* delimiter);
char* strFromInt(const int number);
char* strFromFloat(const float number);
int* strGetIntListFromString(const char* string, int maxTokens, int *length);
void strToLower(char *str);
void strToUpper(char *str);
char* strReplace(char const *src, const char *target, const char *replacer);
bool strHasSubstring(const char* src, const char *substring, int *nMatches);
void strRemoveAccents(char *str);
char* strStripRepeatedChar(const char* input, const char target);