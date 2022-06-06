#include <stdlib.h>
#include <string.h>
#include <memory>
#include <sstream>

#include "../include/game.h"
#include "../include/debug.h"

/**
 * ------------------------------------------------
 * == HAND PARSING HELPERS ========================
 * ------------------------------------------------
 */

bool isValidCardNumber(const int number) {
    return number >= CARD_NUM_ACE && number <= CARD_NUM_KING;
}

bool isValidSuit(const char suit) {
    for (int i = 0; i < SUITS_COUNT; i++) {
        if (suit == SUITS_LIST[i])
            return true;
    }
    return false;
}

bool isSequence(const Card cards[CARDS_PER_HAND]) {
    
    for (int i = 1; i < CARDS_PER_HAND; i++) {

        int prevNumber = cards[i - 1].number;
        int currentNumber = cards[i].number;
        
        bool isValidNumber = (
            (prevNumber != CARD_NUM_KING && currentNumber == (prevNumber + 1))
            || (prevNumber == CARD_NUM_KING && currentNumber == CARD_NUM_ACE) // Considers the ace as the last card
        );
        
        if (!isValidNumber)
            return false;
    }

    return true;
}

bool isSameSuit(const Card cards[CARDS_PER_HAND], char *suit) {

    if (suit == NULL)
        suit = (char*)malloc(sizeof(char));
    
    *suit = cards[0].suit;
    for (int i = 1; i < CARDS_PER_HAND; i++) {
        if (cards[i].suit != *suit)
            return false;
    }

    return true;
}

void sortCards(Card cards[CARDS_PER_HAND]) {
    
    // Do the regular sort
    for (int i = 0; i < CARDS_PER_HAND; i++) {
        for (int j = 1; j < CARDS_PER_HAND; j++) {
            Card prev = cards[j - 1];
            Card current = cards[j];
            if (current.number < prev.number) {
                cards[j - 1] = current;
                cards[j] = prev;
            }
        }
    }

    // Handle ace conditional position
    int lastIdx = CARDS_PER_HAND - 1;
    bool isAceSpecialCase = cards[lastIdx].number == CARD_NUM_KING && cards[0].number == CARD_NUM_ACE;
    if (!isAceSpecialCase)
        return;

    Card ace = cards[0];

    for (int i = 1; i < CARDS_PER_HAND; i++) {
        Card prev = cards[i - 1];
        Card current = cards[i];
        cards[i - 1] = current;
        cards[i] = prev;
    }

    cards[lastIdx] = ace;
}

int getHandScore(const Hand hand) {
    return (
        hand.type
        + 5*hand.fourOfKindNumber
        + 4*hand.threeOfKindNumber
        + 3*hand.pairNumber
        + 2*hand.pairNumber2
        + 1*hand.highest
    );
}

void countCards(const Card cards[CARDS_PER_HAND], int counts[CARDS_PER_SUIT]) {
    for (int i = 0; i < CARDS_PER_HAND; i++)
        counts[cards[i].number - 1]++;
}

/**
 * TODO: 2022-06-03 - Check if we really need the suit
 */
bool hasNOfAKind(const int n, const Card cards[CARDS_PER_HAND], int *matchedNumber, char *matchedSuit, int counts[CARDS_PER_SUIT]) {

    // Set each number occurrences count
    if (counts == NULL)
        counts = (int*)malloc(CARDS_PER_SUIT * sizeof(int));
    memset(counts, 0, CARDS_PER_SUIT * sizeof(int));
    countCards(cards, counts);

    // Check if we have the exact counting we're looking for
    if (matchedNumber == NULL)
        matchedNumber = (int*)malloc(sizeof(int));
    *matchedNumber = 0;

    if (matchedSuit == NULL)
        matchedSuit = (char*)malloc(sizeof(char));
    *matchedSuit = ' ';

    int bestCount = 0;
    for (int i = 0; i < CARDS_PER_HAND; i++) {

        if (!isValidCardNumber(cards[i].number))
            continue;

        int thisCount = counts[cards[i].number - 1];
        if (thisCount > bestCount) {
            bestCount = thisCount;
            *matchedSuit = cards[i].suit;
            *matchedNumber = cards[i].number;
        }
    }

    return bestCount == n;
}

