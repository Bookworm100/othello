#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    Side AI;
    Side opponent;
    Board *board;

    Move *doMove(Move *opponentsMove, int msLeft);
    Move *firstMove();
    Move *simpleMove();
    Move *minimax();
    int simpleScore(Board *copy);
    int minimaxScore(Move *move);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
