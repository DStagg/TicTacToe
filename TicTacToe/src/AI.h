#pragma once


#include "Random.h"
#include "Grid.h"

class AI
{
public:
	
	AI();
	~AI();

	virtual void TakeMove(Grid* cells) = 0;
};

class EasyAI : public AI
{
public:

	EasyAI();
	~EasyAI();

	void TakeMove(Grid* cells);

};
