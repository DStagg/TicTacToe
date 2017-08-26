#include <SFML/Graphics.hpp>

#include "Scene.h"

#include "MenuScene.h"
#include "TTTScene.h"


int main()
{
	int FramesPerSecond = 60;
	float deltaT = 0.f;
	sf::Clock UpdateClock;

	sf::RenderWindow _Window;
	_Window.create(sf::VideoMode(624, 624), "Tic-Tac-Toe");

	SceneManager SCM;
	SCM.PushScene(new MenuScene(&_Window));
	
	UpdateClock.restart();
	while (SCM.GetActiveScenePntr() != 0)
	{
		SCM.GetActiveScenePntr()->Update(UpdateClock.restart().asSeconds());
		_Window.clear();
		SCM.GetActiveScenePntr()->DrawScreen();
		_Window.display();
		SCM.CullScenes();
	}
	
	return 0;
}