#ifndef PAUSESCENE_H
#define PAUSESCENE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Scene.h"
#include "TTTScene.h"
#include "Config.h"

class PauseScene : public Scene
{
public:

	PauseScene(sf::RenderWindow* win = 0);
	~PauseScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	int _MenuChoice;
	sf::RenderWindow* _Window;
	sf::Font _Font;

	sf::SoundBuffer _MenuMoveSFX;
	sf::SoundBuffer _MenuSelectSFX;
	sf::Sound _Player;
};

#endif