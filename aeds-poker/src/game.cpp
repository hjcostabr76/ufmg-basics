#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <memory>
#include <sstream>
#include <fstream>

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

void sortPlayers(Player *players, const int nPlayers) {
    for (int i = 0; i < nPlayers; i++) {
        for (int j = 1; j < nPlayers; j++) {
            Player prev = players[j - 1];
            Player current = players[j];
            if (current.money > prev.money) {
                players[j - 1] = current;
                players[j] = prev;
            }
        }
    }
}

void sortPlays(Play *plays, const int nPlays) {
    for (int i = 0; i < nPlays; i++) {
        for (int j = 1; j < nPlays; j++) {
            Play prev = plays[j - 1];
            Play current = plays[j];
            if (current.hand.score > prev.hand.score) {
                plays[j - 1] = current;
                plays[j] = prev;
            }
        }
    }
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

    int score = (
        20*hand.type
        + 10*hand.fourOfKindNumber
        + 5*hand.threeOfKindNumber
        + 2*hand.pairNumber
        + 2*hand.pairNumber2
    );

    score += hand.highest == CARD_NUM_ACE ? CARD_NUM_KING + 1 : hand.highest;
    return score;
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

    Hand hand;
    
    hand.type = HAND_HIGHER_CARD;
    hand.suit = ' ';
    hand.fourOfKindNumber = 0;
    hand.threeOfKindNumber = 0;
    hand.pairNumber = 0;
    hand.pairNumber2 = 0;
    hand.score = 0;
    hand.highest = 0;

    hand.cards[0] = { ' ', 0 };
    hand.cards[1] = { ' ', 0 };
    hand.cards[2] = { ' ', 0 };
    hand.cards[3] = { ' ', 0 };
    hand.cards[4] = { ' ', 0 };
    
    return hand;
}

int getHighestCard(Card cards[CARDS_PER_HAND]) {
    int highest = 0;
    for (int i = 0; i < CARDS_PER_HAND; i++) {
        if (cards[i].number == CARD_NUM_ACE)
            return CARD_NUM_ACE;
        if (cards[i].number > highest)
            highest = cards[i].number;
    }
    return highest;
}

int findPlayerPosition(Player players[], const string name, const int nPlayers) {
    for (int j = 0; j < nPlayers; j++) {
        bool isMatch = name.compare(players[j].name) == 0;
        if (isMatch)
            return j;
    }
    return -1;
}

