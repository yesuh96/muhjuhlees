#include "player.hpp"
#inlcude <time.h>

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
	clock_t t;
	while ((((float)t)/CLOCKS_PER_SEC) <= 30.0)
	{
        // Will be set to true in test_minimax.cpp.
        testingMinimax = false;
        b = Board();
        if (side == BLACK)
        {
            s = side;
            os = WHITE;
        }
        else
        {
            s = side;
            os = BLACK;
        }
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
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    weightarray = {{},{}}
    if (msLeft == -1)
    {
        return nullptr;
    }
    clock_t t;
    while ((((float)t)/CLOCKS_PER_SEC) <= msLeft)
    {
        if (opponentsMove == nullptr)
        {
            
        }
        return nullptr;
    }
    /*if (b.hasMoves(s))
    {
        b.checkMove()
        
        b.doMove()
        */
         
    if (b.countBlack()>b.countWhite)
    {
        /*"Black wins"*/
    }
    else
    {
        /*"White wins"*/
    }
     
}
