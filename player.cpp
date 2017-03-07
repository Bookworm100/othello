#include "player.hpp"

//This is a test commit

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    board = new Board();

    AI = side;
    if (AI == WHITE)
    {
        opponent = BLACK;
    }
    else
    {
        opponent = WHITE;
    }

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    std::cerr << "1" << std::endl;
    board->doMove(opponentsMove, opponent);
    std::cerr << "2" << std::endl;
    Move * move = minimax();
    return move;
    
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
}

/*
 *
 * Returns the first valid move the AI finds
 *
 */
Move *Player::firstMove()
{
    if (board->hasMoves(AI) == false)
    {
        return nullptr; //There are no available valid moves!
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move *move = new Move(i, j);
            if (board->checkMove(move, AI) == true)
            {
                board->doMove(move, AI);
                return move;
            }
            delete move;
        }
    }
}


Move *Player::simpleMove()
{
    std::cerr << "3" << std::endl;
    if (board->hasMoves(AI) == false)
    {
        return nullptr;
    }
    int best_score = -10000;
    Move *best_move = nullptr;
    std::cerr << "4" << std::endl;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            std::cerr << "5" << std::endl;
            Move *move = new Move(i, j);
            if (board->checkMove(move, AI) == true)
            {
                int score = simpleScore(move);
                if (score > best_score)
                {
                    delete best_move;
                    best_move = move;
                    best_score = score;
                }
                else
                {
                    delete move;
                }
            }
            else
            {
            std::cerr << "6" << std::endl;
                delete move;
            }
        }
    }
    std::cerr << "7" << std::endl;
    std::cerr << "x: " << best_move->getX() << std::endl;
    std::cerr << "y: " << best_move->getY() << std::endl;
    board->doMove(best_move, AI);
    return best_move;
}

int Player::simpleScore(Move *move)
{
    Board *copy = board->copy();
    copy->doMove(move, AI);
    int score (copy->count(AI) - copy->count(opponent));

    if (copy->get(AI,0,0)) score += 3;
    if (copy->get(AI,0,7)) score += 3;
    if (copy->get(AI,7,0)) score += 3;
    if (copy->get(AI,7,7)) score += 3;
    if (copy->get(AI,1,1)) score -= 5;
    if (copy->get(AI,1,6)) score -= 5;
    if (copy->get(AI,6,1)) score -= 5;
    if (copy->get(AI,6,6)) score -= 5;
    for (int i = 2; i < 6; i++)
    {
        if (copy->get(AI,i,0)) score += 1;
        if (copy->get(AI,0,i)) score += 1;
        if (copy->get(AI,7,i)) score += 1;
        if (copy->get(AI,i,7)) score += 1;
    }
    if (copy->get(AI,0,1)) score -= 3;
    if (copy->get(AI,1,0)) score -= 3;
    if (copy->get(AI,0,6)) score -= 3;
    if (copy->get(AI,6,0)) score -= 3;
    if (copy->get(AI,1,7)) score -= 3;
    if (copy->get(AI,7,1)) score -= 3;
    if (copy->get(AI,1,0)) score -= 3;
    if (copy->get(AI,6,7)) score -= 3;
    if (copy->get(AI,7,6)) score -= 3;

    return score;
}

Move *Player::minimax()
{
    std::cerr << "3" << std::endl;
    if (board->hasMoves(AI) == false)
    {
        return nullptr;
    }
    int best_score = -10000;
    Move *best_move = nullptr;
    std::cerr << "4" << std::endl;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            std::cerr << "5" << std::endl;
            Move *move = new Move(i, j);
            if (board->checkMove(move, AI) == true)
            {
                int score = minimaxScore(move);
                if (score > best_score)
                {
            std::cerr << "6" << std::endl;
                    delete best_move;
                    best_move = move;
                    best_score = score;
                }
                else
                {
                    delete move;
                }
            }
            else
            {
            std::cerr << "7" << std::endl;
                delete move;
            }
        }
    }
    std::cerr << "8" << std::endl;
    std::cerr << "x: " << best_move->getX() << std::endl;
    std::cerr << "y: " << best_move->getY() << std::endl;
    board->doMove(best_move, AI);
    return best_move;
}

int Player::minimaxScore(Move *move)
{
    int worst_score = 10000;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            std::cerr << "9" << std::endl;
            Board *copy = board->copy();
            copy->doMove(move, AI);
            Move *opp_move = new Move(i, j);
            if (copy->checkMove(opp_move, opponent) == true)
            {
            std::cerr << "10" << std::endl;
                copy->doMove(opp_move, opponent);
                int score = (copy->count(AI) - copy->count(opponent));
                if (score < worst_score)
                {
                    worst_score = score;
                }
            }
            delete opp_move;
        }
    }
    return worst_score;
}

