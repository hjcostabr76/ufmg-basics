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

int factorial(int number) {
    int fact = number;
    while (--number)
        fact += number;
    return fact;
}

/**
 * TODO: 2022-06-03 - Find out what to do with the score
 */
bool testOneHand(const HandTest test) {

    std::cout << endl << "Testing (" << test.title << ")" << endl;
    
    Hand hand = getHand(test.cards);
    bool isSuccess = (
        hand.suit == test.hand.suit
        && hand.type == test.hand.type
        && hand.fourOfKindNumber == test.hand.fourOfKindNumber
        && hand.threeOfKindNumber == test.hand.threeOfKindNumber
        && hand.pairNumber == test.hand.pairNumber
        && hand.pairNumber2 == test.hand.pairNumber2
        && hand.highest == test.hand.highest
        // && hand.score == test.hand.score
    );

    if (test.isVerbose || !isSuccess) {
        std::cout << "\t-- Cards: -----------------------" << endl;
        std::cout << dbgGetCardsPrint(test.cards, CARDS_PER_HAND);
        
        string suit;
        suit += hand.suit;

        std::cout << "\t-- What came: -------------------" << endl;
        std::cout << "\thand.suit: '" << suit << "'" << endl;
        std::cout << "\thand.type: '" << to_string(hand.type) << "'" << endl;
        std::cout << "\thand.fourOfKindNumber: '" << to_string(hand.fourOfKindNumber) << "'" << endl;
        std::cout << "\thand.threeOfKindNumber: '" << to_string(hand.threeOfKindNumber) << "'" << endl;
        std::cout << "\thand.pairNumber: '" << to_string(hand.pairNumber) << "'" << endl;
        std::cout << "\thand.pairNumber2: '" << to_string(hand.pairNumber2) << "'" << endl;
        std::cout << "\thand.highest: '" << to_string(hand.highest) << "'" << endl;
        
        suit = "";
        suit += test.hand.suit;
        std::cout << "\t-- What was supposed to come: ---" << endl;
        std::cout << "\thand.suit: '" << suit << "'" << endl;
        std::cout << "\thand.type: '" << to_string(test.hand.type) << "'" << endl;
        std::cout << "\thand.fourOfKindNumber: '" << to_string(test.hand.fourOfKindNumber) << "'" << endl;
        std::cout << "\thand.threeOfKindNumber: '" << to_string(test.hand.threeOfKindNumber) << "'" << endl;
        std::cout << "\thand.pairNumber: '" << to_string(test.hand.pairNumber) << "'" << endl;
        std::cout << "\thand.pairNumber2: '" << to_string(test.hand.pairNumber2) << "'" << endl;
        std::cout << "\thand.highest: '" << to_string(test.hand.highest) << "'" << endl;
    }

    if (isSuccess)
        std::cout << "> OK!" << endl;
    else
        std::cout << "> Not OK!" << endl;

    return isSuccess;
}

TestResult testManyHands(const string title, HandTest tests[], const int nTests) {

    std::cout << endl << endl << "----- New Test: " << title << " ------------------------------";

    int nFailures = 0;
    for (int i = 0; i < nTests; i++) {
        HandTest test = tests[i];
        bool isSuccess = testOneHand(test);
        if (!isSuccess)
            nFailures++;
    }

    if (!nFailures)
        std::cout << "-------------------- ALL TESTS PASSED! ------------------" << endl;
    else
        std::cout << "-------------------- " << to_string(nFailures) << " TEST(S) FAILED --------------------" << endl;

    return { nTests, nFailures };
}

/**
 * ------------------------------------------------
 * == TEST ========================================
 * ------------------------------------------------
 */

