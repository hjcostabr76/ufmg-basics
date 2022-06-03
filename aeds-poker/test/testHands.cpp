#include <string.h>
#include <iostream>

#include "../include/types.h"
#include "../include/game.h"
#include "../include/debug.h"

typedef struct {
    Card cards[CARDS_PER_HAND];
    Hand hand;
    bool isVerbose;
    string title;
} HandTest;

/**
 * ------------------------------------------------
 * == HELPERS =====================================
 * ------------------------------------------------
 */

/**
 * TODO: 2022-06-03 - Find out what to do with the score
 */
bool testOneHand(const HandTest test) {

    cout << endl << endl << "Testing (" << test.title << "):" << endl;
    if (test.isVerbose)
        cout << dbgGetCardsPrint(test.cards, CARDS_PER_HAND);
    
    Hand hand = getHand(test.cards);
    bool isSuccess = (
        hand.suit == test.hand.suit
        && hand.type == test.hand.type
        && hand.fourOfKindNumber == test.hand.fourOfKindNumber
        && hand.threeOfKindNumber == test.hand.threeOfKindNumber
        && hand.pairNumber1 == test.hand.pairNumber1
        && hand.pairNumber2 == test.hand.pairNumber2
        && hand.highest == test.hand.highest
        // && hand.score == test.hand.score
    );

    if (test.isVerbose || !isSuccess) {
        string suit;
        suit += hand.suit;

        cout << endl << "\t-- What came: -------------------";
        cout << endl << "\thand.suit: '" << suit << "'";
        cout << endl << "\thand.type: '" << to_string(hand.type) << "'";
        cout << endl << "\thand.fourOfKindNumber: '" << to_string(hand.fourOfKindNumber) << "'";
        cout << endl << "\thand.threeOfKindNumber: '" << to_string(hand.threeOfKindNumber) << "'";
        cout << endl << "\thand.pairNumber1: '" << to_string(hand.pairNumber1) << "'";
        cout << endl << "\thand.pairNumber2: '" << to_string(hand.pairNumber2) << "'";
        cout << endl << "\thand.highest: '" << to_string(hand.highest) << "'";
        // cout << endl << "\thand.score: '" << to_string(hand.score) << "'";
        
        suit = "";
        suit += test.hand.suit;
        cout << endl << "\t-- What was supposed to come: ---";
        cout << endl << "\thand.suit: '" << suit << "'";
        cout << endl << "\thand.type: '" << to_string(test.hand.type) << "'";
        cout << endl << "\thand.fourOfKindNumber: '" << to_string(test.hand.fourOfKindNumber) << "'";
        cout << endl << "\thand.threeOfKindNumber: '" << to_string(test.hand.threeOfKindNumber) << "'";
        cout << endl << "\thand.pairNumber1: '" << to_string(test.hand.pairNumber1) << "'";
        cout << endl << "\thand.pairNumber2: '" << to_string(test.hand.pairNumber2) << "'";
        cout << endl << "\thand.highest: '" << to_string(test.hand.highest) << "'";
        // cout << endl << "\thand.score: '" << to_string(test.hand.score) << "'";
    }

    if (isSuccess)
        cout << endl << "> OK!";
    else
        cout << endl << "> Not OK!";

    return isSuccess;
}

bool testManyHands(const string title, HandTest tests[], const int nTests, const bool isValid) {

    string aux = isValid ? "valid" : "invalid";
    cout << endl << endl << "----- New Test: " << title << " [" << aux << " examples] ------------";

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
        cout << "-------------------- " << to_string(failuresCount) << " TEST(S) FAILED ---------------" << endl;

    return !failuresCount;
}

/**
 * ------------------------------------------------
 * == TEST ========================================
 * ------------------------------------------------
 */

