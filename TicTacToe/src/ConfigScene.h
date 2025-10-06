#ifndef CONFIGSCENE_H
#define CONFIGSCENE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Scene.h"
#include "Config.h"
#include "MenuList.h"

class ConfigScene : public Scene
{
public:

	ConfigScene(sf::RenderWindow* win = 0, sf::Music* bgm = 0);
	~ConfigScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	sf::RenderWindow* _Window;
	SFMLMenuList _MenuList;
	
	sf::Music* _BackgroundMusic;

	sf::SoundBuffer _MenuMoveSFX;
	sf::SoundBuffer _MenuSelectSFX;
	sf::Sound _Player;

	sf::Font _Font;
};

#endif