void removeCardFromHand(Card cards[CARDS_PER_HAND], const int numberToRemove) {
    for (int i = 0; i < CARDS_PER_HAND; i++) {
        if (cards[i].number == numberToRemove)
            cards[i].number = 0;
    }
}

Hand getEmptyHand(void) {
    return { HAND_HIGHER_CARD, ' ', 0, 0, 0, 0, 0, 0 };
}

Hand getHand(const Card handCards[CARDS_PER_HAND]) {

    // Validate
    for (int i = 0; i < CARDS_PER_HAND; i++) {
        Card card = handCards[i];
        
        if (!isValidCardNumber(card.number))
            throw range_error("Invalid card number: " + to_string(card.number));
        
        if (!isValidSuit(card.suit)) {
            string aux;
            throw range_error("Invalid card suit: " + (aux + card.suit));
        }
    }

    // Make a sorted copy of provided cards
    Card cards[CARDS_PER_HAND];
    memcpy(cards, handCards, CARDS_PER_HAND * sizeof(Card));
    sortCards(cards);

    // Detect hand
    bool haveMatch = false;
    Hand hand = getEmptyHand();
    
    char suit;
    int pairNumber = 0;
    int pairNumber2 = 0;
    int fourOfKindNumber = 0;
    int threeOfKindNumber = 0;

    if (!haveMatch) {
        HandEnum type = HAND_ROYAL_STRAIGHT_FLUSH;
        dbgStep("Parsing hand for being: " + HAND_NAMES[type] + "...");
        if (isRoyalStraightFlush(cards, &suit)) {
            haveMatch = true;
            hand.type = type;
            hand.suit = suit;
        }
    }

    if (!haveMatch) {
        HandEnum type = HAND_STRAIGHT_FLUSH;
        dbgStep("Parsing hand for being: " + HAND_NAMES[type] + "...");
        if (isStraightFlush(cards, &suit)) {
            haveMatch = true;
            hand.type = type;
            hand.suit = suit;
        }
    }

    if (!haveMatch) {
        HandEnum type = HAND_4_KIND;
        dbgStep("Parsing hand for being: " + HAND_NAMES[type] + "...");
        if (isFourOfKind(cards, &fourOfKindNumber)) {
            haveMatch = true;
            hand.type =  type;
            hand.fourOfKindNumber =  fourOfKindNumber;
        }
    }

    if (!haveMatch) {
        HandEnum type = HAND_FULL_HOUSE;
        dbgStep("Parsing hand for being: " + HAND_NAMES[type] + "...");
        if (isFullHouse(cards, &threeOfKindNumber, &pairNumber)) {
            haveMatch = true;
            hand.type = type;
            hand.pairNumber =  pairNumber;
            hand.threeOfKindNumber =  threeOfKindNumber;
        }
    }

    if (!haveMatch) {
        HandEnum type = HAND_FLUSH;
        dbgStep("Parsing hand for being: " + HAND_NAMES[type] + "...");
        if (isFlush(cards, &suit)) {
            haveMatch = true;
            hand.type = type;
            hand.suit = suit;
        }
    }

    if (!haveMatch) {
        HandEnum type = HAND_STRAIGHT;
        dbgStep("Parsing hand for being: " + HAND_NAMES[type] + "...");
        if (isStraight(cards)) {
            haveMatch = true;
            hand.type = type;
        }
    }

    if (!haveMatch) {
        HandEnum type = HAND_3_KIND;
        dbgStep("Parsing hand for being: " + HAND_NAMES[type] + "...");
        if (isThreeOfKind(cards, &threeOfKindNumber)) {
            haveMatch = true;
            hand.type = type;
            hand.threeOfKindNumber = threeOfKindNumber;
        }
    }

    if (!haveMatch) {
        HandEnum type = HAND_2_PAIRS;
        dbgStep("Parsing hand for being: " + HAND_NAMES[type] + "...");
        if (isTwoPairs(cards, &pairNumber, &pairNumber2)) {
            haveMatch = true;
            hand.type = type;
            hand.pairNumber = pairNumber;
            hand.pairNumber2 = pairNumber2;
        }
    }

    if (!haveMatch) {
        HandEnum type = HAND_PAIR;
        dbgStep("Parsing hand for being: " + HAND_NAMES[type] + "...");
        if (isOnePair(cards, &pairNumber)) {
            haveMatch = true;
            hand.type = type;
            hand.pairNumber = pairNumber;
        }
    }

    dbgStep("Hand match: " + HAND_NAMES[hand.type] + "!");
    hand.score = getHandScore(hand);
    return hand;
}

