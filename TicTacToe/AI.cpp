#include "AI.h"

AI::AI()
{

};
AI::~AI()
{

};

//

EasyAI::EasyAI()
{

};
EasyAI::~EasyAI()
{

};

void EasyAI::TakeMove(Grid* cells)
{
	cells->SetCell(1, 1, 2);
};