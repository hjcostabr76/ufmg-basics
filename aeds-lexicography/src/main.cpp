#include "../include/utils_debug.h"
#include "../include/utils_string.h"

#include <iostream>
// #include <stdlib.h>
#include <string.h>
// #include <memory>
#include <sstream>
#include <fstream>

// #include <string.h>
#include <fstream>
#include <map>

using namespace std;

const string ID_SEQ_ORDER = "#ORDEM";
const string ID_SEQ_TXT = "#TEXTO";

int main() {
    
    bool statusOK = true;

    // const char target[] = "ar";
    // const char replacer[] = "REP";
    
    // const char foo[] = "altar";
    // const char *baz = strReplace(foo, target, replacer);
    // printf("\n(replacing: '%s' -> '%s') | Before: '%s'; After: '%s';", target, replacer, foo, baz);

    // const char bar[] = "armario arriado";
    // const char *chico = strReplace(bar, target, replacer);
    // printf("\n(replacing: '%s' -> '%s') | Before: '%s'; After: '%s';", target, replacer, bar, chico);


    // const char caray[] = "arquear";
    // const char *coco = strReplace(caray, target, replacer);
    // printf("\n(replacing: '%s' -> '%s') | Before: '%s'; After: '%s';", target, replacer, caray, coco);
    // int nMatches = 0;
    // const char foo[] = "abaacaate";
    // strHasSubstring(foo, "aa", &nMatches);
    // printf("\nfoo: '%s': %d matches;", foo, nMatches);

    // const char bar[] = "abaacate";
    // strHasSubstring(bar, "aa", &nMatches);
    // printf("\nbar: '%s': %d matches;", bar, nMatches);

    // const char baz[] = "albatroz";
    // strHasSubstring(baz, "aa", &nMatches);
    // printf("\nbaz: '%s': %d matches;", baz, nMatches);
    
    int n = 35;
    char sources[35][30] = {
        "antesádepois",
        "antesãdepois",
        "antesâdepois",
        "antesêdepois",
        "antesẽdepois",
        "antesídepois",
        "antesìdepois",
        "antesódepois",
        "antesòdepois",
        "antesôdepois",
        "antesõdepois",
        "antesúdepois",
        "antesùdepois",
        "antesûdepois",
        "antesçdepois",
        "antesÁdepois",
        "antesÀdepois",
        "antesÃdepois",
        "antesÂdepois",
        "antesÉdepois",
        "antesÈdepois",
        "antesÊdepois",
        "antesẼdepois",
        "antesÍdepois",
        "antesÌdepois",
        "antesÓdepois",
        "antesÒdepois",
        "antesÔdepois",
        "antesÕdepois",
        "antesÚdepois",
        "antesÙdepois",
        "antesÛdepois",
        "antesÇdepois"
    };

    try {

        for (int i = 0; i < n; i++) {
            char *source = sources[i];
            printf("\nPIMBA: antes: '%s'; depois: ", source);
            strRemoveAccents(source);
            printf("'%s';", source);
        }

        // All good
        cout << endl;
        cout << "-- The End --" << endl;

    } catch (exception &error) {
        statusOK = false;
        cout << "-- Ops! Something wrong isn't right... --" << endl;
        if (DEBUG_ENABLE)
            cout << "What went wrong: '" << error.what() << "'" << endl;
        cout << endl;
    }

    // Fim da execucao
    return statusOK ? EXIT_SUCCESS : EXIT_FAILURE;
}