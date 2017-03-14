#include "player.hpp"
#include <time.h>
#include <vector>

using namespace std;
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

int Player::pvs(Board *cc, int depth, int alpha, int beta, Side s)
{
	Move * m2 = new Move(0, 0);
	int score;
    Board *copy;
    if (depth == 0 || !(cc->hasMoves(s)))
    {
		return cc->score(s);
	}
    int flag = 1;
    // for each child
    for (int i = 0; i < 8; i++)
    {
        for (int k = 0; k < 8; k++)
        {
            copy = cc->copy();
            m2->setX(i);
            m2->setY(k);
            // for each valid child
            if(copy->checkMove(m2, s))
            {
                if (flag == 1)
                { 
                    score = -pvs(copy, depth-1, -beta, -alpha, os);
                    flag = 0;
                }
                else
                {
                    score = -pvs(copy, depth-1, -alpha-1, -alpha, os);
                    if (alpha < score && score < beta)
                    {
                        score = -pvs(copy, depth-1, -beta, -score, os);
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
	
	//in doMove() function
	//Array of valid moves
	Move * m;
	vector<Move*> moves;
    Board * cc;
	int depth = 4;
	int alpha = -100000;
	int beta = 100000;
	if (opponentsMove == nullptr)
    {
        if (!(b->hasMoves(s)))
        {
            return nullptr;
        }
        else
        {
			if (depth == 0 || !(b->hasMoves(s)))
			{
				return nullptr;
			}
			else
			{
				for (int i = 0; i < 8; i++)
				{
					for (int k = 0; k < 8; k++)
					{
						cc = b->copy();
						m->setX(i);
						m->setY(k);
						//if the chlid is valid
						if (cc->checkMove(m, s))
						{
							moves.push_back(m);
						}
					}
				}
				//for each of first chlid valid moves
				int index = 0;
				for (unsigned int movecheck = 0; 
				movecheck < moves.size(); movecheck++)
				{
					int fscore = -1000000;
					Board *copy3 = b->copy();
					copy3->doMove(moves[movecheck], s);
					int tempscore = pvs(copy3, depth, alpha, beta, s);
					if (tempscore > fscore)
					{
						fscore = tempscore;
						index = movecheck;
					}
				}
				b->doMove(moves[index], s);
				return moves[index];
			}
		}
	}
	else
	{
		b->doMove(opponentsMove, os);
		for (int i = 0; i < 8; i++)
		{
			for (int k = 0; k < 8; k++)
			{
				cc = b->copy();
				m->setX(i);
				m->setY(k);
				//if the chlid is valid
				if (cc->checkMove(m, s))
				{
					moves.push_back(m);
				}
			}
		}
		//for each of first chlid valid moves
		int index = 0;
		for (unsigned int movecheck = 0; 
		movecheck < moves.size(); movecheck++)
		{
			int fscore = -1000000;
			Board *copy3 = b->copy();
			copy3->doMove(moves[movecheck], s);
			int tempscore = pvs(copy3, depth, alpha, beta, s);
			if (tempscore > fscore)
			{
				fscore = tempscore;
				index = movecheck;
			}
		}
		b->doMove(moves[index], s);
		return moves[index];
	}
    /*Board *copy;
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
			if (testingMinimax == false)
			{
				for (int i = 0; i < 8; i++)
				{
					for (int k = 0; k < 8; k++)
					{
						copy = b->copy();
						m->setX(i);
						m->setY(k);
						if(copy->checkMove(m, s))
						{
							copy->doMove(m, s);
							if(copy->score(s) > maxMoveVal)
							{
								maxMoveVal = copy->score(s);
								maxxpos = i;
								maxypos = k;
							}
						}
					}
				}
				Move * finalpos = new Move(maxxpos, maxypos);
				b->doMove(finalpos, s);
				return finalpos;
			}
			//for minimax
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
								for (int subk = 0; subk <8; subk++)
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
			if (testingMinimax == false)
			{
				for (int i = 0; i < 8; i++)
				{
					for (int k = 0; k < 8; k++)
					{
						copy = b->copy();
						m->setX(i);
						m->setY(k);
						if(copy->checkMove(m, s))
						{
							copy->doMove(m, s);
							if(copy->score(s) > maxMoveVal)
							{
								maxMoveVal = copy->score(s);
								maxxpos = i;
								maxypos = k;
							}
						}
					}
				}
				Move * finalpos = new Move(maxxpos, maxypos);
				b->doMove(finalpos, s);
				return finalpos;
			} 
			//for minimax
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
								for (int subk = 0; subk <8; subk++)
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
	}
    return nullptr;
    */
    return nullptr;
}
