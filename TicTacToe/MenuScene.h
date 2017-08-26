#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <SFML/Graphics.hpp>

#include "Scene.h"
#include "TTTScene.h"

class MenuScene : public Scene
{
public:

	MenuScene(sf::RenderWindow* win = 0);
	~MenuScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	sf::Font _Font;
	sf::RenderWindow* _Window;
	int _MenuChoice;
};

#endif