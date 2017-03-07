#include "player.hpp"
#include <time.h>

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
        
        int weightarray[8][8] = {{20,-5,5,5,5,5,-5,20},
                                 {-5,-5,2,2,2,2,-5,-5},
                                 {5,2,2,2,2,2,2,5},
                                 {5,2,2,2,2,2,2,5},
                                 {5,2,2,2,2,2,2,5},
                                 {5,2,2,2,2,2,2,5},
                                 {-5,-5,2,2,2,2,-5,-5},
                                 {20,-5,5,5,5,5,-5,20}};
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
    Board copy;
    Move *m;
    int maxxpos;
    int maxypos;
    int maxMoveVal = -1000;
    if (msLeft == -1)
    {
        return nullptr;
    }
    clock_t t;
    while ((((float)t)/CLOCKS_PER_SEC) <= msLeft)
    {
        if (opponentsMove == nullptr)
        {
             if (!b.hasMoves(s))
             {
				 return nullptr;
			 }
			 else
			 {
                 for (int i = 0; i < 8; i++)
                 {
					 for (int k = 0; k < 8; k++)
					 {
						 copy = b.copy();
						 m->setX(i);
						 m->setY(k);
						 if(copy.checkMove(m, s))
						 {
							 copy.doMove(m, s);
							 if(copy.score(weightarray, s) > maxMoveval)
							 {
								 maxMoveVal = copy.score(weightarray, s);
								 maxxpos = i;
								 maxypos = k;
							 }
							 else
							 {
								 continue;
							 }
						 }
						 else
						 {
							 continue;
						 }
					 }
				 }
				  return Move(maxxpos, maxypos);
			 }
        }
        else
        {
			b.doMove(opponentsMove, os);
			for (int i = 0; i < 8; i++)
            {
				for (int k = 0; k < 8; k++)
				{
					copy = b.copy();
					m->setX(i);
					m->setY(k);
					if(copy.checkMove(m, s))
					{
						copy.doMove(m, s);
						if(copy.score(weightarray, s) > maxMoveval)
						{
							maxMoveVal = copy.score(weightarray, s);
							maxxpos = i;
							maxypos = k;
						}
						else
						{
							continue;
						}
					}
					else
					{
						continue;
					}
				}
			}
			return Move(maxxpos, maxypos);
		}
        return nullptr;
    }
    
    /*check more heavily weighted positions first, then do move if valid,
     * for example, if corner position is available, do move for corner position
     */
     
    /*
    for (i=0;i<8;i++)
    {
        for (j=0; j<8;j++)
        {
            Move e->setX(i);
            Move e->setY(j);
            for (weightarray[i][j] == 4)
            {
                checkMove(e,s);
                doMove(e,s);
            }
                
            }
            for (weightarray[i][j]
                e
                
                
                
                
                b[i][j]
                
                int X = m->getX();
                m->setX(
    int Y = m->getY();
                
    if (b.hasMoves(s))
    {
        b.checkMove()
        
        b.doMove()
        */
         
    if (b.countBlack()>b.countWhite())
    {
        /*"Black wins"*/      //I don't think this part is necessary
                              //because we are only doing moves
    }
    else
    {
        /*"White wins"*/
    }
     
}
