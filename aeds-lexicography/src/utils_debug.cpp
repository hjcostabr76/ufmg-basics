#include "../include/utils_debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

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

// char* comDbgBool(bool v) {
//     char* aux = v ? "1" : "0";
//     return aux;
// }