/** 05 cards of the same suit in row counting from 10 to Aces. */
TestResult testRoyalStraightFlush(void) {
    
    /** == VALID: Must fit for all suits ================ */

    int n = -1;
    bool isVerbose = false;
    HandTest tests[SUITS_COUNT + 3];

    char suit;
    
    for (int i = 0; i < SUITS_COUNT; i++) {
        
        n++;
        suit = SUITS_LIST[i];

        string suitAux;
        suitAux += suit;

        tests[n].title = "Must fit for suit " + suitAux;
        tests[n].isVerbose = isVerbose;
        tests[n].hand = getEmptyHand();
        tests[n].hand.type = HAND_ROYAL_STRAIGHT_FLUSH;
        tests[n].hand.suit = suit;
        
        tests[n].cards[0] = { suit, 10 }; 
        tests[n].cards[1] = { suit, 11 }; 
        tests[n].cards[2] = { suit, 12 }; 
        tests[n].cards[3] = { suit, 13 }; 
        tests[n].cards[4] = { suit, 1 };
    }

    /** == VALID: Must fit for unordered sequences ====== */
    
    // New Test...
    n++;
    suit = SUIT_CLUBS;

    tests[n].title = "Must fit for unordered sequences";
    tests[n].isVerbose = isVerbose;
    tests[n].hand = getEmptyHand();
    tests[n].hand.type = HAND_ROYAL_STRAIGHT_FLUSH;
    tests[n].hand.suit = suit;
    
    tests[n].cards[0] = { suit, 1 };
    tests[n].cards[1] = { suit, 13 };
    tests[n].cards[2] = { suit, 12 };
    tests[n].cards[3] = { suit, 11 };
    tests[n].cards[4] = { suit, 10 };

    // New Test...
    n++;
    tests[n].title = "Must fit for unordered sequences";
    tests[n].isVerbose = isVerbose;
    tests[n].hand = getEmptyHand();
    tests[n].hand.type = HAND_ROYAL_STRAIGHT_FLUSH;
    tests[n].hand.suit = SUIT_DIAMONDS;
    
    tests[n].cards[0] = { SUIT_DIAMONDS, 13 };
    tests[n].cards[1] = { SUIT_DIAMONDS, 10 };
    tests[n].cards[2] = { SUIT_DIAMONDS, 12 };
    tests[n].cards[3] = { SUIT_DIAMONDS, 1 };
    tests[n].cards[4] = { SUIT_DIAMONDS, 11 };

    /** == INVALID Tests ====================== */

    // New Test
    n++;
    tests[n].title = "Must not match for mixed suits";
    tests[n].isVerbose = isVerbose;
    tests[n].hand = getEmptyHand();
    tests[n].hand.type = HAND_STRAIGHT;
    
    tests[n].cards[0] = { SUIT_SPADES, 13 };
    tests[n].cards[1] = { SUIT_HEARTS, 10 };
    tests[n].cards[2] = { SUIT_HEARTS, 12 };
    tests[n].cards[3] = { SUIT_HEARTS, 1 };
    tests[n].cards[4] = { SUIT_HEARTS, 11 };

    return testManyHands(HAND_NAMES[HAND_ROYAL_STRAIGHT_FLUSH], tests, n + 1);
}

