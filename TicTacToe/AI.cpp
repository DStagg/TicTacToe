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
	std::vector<int> openx;
	std::vector<int> openy;
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			if (cells->GetCell(x, y) == 0)
			{
				openx.push_back(x);
				openy.push_back(y);
			}
	if ((int)openx.size() == 0)
		return;
	int choice = Random::Generate(0, (int)openx.size() - 1);
	
	cells->SetCell(openx[choice], openy[choice], 2);
};