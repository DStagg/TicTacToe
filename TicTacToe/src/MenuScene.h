#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Scene.h"
#include "TTTScene.h"

#include "Config.h"
#include "ConfigScene.h"

#include "MenuList.h"

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
	
	SFMLMenuList _MenuList;

	sf::SoundBuffer _MenuMoveSFX;
	sf::SoundBuffer _MenuSelectSFX;
	sf::Music _Music;
	sf::Sound _Player;
};

#endif