/** 05 cards of the same suit in a row NOT counting from 10 to Ace (!= RSF). */
TestResult testStraightFlush(void) {

    int n = -1;
    bool isVerbose = false;
    HandTest tests[SUITS_COUNT + 9 + 2];

    /** == VALID: Must for any suit ===================== */

    char suit;
    for (int i = 0; i < SUITS_COUNT; i++) {
        
        n++;
        suit = SUITS_LIST[i];

        string suitAux;
        suitAux += suit;

        tests[n].title = "Must fit for suit " + suitAux;
        tests[n].isVerbose = isVerbose;
        tests[n].hand = getEmptyHand();
        tests[n].hand.type = HAND_STRAIGHT_FLUSH;
        tests[n].hand.suit = suit;
        
        tests[n].cards[0] = { suit, 9 };
        tests[n].cards[1] = { suit, 10 };
        tests[n].cards[2] = { suit, 11 };
        tests[n].cards[3] = { suit, 12 };
        tests[n].cards[4] = { suit, 13 };
    }


    /** == VALID: Must fit for all valid sequences ====== */
    
    // New Test...
    suit = SUIT_CLUBS;

    for (int i = 1; i < 10; i++) {

        n++;
        tests[n].title = "Must fit for sequence starting from " + to_string(i);
        tests[n].isVerbose = isVerbose;
        tests[n].hand = getEmptyHand();
        tests[n].hand.type = HAND_STRAIGHT_FLUSH;
        tests[n].hand.suit = suit;

        for (int j = 0; j < CARDS_PER_HAND; j++)
            tests[n].cards[j] = { suit, i + j };
    }


    /** == VALID: Must fit for unordered sequences ====== */
    
    // New Test...
    n++;
    suit = SUIT_HEARTS;

    tests[n].title = "Must fit for unordered sequences";
    tests[n].isVerbose = isVerbose;
    tests[n].hand = getEmptyHand();
    tests[n].hand.type = HAND_STRAIGHT_FLUSH;
    tests[n].hand.suit = suit;
    
    tests[n].cards[0] = { suit, 9 };
    tests[n].cards[1] = { suit, 12 };
    tests[n].cards[2] = { suit, 10 };
    tests[n].cards[3] = { suit, 13 };
    tests[n].cards[4] = { suit, 11 };

    // New Test...
    n++;
    suit = SUIT_DIAMONDS;

    tests[n].title = "Must fit for unordered sequences";
    tests[n].isVerbose = isVerbose;
    tests[n].hand = getEmptyHand();
    tests[n].hand.type = HAND_STRAIGHT_FLUSH;
    tests[n].hand.suit = suit;
    
    tests[n].cards[0] = { suit, 3 };
    tests[n].cards[1] = { suit, 7 };
    tests[n].cards[2] = { suit, 5 };
    tests[n].cards[3] = { suit, 4 };
    tests[n].cards[4] = { suit, 6 };

    return testManyHands(HAND_NAMES[HAND_STRAIGHT_FLUSH], tests, n + 1);
}

TestResult testFourOfKind(void) {

    int n = -1;
    bool isVerbose = false;
    HandTest tests[SUITS_COUNT + CARD_NUM_KING + CARDS_PER_HAND];

    // Must fit for any suit
    char suit;
    for (int i = 0; i < SUITS_COUNT; i++) {
        
        n++;
        suit = SUITS_LIST[i];
        char altSuit = i > 0 ? SUITS_LIST[i - 1] : SUITS_LIST[1];

        string suitAux;
        suitAux += suit;
        int fourOfKindNumber = i + 1;
        int otherCardNumber = (fourOfKindNumber > 1) ? fourOfKindNumber - 1 : 3;

        tests[n].title = "Must fit for suit " + suitAux;
        tests[n].isVerbose = isVerbose;
        tests[n].hand = getEmptyHand();
        tests[n].hand.type = HAND_4_KIND;
        tests[n].hand.fourOfKindNumber = fourOfKindNumber;
        
        tests[n].cards[0] = { suit, fourOfKindNumber };
        tests[n].cards[1] = { suit, fourOfKindNumber };
        tests[n].cards[2] = { suit, fourOfKindNumber };
        tests[n].cards[3] = { suit, fourOfKindNumber };
        tests[n].cards[4] = { altSuit, otherCardNumber };
    }

    // Must fit for any number
    suit = SUIT_DIAMONDS;
    for (int i = 1; i <= CARD_NUM_KING; i++) {
        
        n++;
        int fourOfKindNumber = i;
        int otherCardNumber = (fourOfKindNumber > 1) ? fourOfKindNumber - 1 : 3;
        
        tests[n].title = "Must fit for card number " + to_string(fourOfKindNumber);
        tests[n].isVerbose = isVerbose;
        tests[n].hand = getEmptyHand();
        tests[n].hand.type = HAND_4_KIND;
        tests[n].hand.fourOfKindNumber = fourOfKindNumber;

        tests[n].cards[0] = { suit, fourOfKindNumber };
        tests[n].cards[1] = { suit, fourOfKindNumber };
        tests[n].cards[2] = { suit, fourOfKindNumber };
        tests[n].cards[3] = { suit, fourOfKindNumber };
        tests[n].cards[4] = { suit, otherCardNumber };
    }
    
    // Must fit with different number at any position
    suit = SUIT_SPADES;

    for (int i = 0; i < CARDS_PER_HAND; i++) {

        n++;
        int fourOfKindNumber = 13 - i;
        
        tests[n].title = "Must fit for different number at place " + to_string(i + 1);
        tests[n].isVerbose = isVerbose;
        tests[n].hand = getEmptyHand();
        tests[n].hand.type = HAND_4_KIND;
        tests[n].hand.fourOfKindNumber = fourOfKindNumber;

        for (int j = 0; j < CARDS_PER_HAND; j++)
            tests[n].cards[j] = { suit, fourOfKindNumber };

        // Place different card at varying position
        tests[n].cards[i].number = fourOfKindNumber - 1;
    }

    return testManyHands(HAND_NAMES[HAND_4_KIND], tests, n + 1);
}


