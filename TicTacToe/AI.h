#ifndef AI_H
#define AI_H

#include "Random.h"

class AI
{
public:
	
	AI();
	~AI();

	virtual void TakeMove() = 0;
};

class EasyAI : public AI
{
public:

	EasyAI();
	~EasyAI();

	void TakeMove();

};

#endif