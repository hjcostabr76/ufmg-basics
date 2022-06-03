#include <iostream>
// #include <string.h>

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <regex.h>
// #include <string.h>

#include "../include/types.h"
#include "../include/game.h"
#include "../include/debug.h"

typedef struct {
    Card cards[CARDS_PER_HAND];
    Hand hand;
    bool isVerbose;
} HandTest;

/**
 * ------------------------------------------------
 * == HELPERS =====================================
 * ------------------------------------------------
 */

bool testOneHand(const HandTest test) {

    cout << endl << endl << "Testing cards: '" << endl << dbgGetCardsPrint(test.cards, CARDS_PER_HAND);
    
    Hand hand = getHand(test.cards);
    bool isSuccess = (
        hand.suit == test.hand.suit
        && hand.fourOfKindNumber == test.hand.fourOfKindNumber
        && hand.threeOfKindNumber == test.hand.threeOfKindNumber
        && hand.pairNumber1 == test.hand.pairNumber1
        && hand.pairNumber2 == test.hand.pairNumber2
        && hand.highest == test.hand.highest
        && hand.score == test.hand.score
    );

    if (test.isVerbose || !isSuccess) {
        string suit;
        suit += hand.suit;

        cout << endl << "\t-- What came: -------------------";
        cout << endl << "\thand.suit: '" << suit << "'";
        cout << endl << "\thand.fourOfKindNumber: '" << to_string(hand.fourOfKindNumber) << "'";
        cout << endl << "\thand.threeOfKindNumber: '" << to_string(hand.threeOfKindNumber) << "'";
        cout << endl << "\thand.pairNumber1: '" << to_string(hand.pairNumber1) << "'";
        cout << endl << "\thand.pairNumber2: '" << to_string(hand.pairNumber2) << "'";
        cout << endl << "\thand.highest: '" << to_string(hand.highest) << "'";
        cout << endl << "\thand.score: '" << to_string(hand.score) << "'";
        
        suit = "";
        suit += hand.suit;
        cout << endl << "\t-- What was supposed to come: ---";
        cout << endl << "\thand.suit: '" << suit << "'";
        cout << endl << "\thand.fourOfKindNumber: '" << to_string(test.hand.fourOfKindNumber) << "'";
        cout << endl << "\thand.threeOfKindNumber: '" << to_string(test.hand.threeOfKindNumber) << "'";
        cout << endl << "\thand.pairNumber1: '" << to_string(test.hand.pairNumber1) << "'";
        cout << endl << "\thand.pairNumber2: '" << to_string(test.hand.pairNumber2) << "'";
        cout << endl << "\thand.highest: '" << to_string(test.hand.highest) << "'";
        cout << endl << "\thand.score: '" << to_string(test.hand.score) << "'";
    }

    if (isSuccess)
        cout << endl << "> OK!";
    else
        cout << endl << "> Not OK!";

    return isSuccess;
}

bool testManyHands(const string title, HandTest tests[], const int nTests, const bool isValid) {

    string aux = isValid ? "valid" : "invalid";
    cout << endl << endl << "----- New Test: " << title << " [" << aux << "examples] ------------";

    int failuresCount = 0;
    for (int i = 0; i < nTests; i++) {
        HandTest test = tests[i];
        bool isSuccess = testOneHand(test);
        if (!isSuccess)
            failuresCount++;
    }

    if (!failuresCount)
        cout << endl << "-------------------- ALL TESTS PASSED! --------------" << endl;
    else
        cout << "-------------------- " << to_string(failuresCount) << " TESTS FAILED ---------------" << endl;

    return !failuresCount;
}

/**
 * ------------------------------------------------
 * == TEST ========================================
 * ------------------------------------------------
 */

/** 05 cards of the same suit in row counting from 10 to Aces. */
void testRoyalStraightFlush(void) {

    /** == VALID Tests ========== */

    int n = -1;
    int nTests = 1;
    bool isVerbose = true;
    HandTest validTests[nTests];

    // New test...
    n++;
    validTests[n].isVerbose = isVerbose;
    validTests[n].hand = getEmptyHand();
    validTests[n].hand.type = HAND_ROYAL_STRAIGHT_FLUSH;
    
    validTests[n].cards[0] = { 'P', 10 }; 
    validTests[n].cards[1] = { 'P', 11 }; 
    validTests[n].cards[2] = { 'P', 12 }; 
    validTests[n].cards[3] = { 'P', 13 }; 
    validTests[n].cards[4] = { 'P', 1 }; 

    testManyHands("Royal Straight Flush", validTests, nTests, true);
}

int main() {
    testRoyalStraightFlush();
}