/**
 * 01 pair + 03 of a kind.
 * - In case of a tie, the higher 03 of a kind wins;
 * - If it remains tied, the higher pair wins;
 */
TestResult testFullHouse(void) {

    int n = -1;
    bool isVerbose = false;
    HandTest tests[CARD_NUM_KING + factorial(CARDS_PER_HAND - 1)];
    
    // Must fit for any number
    for (int i = 1; i <= CARD_NUM_KING; i++) {
        
        n++;
        int pairNumber = i;
        int threeOfKindNumber = CARD_NUM_KING - i + 1;
        if (pairNumber == threeOfKindNumber)
            threeOfKindNumber--;

        tests[n].title = "Must fit for card numbers: [Pair: " + to_string(pairNumber) + "] / [03 of kind: " + to_string(threeOfKindNumber) + "]";
        tests[n].isVerbose = isVerbose;
        tests[n].hand = getEmptyHand();
        tests[n].hand.type = HAND_FULL_HOUSE;
        tests[n].hand.pairNumber = pairNumber;
        tests[n].hand.threeOfKindNumber = threeOfKindNumber;
        
        tests[n].cards[0] = { SUIT_HEARTS, pairNumber };
        tests[n].cards[1] = { SUIT_CLUBS, pairNumber };
        tests[n].cards[2] = { SUIT_DIAMONDS, threeOfKindNumber };
        tests[n].cards[3] = { SUIT_SPADES, threeOfKindNumber };
        tests[n].cards[4] = { SUIT_HEARTS, threeOfKindNumber };
    }

    // Must fit for combinations at any position
    int pairNumber = 3;
    int threeOfKindNumber = 8;

    for (int i = 0; i < CARDS_PER_HAND; i++) {
        for (int j = 0; j < CARDS_PER_HAND; j++) {
            
            if (i >= j)
                continue;

            n++;
            tests[n].title = "Must fit for pairs at position (" + to_string(i + 1) + "/" + to_string(j + 1) + ")";
            tests[n].isVerbose = isVerbose;
            tests[n].hand = getEmptyHand();
            tests[n].hand.type = HAND_FULL_HOUSE;
            tests[n].hand.pairNumber = pairNumber;
            tests[n].hand.threeOfKindNumber = threeOfKindNumber;

            for (int k = 0; k < CARDS_PER_HAND; k++) {
                if (k == i || k == j)
                    tests[n].cards[k] = { SUIT_HEARTS, pairNumber };
                else
                    tests[n].cards[k] = { SUIT_DIAMONDS, threeOfKindNumber };
            }
        }   
    }

    return testManyHands(HAND_NAMES[HAND_FULL_HOUSE], tests, n + 1);
}

