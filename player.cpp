#include "player.hpp"
#include <time.h>
#include <vector>

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
	// Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    b = new Board();
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

int *Player::pvs(Board *cc, Move *m, int depth, int alpha, int beta, Side s)
{
	int score;
    if (depth == 0 || !(b->hasMoves(s)))
    {
		return b->score(s);
	}
    int flag = 1;
    // for each child
    for (int i = 0; i < 8; i++)
    {
        for (int k = 0; k < 8; k++)
        {
            copy = b->copy();
            m->setX(i);
            m->setY(k);
            if(copy->checkMove(m, s))
            {
                if (flag == 1)
                { 
                    score = -pvs(child, depth-1, -beta, -alpha, -color);
                    flag = 0;
                }
                else
                {
                    score = -pvs(child, depth-1, -alpha-1, -alpha, -color);
                    if (alpha < score && score < beta)
                    {
                        score = -pvs(child, depth-1, -beta, -score, -color);
                    }
                }
                alpha = max(alpha, score);
                if (alpha >= beta)
                {
                    break;
                }
            }
        }
    }
    return alpha;
}


Move *Player::doMove(Move *opponentsMove, int msLeft) {
    Board *copy;
    Move *m = new Move(0, 0);
    int maxxpos;
    int maxypos;
    int maxMoveVal = -1000;
    if (opponentsMove == nullptr)
    {
        if (!(b->hasMoves(s)))
        {
            return nullptr;
        }
        else
        {
            vector<int>scores;
            vector<Move>moves;
            for (int i = 0; i < 8; i++)
            {
                for (int k = 0; k < 8; k++)
                {
                    copy = b->copy();
                    m->setX(i);
                    m->setY(k);
                    if(copy->checkMove(m, s))
                    {
                        maxMoveVal = 1000;
                        //do valid move
                        /*
                        copy->doMove(m, s);
                        for (int i2 = 0; i2 < 8; i2++)
                        {
							for (int k2 = 0; k2 < 8; k2++)
							{
								m->setX(i2);
								m->setY(k2);
								if (copy->checkMove(m, s))
								{ */
									copy->doMove(m, s);
                                    for (int subi = 0; subi < 8; subi++)
                                    {
                                        for (int subk = 0; subk < 8; subk++)
                                        {
                                            m->setX(i);
                                            m->setY(k);
                                            if(copy->checkMove(m, s))
                                            {
                                                copy->doMove(m, s);
                                                if(copy->score(s) < maxMoveVal)
                                                {
                                                    maxMoveVal = copy->score(s);
                                                }
                                            /*}
                                        }
									}*/
								}		
							}
						}
                        scores.push_back(maxMoveVal);
                        moves.push_back(Move(i, k));
                    }
                }
            }
            int greatestminval;
            int index;
            for (unsigned int s = 0; s < scores.size() - 1; s++)
            {
                greatestminval = scores[0];
                index = 0;
                if (scores[s] > greatestminval)
                {
                    index = s;
                    greatestminval = scores[s];
                }
            }
            maxxpos = (moves[index]).getX();
            maxypos = (moves[index]).getY();
            Move * finalpos = new Move(maxxpos, maxypos);
            b->doMove(finalpos, s);
            return finalpos;
		}
    }
    else
    {
        b->doMove(opponentsMove, os);
        if (!(b->hasMoves(s)))
        {
            return nullptr;
        }
        else
        {
            vector<int>scores;
            vector<Move>moves;
            for (int i = 0; i < 8; i++)
            {
                for (int k = 0; k < 8; k++)
                {
                    copy = b->copy();
                    m->setX(i);
                    m->setY(k);
                    if(copy->checkMove(m, s))
                    {
                        maxMoveVal = 1000;
                        //do valid move
                        copy->doMove(m, s);
						for (int subi = 0; subi < 8; subi++)
						{
							for (int subk = 0; subk < 8; subk++)
							{
								m->setX(i);
								m->setY(k);
								if(copy->checkMove(m, s))
								{
									copy->doMove(m, s);
									if(copy->score(s) < maxMoveVal)
									{
										maxMoveVal = copy->score(s);
									}
								}		
							}
						}
                        scores.push_back(maxMoveVal);
                        moves.push_back(Move(i, k));
                    }
                }
            }
            int greatestminval;
            int index;
            for (unsigned int s = 0; s < scores.size() - 1; s++)
            {
                greatestminval = scores[0];
                index = 0;
                if (scores[s] > greatestminval)
                {
                    index = s;
                    greatestminval = scores[s];
                }
            }
            maxxpos = (moves[index]).getX();
            maxypos = (moves[index]).getY();
            Move * finalpos = new Move(maxxpos, maxypos);
            b->doMove(finalpos, s);
            return finalpos;
		}
	}
    return nullptr;
}
