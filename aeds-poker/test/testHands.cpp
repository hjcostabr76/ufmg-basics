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

typedef struct {
    int nTests;
    int nFailures;
} TestResult;

/**
 * ------------------------------------------------
 * == HELPERS =====================================
 * ------------------------------------------------
 */

/**
 * TODO: 2022-06-03 - Find out what to do with the score
 */
bool testOneHand(const HandTest test) {

    cout << endl << "Testing (" << test.title << ")" << endl;
    
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
        cout << "\t-- Cards: -----------------------" << endl;
        cout << dbgGetCardsPrint(test.cards, CARDS_PER_HAND);
        
        string suit;
        suit += hand.suit;

        cout << "\t-- What came: -------------------" << endl;
        cout << "\thand.suit: '" << suit << "'" << endl;
        cout << "\thand.type: '" << to_string(hand.type) << "'" << endl;
        cout << "\thand.fourOfKindNumber: '" << to_string(hand.fourOfKindNumber) << "'" << endl;
        cout << "\thand.threeOfKindNumber: '" << to_string(hand.threeOfKindNumber) << "'" << endl;
        cout << "\thand.pairNumber1: '" << to_string(hand.pairNumber1) << "'" << endl;
        cout << "\thand.pairNumber2: '" << to_string(hand.pairNumber2) << "'" << endl;
        cout << "\thand.highest: '" << to_string(hand.highest) << "'" << endl;
        
        suit = "";
        suit += test.hand.suit;
        cout << "\t-- What was supposed to come: ---" << endl;
        cout << "\thand.suit: '" << suit << "'" << endl;
        cout << "\thand.type: '" << to_string(test.hand.type) << "'" << endl;
        cout << "\thand.fourOfKindNumber: '" << to_string(test.hand.fourOfKindNumber) << "'" << endl;
        cout << "\thand.threeOfKindNumber: '" << to_string(test.hand.threeOfKindNumber) << "'" << endl;
        cout << "\thand.pairNumber1: '" << to_string(test.hand.pairNumber1) << "'" << endl;
        cout << "\thand.pairNumber2: '" << to_string(test.hand.pairNumber2) << "'" << endl;
        cout << "\thand.highest: '" << to_string(test.hand.highest) << "'" << endl;
    }

    if (isSuccess)
        cout << "> OK!" << endl;
    else
        cout << "> Not OK!" << endl;

    return isSuccess;
}

TestResult testManyHands(const string title, HandTest tests[], const int nTests) {

    cout << endl << endl << "----- New Test: " << title << " ------------------------------";

    int nFailures = 0;
    for (int i = 0; i < nTests; i++) {
        HandTest test = tests[i];
        bool isSuccess = testOneHand(test);
        if (!isSuccess)
            nFailures++;
    }

    if (!nFailures)
        cout << "-------------------- ALL TESTS PASSED! ------------------" << endl;
    else
        cout << "-------------------- " << to_string(nFailures) << " TEST(S) FAILED --------------------" << endl;

    return { nTests, nFailures };
}

/**
 * ------------------------------------------------
 * == TEST ========================================
 * ------------------------------------------------
 */