/**
 * 05 cards of the same suit (without being in a row).
 * - In case of a tie the one with the highest card wins;
 */
TestResult testFlush(void) {

    int n = -1;
    bool isVerbose = false;
    HandTest tests[SUITS_COUNT + 1];

    // Must fit for any suit
    char suit;
    for (int i = 0; i < SUITS_COUNT; i++) {
        
        n++;
        suit = SUITS_LIST[i];

        string suitAux;
        suitAux += suit;

        tests[n].title = "Must fit for suit " + suitAux;
        tests[n].isVerbose = isVerbose;
        tests[n].hand = getEmptyHand();
        tests[n].hand.type = HAND_FLUSH;
        tests[n].hand.suit = suit;
        
        tests[n].cards[0] = { suit, 1 };
        tests[n].cards[1] = { suit, 6 };
        tests[n].cards[2] = { suit, 5 };
        tests[n].cards[3] = { suit, 4 };
        tests[n].cards[4] = { suit, 9 };
    }

    // New test
    n++;
    tests[n].title = "Must fail for mixed suits";
    tests[n].isVerbose = isVerbose;
    tests[n].hand = getEmptyHand();
    tests[n].hand.type = HAND_HIGHER_CARD;
    
    tests[n].cards[0] = { SUIT_DIAMONDS, 1 };
    tests[n].cards[1] = { SUIT_DIAMONDS, 6 };
    tests[n].cards[2] = { SUIT_DIAMONDS, 5 };
    tests[n].cards[3] = { SUIT_DIAMONDS, 4 };
    tests[n].cards[4] = { SUIT_CLUBS, 9 };

    return testManyHands(HAND_NAMES[HAND_FLUSH], tests, n + 1);
}

/**
 * 05 cards in a row not caring about the suit.
 * - In case of a tie, the one with highest card wins;
 */
TestResult testStraight(void) {

    int n = -1;
    bool isVerbose = false;
    HandTest tests[3];

    // New Test...
    n++;
    tests[n].title = "Must fit for unordered sequences";
    tests[n].isVerbose = isVerbose;
    tests[n].hand = getEmptyHand();
    tests[n].hand.type = HAND_STRAIGHT;
    
    tests[n].cards[0] = { SUIT_HEARTS, 9 };
    tests[n].cards[1] = { SUIT_HEARTS, 12 };
    tests[n].cards[2] = { SUIT_HEARTS, 10 };
    tests[n].cards[3] = { SUIT_CLUBS, 13 };
    tests[n].cards[4] = { SUIT_HEARTS, 11 };

    // New Test...
    n++;
    tests[n].title = "Must fit for unordered sequences";
    tests[n].isVerbose = isVerbose;
    tests[n].hand = getEmptyHand();
    tests[n].hand.type = HAND_STRAIGHT;
    
    tests[n].cards[0] = { SUIT_HEARTS, 4 };
    tests[n].cards[1] = { SUIT_HEARTS, 2 };
    tests[n].cards[2] = { SUIT_HEARTS, 5 };
    tests[n].cards[3] = { SUIT_CLUBS, 1 };
    tests[n].cards[4] = { SUIT_HEARTS, 3 };

    // New Test...
    n++;
    tests[n].title = "Must not apply for same suit sequence";
    tests[n].isVerbose = isVerbose;
    tests[n].hand = getEmptyHand();
    tests[n].hand.type = HAND_STRAIGHT_FLUSH;
    tests[n].hand.suit = SUIT_HEARTS;
    
    tests[n].cards[0] = { SUIT_HEARTS, 9 };
    tests[n].cards[1] = { SUIT_HEARTS, 12 };
    tests[n].cards[2] = { SUIT_HEARTS, 10 };
    tests[n].cards[3] = { SUIT_HEARTS, 13 };
    tests[n].cards[4] = { SUIT_HEARTS, 11 };

    return testManyHands(HAND_NAMES[HAND_STRAIGHT], tests, n + 1);
}


