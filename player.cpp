//This is a test commit

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
#include "player.hpp"
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
    
    board->doMove(opponentsMove, opponent); //Updates board
    Move *move;
    move = minimax();
    return move;
    
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
            if (board->checkMove(move, AI) == true) //Is this a possible move?
            {
                board->doMove(move, AI); //Does the first available move that can be found
                return move;
            }
            delete move;
        }
    }
}

/*
 *
 * Implements the heuristic algorithm
 *
 */
/*
Move *Player::simpleMove()
{
   
    if (board->hasMoves(AI) == false) //There are no available valid moves!
    {
        return nullptr;
    }
    int best_score = -10000; //Initialize best score and best move variables
    Move *best_move = nullptr;
    
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++) //Loop through each possible set of coordinates
        {
            
            Move *move = new Move(i, j); 
            if (board->checkMove(move, AI) == true) //Check if each possible move is valid
            {
                int score = simpleScore(move); //Get the score of the move
                if (score > best_score) //If it's the current highest score
                {
                    delete best_move; //Get rid of the previous best move
                    best_move = move; //Now the best move is the current move
                    best_score = score; //Now the best score is the current score
                }
                else
                {
                    delete move; //Otherwise free the memory allocated to the move!
                }
            }
            else
            {
            
                delete move; 
            }
        }
    }
   
    board->doMove(best_move, AI); //Do this move
    return best_move;
}
*/
/*
 *
 * Helper function for the heuristic algorithm
 *
 */
int Player::simpleScore(Board *copy)
{
//    Board *copy = board->copy();
//    copy->doMove(move, AI);
    int score;
//    if (player == AI)
//    {
        score = (copy->count(AI) - copy->count(opponent));
//    }
//    else
//    {
//        score = (copy->count(opponent) - copy->count(AI));

    if (copy->get(AI,0,0)) score += 3; //If corner
    if (copy->get(AI,0,7)) score += 3;
    if (copy->get(AI,7,0)) score += 3;
    if (copy->get(AI,7,7)) score += 3;
    if (copy->get(AI,1,1)) score -= 5; //If diagonally adjacent to corner
    if (copy->get(AI,1,6)) score -= 5;
    if (copy->get(AI,6,1)) score -= 5;
    if (copy->get(AI,6,6)) score -= 5;
    for (int i = 2; i < 6; i++) //If edge
    {
        if (copy->get(AI,i,0)) score += 1; 
        if (copy->get(AI,0,i)) score += 1;
        if (copy->get(AI,7,i)) score += 1;
        if (copy->get(AI,i,7)) score += 1;
    }
    if (copy->get(AI,0,1)) score -= 3; //If next to corner but not diagonal from it
    if (copy->get(AI,1,0)) score -= 3;
    if (copy->get(AI,0,6)) score -= 3;
    if (copy->get(AI,6,0)) score -= 3;
    if (copy->get(AI,1,7)) score -= 3;
    if (copy->get(AI,7,1)) score -= 3;
    if (copy->get(AI,6,7)) score -= 3;
    if (copy->get(AI,7,6)) score -= 3;

    return score;
}

/*
 *
 * Implements the minimax algorithm
 *
 */
Move *Player::minimax()
{
    
    if (board->hasMoves(AI) == false) //If there are no available valid moves!
    {
        return nullptr;
    }
    int best_score = -10000; //Initialize best score and best move variables
    Move *best_move = nullptr;
    
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            
            Move *move = new Move(i, j); //Check each move
            if (board->checkMove(move, AI) == true) //If the move is valid, find its score!
            {
                int score = minimaxScore(move);
                if (score >= best_score) //If we got a better score
                {
            
                    
                    delete best_move; //Get rid of the previous best move
                    best_move = move; //Now best move is the current move
                    best_score = score; //Now the best score is the current score
                }
                else
                {
                    delete move; //Free the memory associated with this move!
                }
            }
            else
            {
            
                delete move;
            }
        }
    }
    

    board->doMove(best_move, AI); //Make the move
    return best_move;
}

/*
 *
 * Helper function for the minimax algorithm
 *
 */
int Player::minimaxScore(Move *move)
{
    int worst_score = 10000; //Initialize the worst score
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++) //Go through each possible move
        {
            Board *copy1 = board->copy(); //Copy the board and iterate through possible opponent moves
            copy1->doMove(move, AI);
            Move *opp_move = new Move(i, j);
            if (copy1->checkMove(opp_move, opponent) == true)
            {
            
                copy1->doMove(opp_move, opponent);
                int best_score = -10000;
                for (int k = 0; k < 8; k++)
                {
                    for (int l = 0; l < 8; l++) //Go through each possible move
                    {
                        Board *copy2 = copy1->copy();
                        Move *AI_move = new Move(k, l);
                        if (copy2->checkMove(AI_move, AI) == true)
                        {
                            copy2->doMove(AI_move, AI);
/*
                            int score = simpleScore(copy2);
                            if (score > best_score)
*/
                            int worst_score2 = 10000;
                                for (int k = 0; k < 8; k++)
                                {
                                    for (int l = 0; l < 8; l++) //Go through each possible move
                                    {
                                        Board *copy3 = copy2->copy();
                                        Move *opp_move2 = new Move(k, l);
                                        if (copy3->checkMove(opp_move2, opponent) == true)
                                        {
                                            copy3->doMove(opp_move2, opponent);
                                            int score = simpleScore(copy3);
                                            if (score < worst_score2)
                                            {
                                            worst_score2 = score;
                                            }
                                        }
                                    }
                                
                            }
                            if (worst_score2 > best_score)
                            {
                                best_score = worst_score2;
                            }
                        }
                    }
                }
 
                if (best_score < worst_score) //If the current score is lower
                {
                    worst_score = best_score; //Set the new current score
                }
            }
            delete opp_move; //Free memory!
            delete copy1;
        }
    }
    return worst_score; //Return worst score
}