/**
 * ------------------------------------------------
 * == HAND PARSERS ================================
 * ------------------------------------------------
 */

/** 05 cards of the same suit in row counting from 10 to Ace. */
bool isRoyalStraightFlush(const Card cards[CARDS_PER_HAND], char *suit) {
    int firstNumber = cards[0].number;
    return firstNumber == 10 && isSameSuit(cards, suit) && isSequence(cards);
}

/** 05 cards of the same suit in a row NOT counting from 10 to Ace (!= RSF). */
bool isStraightFlush(const Card cards[CARDS_PER_HAND], char *suit) {
    /**
     * NOTE: 1st number >= 10 would be Royal straight flush or nothing at all...
     */
    int firstNumber = cards[0].number;
    return firstNumber < 10 && isSameSuit(cards, suit) && isSequence(cards);
}

/**
 * 04 equal cards.
 * - In case of a tie the higher number hand wins;
 * - If it remains tied the one with the higher fifth card wins;
 */
bool isFourOfKind(const Card cards[CARDS_PER_HAND], int *fourOfKindNumber) {
    bool isHigherHand =  isRoyalStraightFlush(cards, NULL) || isStraightFlush(cards, NULL);
    return !isHigherHand && hasNOfAKind(4, cards, fourOfKindNumber, NULL, NULL);
}

/**
 * 01 pair + 03 of a kind.
 * - In case of a tie, the higher 03 of a kind wins;
 * - If it remains tied, the higher pair wins;
 */
bool isFullHouse(const Card cards[CARDS_PER_HAND], int *threeOfKindNumber, int *pairNumber) {

    bool isHigherHand = (
        isRoyalStraightFlush(cards, NULL)
        || isStraightFlush(cards, NULL)
        || isFourOfKind(cards, NULL)
    );

    if (isHigherHand)
        return false;

    // Check the 03 of a kind part
    if (threeOfKindNumber == NULL)
        threeOfKindNumber = (int*)malloc(sizeof(int));

    int counts[CARDS_PER_SUIT] = { 0 };
    if (!hasNOfAKind(3, cards, threeOfKindNumber, NULL, counts))
        return false;

    // Check the pair part
    Card cardsCopy[CARDS_PER_HAND];
    memcpy(cardsCopy, cards, CARDS_PER_HAND * sizeof(Card));
    removeCardFromHand(cardsCopy, *threeOfKindNumber);

    return hasNOfAKind(2, cardsCopy, pairNumber, NULL, NULL);
}

/**
 * 05 cards of the same suit (without being in a row).
 * - In case of a tie the one with the highest card wins;
 */
bool isFlush(const Card cards[CARDS_PER_HAND], char *suit) {

    bool isHigherHand = (
        isRoyalStraightFlush(cards, NULL)
        || isStraightFlush(cards, NULL)
        || isFourOfKind(cards, NULL)
        || isFullHouse(cards, NULL, NULL)
    );

    return !isHigherHand && isSameSuit(cards, suit);
}

/**
 * 05 cards in a row not caring about the suit.
 * - In case of a tie, the one with highest card wins;
 */
bool isStraight(const Card cards[CARDS_PER_HAND]) {

    bool isHigherHand = (
        isRoyalStraightFlush(cards, NULL)
        || isStraightFlush(cards, NULL)
        || isFourOfKind(cards, NULL)
        || isFullHouse(cards, NULL, NULL)
        || isFlush(cards, NULL)
    );

    return !isHigherHand && isSequence(cards);
}

/**
 * 03 equal cards + 02 different ones.
 * - In case of a tie, the one with the highest 03 of a kind card wins;
 * - If it remains, the one with the highest card wins;
 */