/** 05 cards of the same suit in row counting from 10 to Aces. */
TestResult testRoyalStraightFlush(void) {
    
    TestResult result;

    /** == VALID: Must fit for all suits ================ */

    int n = -1;
    int nTests = SUITS_COUNT + 2;
    bool isVerbose = false;
    HandTest validTests[nTests];

    char suit;
    
    for (int i = 0; i < SUITS_COUNT; i++) {
        
        n++;
        suit = SUITS_LIST[i];

        string suitAux;
        suitAux += suit;

        validTests[n].title = "Must fit for suit" + suitAux;
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

    result = testManyHands("Royal Straight Flush", validTests, nTests);

    /** == INVALID Tests ====================== */

    n = -1;
    nTests = 1;
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

    TestResult aux = testManyHands("Royal Straight Flush", invalidTests, nTests);
    result.nTests = aux.nTests;
    result.nFailures = aux.nFailures;
    
    return result;
}

/** 05 cards of the same suit in a row NOT counting from 10 to Ace (!= RSF). */
TestResult testStraightFlush(void) {

    /** == VALID ======================================== */

    int n = -1;
    int nTests = SUITS_COUNT + 9 + 2;
    bool isVerbose = false;
    HandTest validTests[nTests];

    char suit;
    for (int i = 0; i < SUITS_COUNT; i++) {
        
        n++;
        suit = SUITS_LIST[i];

        string suitAux;
        suitAux += suit;

        validTests[n].title = "Must fit for suit" + suitAux;
        validTests[n].isVerbose = isVerbose;
        validTests[n].hand = getEmptyHand();
        validTests[n].hand.type = HAND_STRAIGHT_FLUSH;
        validTests[n].hand.suit = suit;
        
        validTests[n].cards[0] = { suit, 9 };
        validTests[n].cards[1] = { suit, 10 };
        validTests[n].cards[2] = { suit, 11 };
        validTests[n].cards[3] = { suit, 12 };
        validTests[n].cards[4] = { suit, 13 };
    }


    /** == VALID: Must fit for all valid sequences ====== */
    
    // New Test...
    suit = SUIT_CLUBS;

    for (int i = 1; i < 10; i++) {

        n++;
        validTests[n].title = "Must fit for sequence starting from " + to_string(i);
        validTests[n].isVerbose = isVerbose;
        validTests[n].hand = getEmptyHand();
        validTests[n].hand.type = HAND_STRAIGHT_FLUSH;
        validTests[n].hand.suit = suit;

        for (int j = 0; j < CARDS_PER_HAND; j++)
            validTests[n].cards[j] = { suit, i + j };
    }


    /** == VALID: Must fit for unordered sequences ====== */
    
    // New Test...
    n++;
    suit = SUIT_HEARTS;

    validTests[n].title = "Must fit for unordered sequences";
    validTests[n].isVerbose = isVerbose;
    validTests[n].hand = getEmptyHand();
    validTests[n].hand.type = HAND_STRAIGHT_FLUSH;
    validTests[n].hand.suit = suit;
    
    validTests[n].cards[0] = { suit, 9 };
    validTests[n].cards[1] = { suit, 12 };
    validTests[n].cards[2] = { suit, 10 };
    validTests[n].cards[3] = { suit, 13 };
    validTests[n].cards[4] = { suit, 11 };

    // New Test...
    n++;
    suit = SUIT_DIAMONDS;

    validTests[n].title = "Must fit for unordered sequences";
    validTests[n].isVerbose = isVerbose;
    validTests[n].hand = getEmptyHand();
    validTests[n].hand.type = HAND_STRAIGHT_FLUSH;
    validTests[n].hand.suit = suit;
    
    validTests[n].cards[0] = { suit, 3 };
    validTests[n].cards[1] = { suit, 7 };
    validTests[n].cards[2] = { suit, 5 };
    validTests[n].cards[3] = { suit, 4 };
    validTests[n].cards[4] = { suit, 6 };

    return testManyHands("Straight Flush", validTests, nTests);
}

TestResult testFourOfKind(void) {

    /** == VALID ======================================== */

    int n = -1;
    int nTests = SUITS_COUNT + CARD_NUM_KING + CARDS_PER_HAND;
    bool isVerbose = false;
    HandTest validTests[nTests];

    // Must fit for any suit
    char suit;
    for (int i = 0; i < SUITS_COUNT; i++) {
        
        n++;
        suit = SUITS_LIST[i];
        char altSuit = i > 0 ? SUITS_LIST[i - 1] : SUITS_LIST[1];

        string suitAux;
        suitAux += suit;
        int fourOfKindNumber = i + 1;

        validTests[n].title = "Must fit for suit" + suitAux;
        validTests[n].isVerbose = isVerbose;
        validTests[n].hand = getEmptyHand();
        validTests[n].hand.type = HAND_4_KIND;
        validTests[n].hand.suit = suit;
        validTests[n].hand.fourOfKindNumber = fourOfKindNumber;
        
        validTests[n].cards[0] = { suit, fourOfKindNumber };
        validTests[n].cards[1] = { suit, fourOfKindNumber };
        validTests[n].cards[2] = { suit, fourOfKindNumber };
        validTests[n].cards[3] = { suit, fourOfKindNumber };
        validTests[n].cards[4] = { altSuit, fourOfKindNumber + 1 };
    }

    // Must fit for any number
    suit = SUIT_DIAMONDS;
    for (int i = 1; i <= CARD_NUM_KING; i++) {
        
        n++;
        int fourOfKindNumber = i;
        
        validTests[n].title = "Must fit for card number " + to_string(fourOfKindNumber);
        validTests[n].isVerbose = isVerbose;
        validTests[n].hand = getEmptyHand();
        validTests[n].hand.type = HAND_4_KIND;
        validTests[n].hand.suit = suit;
        validTests[n].hand.fourOfKindNumber = fourOfKindNumber;

        validTests[n].cards[0] = { suit, fourOfKindNumber };
        validTests[n].cards[1] = { suit, fourOfKindNumber };
        validTests[n].cards[2] = { suit, fourOfKindNumber };
        validTests[n].cards[3] = { suit, fourOfKindNumber };
        validTests[n].cards[4] = { suit, fourOfKindNumber - 1 };
    }

    // Must fit with different number at any position
    suit = SUIT_SPADES;

    for (int i = 0; i < CARDS_PER_HAND; i++) {

        n++;
        int fourOfKindNumber = 13 - i;
        
        validTests[n].title = "Must fit for different number at place " + to_string(i + 1);
        validTests[n].isVerbose = isVerbose;
        validTests[n].hand = getEmptyHand();
        validTests[n].hand.type = HAND_4_KIND;
        validTests[n].hand.suit = suit;
        validTests[n].hand.fourOfKindNumber = fourOfKindNumber;

        for (int j = 0; j < CARDS_PER_HAND; j++)
            validTests[n].cards[j] = { suit, fourOfKindNumber };

        // Place different card at varying position
        validTests[n].cards[i].number = fourOfKindNumber - 1;
    }

    return testManyHands("Four of a kind", validTests, nTests);
}

int main() {

    // Notify tests start
    cout << endl << endl
        << ">> ---------------------------------------------------------------------------- >>" << endl
        << ">> Running tests... >> Running tests... >> Running tests... >> Running tests... >>" << endl
        << ">> ---------------------------------------------------------------------------- >>" << endl;

    // Trun test groups
    TestResult acc = { 0, 0 };
    TestResult aux;
    int nGroups = 0;

    nGroups++;
    aux = testRoyalStraightFlush();
    acc.nTests += aux.nTests;
    acc.nFailures += aux.nFailures;
    
    nGroups++;
    aux = testStraightFlush();
    acc.nTests += aux.nTests;
    acc.nFailures += aux.nFailures;

    nGroups++;
    aux = testFourOfKind();
    acc.nTests += aux.nTests;
    acc.nFailures += aux.nFailures;

    // Notify end result
    bool isSuccess = acc.nFailures == 0;

    cout << endl << "<< ---------------------------------------------------------------------------- <<" << endl;

    if (isSuccess)
        cout << "<<<< All tests passed! >>> <<<< All tests passed!! >>>> <<< All tests passed! >>>>" << endl;
    else
        cout << "<<<<--- TESTS FAILED --->>> <<<--- TESTS FAILED --->>> <<<--- TESTS FAILED --->>>>" << endl;
    
    cout << "<< ---------------------------------------------------------------------------- <<" << endl
        << endl
        << ">> " << to_string(nGroups) << " test group(s);" << endl
        << ">> " << to_string(acc.nTests) << " unit test(s);" << endl
        << ">> " << to_string(acc.nFailures) << " error(s); " << endl
        << endl;
}
