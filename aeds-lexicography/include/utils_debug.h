#pragma once

#include <stdbool.h>

/**
 * ------------------------------------------------
 * == CONSTS ======================================
 * ------------------------------------------------
 */

#define DEBUG_ENABLE true

/**
 * ------------------------------------------------
 * == HEADERS =====================================
 * ------------------------------------------------
 */

void comDbgStep(const char *text);
void comLogErrorAndDie(char *msg);
// char* comDbgBool(bool v);