/**
 * 03 equal cards + 02 different ones.
 * - In case of a tie, the one with the highest 03 of a kind card wins;
 * - If it remains, the one with the highest card wins;
 */
TestResult testThreeOfKind(void) {

    int n = -1;
    bool isVerbose = false;
    HandTest tests[CARD_NUM_KING + factorial(CARDS_PER_HAND - 1) + 1];

    // Must fit for any number
    for (int i = 1; i <= CARD_NUM_KING; i++) {
        n++;
        
        // Set numbers for a combination test
        int threeOfKindNumber = i;
        int otherCard1;
        int otherCard2;

        if (threeOfKindNumber > 2) {
            otherCard1 = threeOfKindNumber - 1;
            otherCard2 = threeOfKindNumber - 2;
        } else {
            otherCard1 = threeOfKindNumber + 1;
            otherCard2 = threeOfKindNumber + 2;
        }

        // Build test config
        tests[n].title = "Must fit for card " + to_string(threeOfKindNumber);
        tests[n].isVerbose = isVerbose;
        tests[n].hand = getEmptyHand();
        tests[n].hand.type = HAND_3_KIND;
        tests[n].hand.threeOfKindNumber = threeOfKindNumber;
        
        tests[n].cards[0] = { SUIT_HEARTS, otherCard1 };
        tests[n].cards[1] = { SUIT_CLUBS, otherCard2 };
        tests[n].cards[2] = { SUIT_DIAMONDS, threeOfKindNumber };
        tests[n].cards[3] = { SUIT_SPADES, threeOfKindNumber };
        tests[n].cards[4] = { SUIT_HEARTS, threeOfKindNumber };
    }

    // Must fit three of a kind in any position
    int otherCard1 = 3;
    int otherCard2 = 4;
    int threeOfKindNumber = 5;

    for (int i = 0; i < CARDS_PER_HAND; i++) {
        for (int j = 0; j < CARDS_PER_HAND; j++) {
            
            if (i >= j)
                continue;

            n++;
            tests[n].title = "Must fit for the other two cards at position (" + to_string(i + 1) + "/" + to_string(j + 1) + ")";
            tests[n].isVerbose = isVerbose;
            tests[n].hand = getEmptyHand();
            tests[n].hand.type = HAND_3_KIND;
            tests[n].hand.threeOfKindNumber = threeOfKindNumber;

            for (int k = 0; k < CARDS_PER_HAND; k++) {
                if (k == i)
                    tests[n].cards[k] = { SUIT_HEARTS, otherCard1 };
                else if (k == j)
                    tests[n].cards[k] = { SUIT_CLUBS, otherCard2 };
                else
                    tests[n].cards[k] = { SUIT_DIAMONDS, threeOfKindNumber };
            }
        }   
    }

    // New Test...
    otherCard1 = 5;
    threeOfKindNumber = 1;

    n++;
    tests[n].title = "Must not match as a full house";
    tests[n].isVerbose = isVerbose;
    tests[n].hand = getEmptyHand();
    tests[n].hand.type = HAND_FULL_HOUSE;
    tests[n].hand.threeOfKindNumber = threeOfKindNumber;
    tests[n].hand.pairNumber = otherCard1;
    
    tests[n].cards[0] = { SUIT_HEARTS, otherCard1 };
    tests[n].cards[1] = { SUIT_CLUBS, otherCard1 };
    tests[n].cards[2] = { SUIT_DIAMONDS, threeOfKindNumber };
    tests[n].cards[3] = { SUIT_SPADES, threeOfKindNumber };
    tests[n].cards[4] = { SUIT_HEARTS, threeOfKindNumber };

    return testManyHands(HAND_NAMES[HAND_FULL_HOUSE], tests, n + 1);
}

