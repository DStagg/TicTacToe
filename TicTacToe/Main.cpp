#include <SFML/Graphics.hpp>

#include "Scene.h"

#include "TTTScene.h"


int main()
{
	int FramesPerSecond = 60;
	float deltaT = 0.f;
	sf::Clock UpdateClock;

	SceneManager SCM;
	SCM.PushScene(new TTTScene());
	
	UpdateClock.restart();
	while (SCM.GetActiveScenePntr() != 0)
	{
		SCM.GetActiveScenePntr()->Update(UpdateClock.restart().asSeconds());
		SCM.GetActiveScenePntr()->DrawScreen();
		SCM.CullScenes();
	}
	
	return 0;
}