void readGamePlayers(Game &game) {
    game.nPlayers = 0;

    // Search for players among game rounds
    for (int i = 0; i < game.nRounds; i++) {
        Round round = game.rounds[i];
        
        // Search for players among round plays
        for (int j = 0; j < round.nPlays; j++) {
            Play play = round.plays[j];
            
            // Check if we already know this one
            bool isMatch = false;
            for (int k = 0; k < game.nPlayers; k++) {
                isMatch = play.playerName.compare(game.players[k].name) == 0;
                if (isMatch)
                    break;
            }

            if (isMatch)
                continue;
            
            if (game.nPlayers >= MAX_PLAYERS)
                throw runtime_error("Max players reached");

            // Add new found player
            game.players[game.nPlayers].money = game.initialAmount;
            game.players[game.nPlayers].name = play.playerName;
            game.nPlayers = game.nPlayers + 1;
        }
    }
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
 * == Game actions ================================
 * ------------------------------------------------
 */

void detectHand(Hand &hand) {

    // Validate
    for (int i = 0; i < CARDS_PER_HAND; i++) {
        Card card = hand.cards[i];
        
        if (!isValidCardNumber(card.number))
            throw range_error("Invalid card number: " + to_string(card.number));
        
        if (!isValidSuit(card.suit)) {
            string aux;
            throw range_error("Invalid card suit: " + (aux + card.suit));
        }
    }

    // Make a sorted copy of provided cards
    Card cards[CARDS_PER_HAND];
    memcpy(cards, hand.cards, CARDS_PER_HAND * sizeof(Card));
    sortCards(cards);

    // Detect hand
    bool haveMatch = false;
    
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

    hand.highest = getHighestCard(cards);
    hand.score = getHandScore(hand);
    
    dbgStep("Hand match: " + HAND_NAMES[hand.type] + "! ( highest: " + to_string(hand.highest) + " / score: " + to_string(hand.score) + ")");
}

void parseRound(Round &round, Player* players, const int nPlayers) {
    
    int nBrokePLayers = 0;
    string *brokePlayerNames = (string*)malloc(nPlayers * BUF_SIZE);

    // Compute the round pot (all players contribute)
    for (int i = 0; i < nPlayers; i++) {
        bool canAfford = players[i].money >= round.blind;
        if (canAfford) {
            players[i].money -= round.blind;
            round.pot += round.blind;
        } else {
            nBrokePLayers++;
            brokePlayerNames[nBrokePLayers] = players[i].name;
        }
    }

    // Compute all plays
    for (int i = 0; i < round.nPlays; i++) {

        Play *play = &round.plays[i];

        // Determine player
        int pos = findPlayerPosition(players, play->playerName, nPlayers);
        if (pos == -1)
            throw runtime_error("Couldn't find player named '" + play->playerName + "'");
        
        Player *player = &players[pos];

        // Check if player can afford it
        bool isBroke = false;
        for (int j = 0; j < nBrokePLayers; j++)
            isBroke = brokePlayerNames[j].compare(player->name) == 0;
        
        isBroke = isBroke || player->money < play->bid;
        if (isBroke)
            throw range_error("'" + player->name + "' couldn't afford to play...");

        if (play->bid <= 0 || play->bid % BID_BASE_VALUE != 0)
            throw invalid_argument("Bid has to be a positive multiple of 50 ('" + to_string(play->bid) +"' received)");

        // Compute this play
        detectHand(play->hand);
        player->money -= play->bid;
        round.pot += play->bid;
    }

    // Determine winner(s)
    sortPlays(round.plays, round.nPlays);

    int i = 0;
    round.nWinners = 1;
    round.winningHand = round.plays[0].hand.type;

    while (round.plays[i].hand.score == round.plays[i + 1].hand.score && (i + 1) < round.nPlays) {
        round.nWinners++;
        i++;
    }
    
    round.prize = round.pot / round.nWinners;
    // cout << endl << "prize: '" << to_string(prize) << "'" << endl;
    round.winners = (string*)malloc(round.nWinners * BUF_SIZE);

    // Add the prize into the winners account
    for (int i = 0; i < round.nWinners; i++) {

        int pos = findPlayerPosition(players, round.plays[i].playerName, nPlayers);
        if (pos == -1)
            throw runtime_error("Couldn't find player named '" + round.plays[i].playerName + "'");

        round.winners[i] = round.plays[i].playerName;
        Player *winner = &players[pos];
        winner->money += round.prize;
        // dbgPrintPlayer(*winner);
    }
}

void consolidateRounds(Game &game) {
    for (int i = 0; i < game.nRounds; i++) {
        try {
            Round *round = &game.rounds[i];
            parseRound(*round, game.players, game.nPlayers);

            int totalMoney = 0;
            for (int j = 0; j < game.nPlayers; j++)
                totalMoney += game.players[j].money;
            dbgStep("Money after round " + to_string(i + 1) + ": " + to_string(totalMoney));

        } catch (range_error &error) {
            dbgStep("Round '" + to_string(i + 1) + "' won't be computed because of sanity verification failure...");
        }
    }
}

void writeResult(const Game game, ofstream &outFile) { 

    // Write each round result
    for (int i = 0; i < game.nRounds; i++) {
        Round round = game.rounds[i];
        
        // Summary
        outFile << to_string(round.nWinners)
            << " " << to_string(round.prize)
            << " " << HAND_CODES[round.winningHand]
            << endl;

        // Winner(s)
        for (int j = 0; j < round.nWinners; j++)
            outFile << round.winners[j] << endl;
    }

    // Write players final balance
    outFile << "####" << endl;

    for (int i = 0; i < game.nPlayers; i++) {
        Player player = game.players[i];
        outFile << player.name << " " << to_string(player.money) << endl;
    }
}

/**
 * ------------------------------------------------
 * == INPUT PARSERS ===============================
 * ------------------------------------------------
 */

Play readPlay(ifstream &inputStream) {

    // Extract line tokens
    const int maxTokens = 10;
    string tokens[maxTokens];
    
    string line;
    getline(inputStream, line);
    stringstream lineStream(line);

    string token;
    int nTokens = 0;
    while (getline(lineStream, token, ' ')) {
        tokens[nTokens] = token;
        nTokens++;
        if (nTokens > maxTokens)
            break;
    }

    // Pick player name
    Play play;
    play.playerName = "";
    for (int i = 0; i < nTokens - CARDS_PER_HAND - 1; i++) {
        if (play.playerName.size())
            play.playerName += " ";
        play.playerName += tokens[i];
    }

    // Pick play bid
    string bid = tokens[nTokens - CARDS_PER_HAND - 1];
    play.bid = stoi(bid);
    
    // Pick play cards
    play.hand = getEmptyHand();
    for (int i = 0; i < CARDS_PER_HAND; i++) {
        token = tokens[nTokens - CARDS_PER_HAND + i];
        play.hand.cards[i].suit = token[token.length() - 1];
        play.hand.cards[i].number = stoi(token.substr(0, token.length() - 1));
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
    round.nWinners = 0;
    round.pot = 0;
    round.prize = 0;
    round.winningHand = HAND_HIGHER_CARD;

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
    game.nPlayers = 0;
    game.players = (Player*)malloc(MAX_PLAYERS * sizeof(Player));

    getline(lineStream, aux, ' ');
    game.nRounds = stoi(aux);
    getline(lineStream, aux, ' ');
    game.initialAmount = stoi(aux);

    // Read rounds
    game.rounds = (Round*)malloc(game.nRounds * sizeof(Round));
    for (int i = 0; i < game.nRounds; i++)
        game.rounds[i] = readRound(inputStream);

    readGamePlayers(game);
    return game;
}