bool isThreeOfKind(const Card cards[CARDS_PER_HAND], int *threeOfKindNumber) {

    bool isHigherHand = (
        isRoyalStraightFlush(cards, NULL)
        || isStraightFlush(cards, NULL)
        || isFourOfKind(cards, NULL)
        || isFullHouse(cards, NULL, NULL)
        || isFlush(cards, NULL)
        || isStraight(cards)
    );

    return !isHigherHand && hasNOfAKind(3, cards, threeOfKindNumber, NULL, NULL);
}

/**
 * 02 pairs.
 * - In case of a tie, the one with the highest pair card wins;
 * - If it remains, the one with the highest lowest pair card wins;
 * - If it remains, the one with the highest card wins;
 */
bool isTwoPairs(const Card cards[CARDS_PER_HAND], int *pairNumber, int *pairNumber2) {

    bool isHigherHand = (
        isRoyalStraightFlush(cards, NULL)
        || isStraightFlush(cards, NULL)
        || isFourOfKind(cards, NULL)
        || isFullHouse(cards, NULL, NULL)
        || isFlush(cards, NULL)
        || isStraight(cards)
        || isThreeOfKind(cards, NULL)
    );

    if (isHigherHand)
        return false;
    
    // Check if we have any pairs
    int counts[CARDS_PER_SUIT] = { 0 };
    if (pairNumber == NULL)
        pairNumber = (int*)malloc(sizeof(int));

    if (!hasNOfAKind(2, cards, pairNumber, NULL, counts))
        return false;
    
    // Check the pair part
    Card cardsCopy[CARDS_PER_HAND];
    memcpy(cardsCopy, cards, CARDS_PER_HAND * sizeof(Card));
    removeCardFromHand(cardsCopy, *pairNumber);
    
    return hasNOfAKind(2, cardsCopy, pairNumber2, NULL, NULL);
}

/**
 * 01 pair.
 * - In case of a tie, the one with the highest pair card wins;
 * - If it remains, the one with the highest lowest pair card wins;
 * - If it remains, the one with the highest card wins;
 */
bool isOnePair(const Card cards[CARDS_PER_HAND], int *pairCard) {

    bool isHigherHand = (
        isRoyalStraightFlush(cards, NULL)
        || isStraightFlush(cards, NULL)
        || isFourOfKind(cards, NULL)
        || isFullHouse(cards, NULL, NULL)
        || isFlush(cards, NULL)
        || isStraight(cards)
        || isThreeOfKind(cards, NULL)
        || isTwoPairs(cards, NULL, NULL)
    );

    return !isHigherHand && hasNOfAKind(2, cards, pairCard, NULL, NULL);
}

/**
 * ------------------------------------------------
 * == INPUT PARSERS ===============================
 * ------------------------------------------------
 */

Play readPlay(ifstream &inputStream) {

    string aux;
    string line;
    getline(inputStream, line);
    stringstream lineStream(line);

    Play play;
    getline(lineStream, play.playerName, ' ');
    getline(lineStream, aux, ' ');
    play.bid = stoi(aux);

    for (int i = 0; i < CARDS_PER_HAND; i++) {
        getline(lineStream, aux, ' ');
        play.cards[i].suit = aux[aux.length() - 1];
        play.cards[i].number = stoi(aux.substr(0, aux.length() - 1));
    }
    
    return play;
}

Round readRound(ifstream &inputStream) {

    string aux;
    string line;
    getline(inputStream, line);
    stringstream lineStream(line);

    // Read round parameters
    Round round;
    getline(lineStream, aux, ' ');
    round.nPlays = stoi(aux);
    getline(lineStream, aux, ' ');
    round.blind = stoi(aux);

    // Read round plays
    round.plays = (Play*)malloc(round.nPlays * sizeof(Play));
    for (int i = 0; i < round.nPlays; i++) {
        Play play = readPlay(inputStream);
        round.plays[i] = play;
    }
    
    return round;
}

Game readGame(ifstream &inputStream) {

    string aux;
    string line;
    getline(inputStream, line);
    stringstream lineStream(line);

    // Read game parameters
    Game game;
    getline(lineStream, aux, ' ');
    game.nRounds = stoi(aux);
    getline(lineStream, aux, ' ');
    game.initialAmount = stoi(aux);

    // Read rounds
    game.rounds = (Round*)malloc(game.nRounds * sizeof(Round));
    for (int i = 0; i < game.nRounds; i++)
        game.rounds[i] = readRound(inputStream);

    return game;
}