/** 05 cards of the same suit in row counting from 10 to Aces. */
void testRoyalStraightFlush(void) {

    /** == VALID: Must fit for all suits ================ */

    int n = -1;
    int nTests = SUITS_COUNT + 2;
    bool isVerbose = false;
    HandTest validTests[nTests];

    char suit;
    string title = "Must fit for all suits";
    
    for (int i = 0; i < SUITS_COUNT; i++) {
        
        n++;
        suit = SUITS_LIST[i];

        validTests[n].title = title;
        validTests[n].isVerbose = isVerbose;
        validTests[n].hand = getEmptyHand();
        validTests[n].hand.type = HAND_ROYAL_STRAIGHT_FLUSH;
        validTests[n].hand.suit = suit;
        
        validTests[n].cards[0] = { suit, 10 }; 
        validTests[n].cards[1] = { suit, 11 }; 
        validTests[n].cards[2] = { suit, 12 }; 
        validTests[n].cards[3] = { suit, 13 }; 
        validTests[n].cards[4] = { suit, 1 };
    }

    /** == VALID: Must fit for unordered sequences ====== */
    
    // New Test...
    n++;
    suit = SUIT_CLUBS;

    validTests[n].title = "Must fit for unordered sequences";
    validTests[n].isVerbose = isVerbose;
    validTests[n].hand = getEmptyHand();
    validTests[n].hand.type = HAND_ROYAL_STRAIGHT_FLUSH;
    validTests[n].hand.suit = suit;
    
    validTests[n].cards[0] = { suit, 1 };
    validTests[n].cards[1] = { suit, 13 };
    validTests[n].cards[2] = { suit, 12 };
    validTests[n].cards[3] = { suit, 11 };
    validTests[n].cards[4] = { suit, 10 };

    // New Test...
    n++;
    suit = SUIT_DIAMONDS;

    validTests[n].title = "Must fit for unordered sequences";
    validTests[n].isVerbose = isVerbose;
    validTests[n].hand = getEmptyHand();
    validTests[n].hand.type = HAND_ROYAL_STRAIGHT_FLUSH;
    validTests[n].hand.suit = suit;
    
    validTests[n].cards[0] = { suit, 13 };
    validTests[n].cards[1] = { suit, 10 };
    validTests[n].cards[2] = { suit, 12 };
    validTests[n].cards[3] = { suit, 1 };
    validTests[n].cards[4] = { suit, 11 };

    testManyHands("Royal Straight Flush", validTests, nTests, true);

    /** == INVALID Tests ====================== */

    n = -1;
    nTests = 3;
    isVerbose = false;
    HandTest invalidTests[nTests];

    // New Test
    n++;
    suit = SUIT_HEARTS;

    invalidTests[n].title = "Mixed suits";
    invalidTests[n].isVerbose = isVerbose;
    invalidTests[n].hand = getEmptyHand();
    invalidTests[n].hand.type = HAND_HIGHER_CARD;
    
    invalidTests[n].cards[0] = { SUIT_SPADES, 13 };
    invalidTests[n].cards[1] = { suit, 10 };
    invalidTests[n].cards[2] = { suit, 12 };
    invalidTests[n].cards[3] = { suit, 1 };
    invalidTests[n].cards[4] = { suit, 11 };

    // New Test
    n++;
    suit = SUIT_DIAMONDS;

    invalidTests[n].title = "Wrong sequence";
    invalidTests[n].isVerbose = isVerbose;
    invalidTests[n].hand = getEmptyHand();
    invalidTests[n].hand.type = HAND_HIGHER_CARD;
    
    invalidTests[n].cards[0] = { suit, 9 };
    invalidTests[n].cards[1] = { suit, 10 };
    invalidTests[n].cards[2] = { suit, 11 };
    invalidTests[n].cards[3] = { suit, 12 };
    invalidTests[n].cards[4] = { suit, 13 };

    // New Test
    n++;
    suit = SUIT_HEARTS;

    invalidTests[n].title = "Wrong sequence";
    invalidTests[n].isVerbose = isVerbose;
    invalidTests[n].hand = getEmptyHand();
    invalidTests[n].hand.type = HAND_HIGHER_CARD;
    
    invalidTests[n].cards[0] = { suit, 1 };
    invalidTests[n].cards[1] = { suit, 2 };
    invalidTests[n].cards[2] = { suit, 3 };
    invalidTests[n].cards[3] = { suit, 4 };
    invalidTests[n].cards[4] = { suit, 5 };

    testManyHands("Royal Straight Flush", invalidTests, nTests, false);
}

int main() {
    testRoyalStraightFlush();
}