/**
 * 02 pairs.
 * - In case of a tie, the one with the highest pair card wins;
 * - If it remains, the one with the highest lowest pair card wins;
 * - If it remains, the one with the highest card wins;
 */
TestResult testTwoPairs(void) {

    int n = -1;
    bool isVerbose = false;
    HandTest tests[factorial(CARD_NUM_KING - 1) + 1];

    // Must fit for combinations at any position
    for (int pairNumber1 = 1; pairNumber1 <= CARD_NUM_KING; pairNumber1++) {
        for (int pairNumber2 = 1; pairNumber2 <= CARD_NUM_KING; pairNumber2++) {

            // Set the 03 numbers we're gonna need
            if (pairNumber1 >= pairNumber2)
                continue;

            int otherNumber = 1;
            while (otherNumber == pairNumber1 || otherNumber == pairNumber2)
                otherNumber++;

            // Build test
            n++;

            tests[n].title = "Must fit for pairs of numbers (" + to_string(pairNumber1) + "/" + to_string(pairNumber2) + ")";
            tests[n].isVerbose = isVerbose;
            tests[n].hand = getEmptyHand();
            tests[n].hand.type = HAND_2_PAIRS;
            tests[n].hand.pairNumber = pairNumber1;
            tests[n].hand.pairNumber2 = pairNumber2;

            tests[n].cards[0] = { SUIT_HEARTS, pairNumber1 };
            tests[n].cards[1] = { SUIT_CLUBS, pairNumber2 };
            tests[n].cards[2] = { SUIT_DIAMONDS, otherNumber };
            tests[n].cards[3] = { SUIT_DIAMONDS, pairNumber2 };
            tests[n].cards[4] = { SUIT_SPADES, pairNumber1 };
        }   
    }

    n++;
    int pairNumber1 = 4;
    int threeOfKindNumber = 8;

    tests[n].title = "Must not fit as full house";
    tests[n].isVerbose = isVerbose;
    tests[n].hand = getEmptyHand();
    tests[n].hand.type = HAND_FULL_HOUSE;
    tests[n].hand.pairNumber = pairNumber1;
    tests[n].hand.threeOfKindNumber = threeOfKindNumber;

    tests[n].cards[0] = { SUIT_HEARTS, pairNumber1 };
    tests[n].cards[1] = { SUIT_CLUBS, threeOfKindNumber };
    tests[n].cards[2] = { SUIT_DIAMONDS, threeOfKindNumber };
    tests[n].cards[3] = { SUIT_DIAMONDS, threeOfKindNumber };
    tests[n].cards[4] = { SUIT_SPADES, pairNumber1 };

    return testManyHands(HAND_NAMES[HAND_2_PAIRS], tests, n + 1);
}

/**
 * 01 pair.
 * - In case of a tie, the one with the highest pair card wins;
 * - If it remains, the one with the highest lowest pair card wins;
 * - If it remains, the one with the highest card wins;
 */
