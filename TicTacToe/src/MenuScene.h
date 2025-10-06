#ifndef MENUSCENE_H
#define MENUSCENE_H

//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

#include "Scene.h"
#include "TTTScene.h"

#include "Config.h"
#include "ConfigScene.h"

#include "MenuList.h"

class MenuScene : public Scene
{
public:

	//MenuScene(sf::RenderWindow* win = 0);
	MenuScene(SDL_Renderer* win = nullptr, MIX_Mixer* mix = nullptr);
	~MenuScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	//sf::Font _Font;
	TTF_Font* _Font = nullptr;
	SDL_Texture* _FontTex = nullptr;
	//sf::RenderWindow* _Window;
	SDL_Renderer* _Window;
	
	SDLMenuList _MenuList;

	//sf::SoundBuffer _MenuMoveSFX;
	//sf::SoundBuffer _MenuSelectSFX;
	//sf::Music _Music;
	//sf::Sound _Player;
	MIX_Audio* _MenuMoveSFX;
	MIX_Audio* _MenuSelectSFX;
	MIX_Audio* _Music;
	MIX_Track* _MusicTrack;
	MIX_Mixer* _Player;
};

#endif