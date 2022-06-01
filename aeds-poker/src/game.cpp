#include <stdlib.h>
#include <memory>
#include <sstream>

#include "../include/game.h"
#include "../include/debug.h"

Play readPlay(ifstream &inputStream) {

    string aux;
    string line;
    getline(inputStream, line);
    stringstream lineStream(line);

    Play play;
    getline(lineStream, play.playerName, ' ');
    getline(lineStream, aux, ' ');
    play.bid = stoi(aux);

    for (int i = 0; i < CARDS_COUNT; i++) {
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