TestResult testOnePair(void) {

    int n = -1;
    bool isVerbose = false;
    HandTest tests[CARD_NUM_KING + 2];

    // Must fit for any number
    for (int pairNumber = 1; pairNumber <= CARD_NUM_KING; pairNumber++) {

        // Make the numbers we're gonna need        
        int otherNumber1 = pairNumber < (CARD_NUM_KING - 1) ? pairNumber + 1 : pairNumber - 1;
        int otherNumber2 = pairNumber < (CARD_NUM_KING - 2) ? pairNumber + 2 : pairNumber - 2;
        int otherNumber3 = pairNumber < (CARD_NUM_KING - 3) ? pairNumber + 3 : pairNumber - 3;

        // Build the test
        n++;
        tests[n].title = "Must fit for pair of '" + to_string(pairNumber) + "'";
        tests[n].isVerbose = isVerbose;
        tests[n].hand = getEmptyHand();
        tests[n].hand.type = HAND_PAIR;
        tests[n].hand.pairNumber = pairNumber;

        tests[n].cards[0] = { SUIT_HEARTS, pairNumber };
        tests[n].cards[1] = { SUIT_CLUBS, pairNumber };
        tests[n].cards[2] = { SUIT_DIAMONDS, otherNumber1 };
        tests[n].cards[3] = { SUIT_DIAMONDS, otherNumber2 };
        tests[n].cards[4] = { SUIT_SPADES, otherNumber3 };
    }

    n++;
    int pairNumber = 1;
    int pairNumber2 = 13;
    int otherNumber = 6;

    tests[n].title = "Must not fit as two pairs";
    tests[n].isVerbose = isVerbose;
    tests[n].hand = getEmptyHand();
    tests[n].hand.type = HAND_2_PAIRS;
    tests[n].hand.pairNumber = pairNumber;
    tests[n].hand.pairNumber2 = pairNumber2;

    tests[n].cards[0] = { SUIT_SPADES, pairNumber };
    tests[n].cards[1] = { SUIT_CLUBS, pairNumber2 };
    tests[n].cards[2] = { SUIT_HEARTS, otherNumber };
    tests[n].cards[3] = { SUIT_DIAMONDS, pairNumber2 };
    tests[n].cards[4] = { SUIT_SPADES, pairNumber };

    n++;
    pairNumber = 1;
    int threeOfKindNumber = 13;

    tests[n].title = "Must not fit as full house";
    tests[n].isVerbose = isVerbose;
    tests[n].hand = getEmptyHand();
    tests[n].hand.type = HAND_FULL_HOUSE;
    tests[n].hand.pairNumber = pairNumber;
    tests[n].hand.threeOfKindNumber = threeOfKindNumber;

    tests[n].cards[0] = { SUIT_SPADES, pairNumber };
    tests[n].cards[1] = { SUIT_CLUBS, threeOfKindNumber };
    tests[n].cards[2] = { SUIT_HEARTS, threeOfKindNumber };
    tests[n].cards[3] = { SUIT_DIAMONDS, threeOfKindNumber };
    tests[n].cards[4] = { SUIT_SPADES, pairNumber };

    return testManyHands(HAND_NAMES[HAND_PAIR], tests, n + 1);
}

int main() {

    // Notify tests start
    std::cout << endl
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

    nGroups++;
    aux = testFullHouse();
    acc.nTests += aux.nTests;
    acc.nFailures += aux.nFailures;

    nGroups++;
    aux = testFlush();
    acc.nTests += aux.nTests;
    acc.nFailures += aux.nFailures;

    nGroups++;
    aux = testStraight();
    acc.nTests += aux.nTests;
    acc.nFailures += aux.nFailures;

    nGroups++;
    aux = testThreeOfKind();
    acc.nTests += aux.nTests;
    acc.nFailures += aux.nFailures;

    nGroups++;
    aux = testTwoPairs();
    acc.nTests += aux.nTests;
    acc.nFailures += aux.nFailures;

    nGroups++;
    aux = testOnePair();
    acc.nTests += aux.nTests;
    acc.nFailures += aux.nFailures;

    // Notify end result
    bool isSuccess = acc.nFailures == 0;
    std::cout << endl << "<< ---------------------------------------------------------------------------- <<" << endl;

    if (isSuccess)
        std::cout << "<<<< All tests passed! >>> <<<< All tests passed!! >>>> <<< All tests passed! >>>>" << endl;
    else
        std::cout << "<<<<--- TESTS FAILED --->>> <<<--- TESTS FAILED --->>> <<<--- TESTS FAILED --->>>>" << endl;
    
    std::cout << "<< ---------------------------------------------------------------------------- <<" << endl
        << endl
        << ">> " << to_string(nGroups) << " test group(s);" << endl
        << ">> " << to_string(acc.nTests) << " unit test(s);" << endl
        << ">> " << to_string(acc.nFailures) << " error(s); " << endl
        << endl;

    return EXIT_SUCCESS;
}
