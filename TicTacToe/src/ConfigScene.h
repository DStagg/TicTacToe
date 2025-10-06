#ifndef CONFIGSCENE_H
#define CONFIGSCENE_H
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include "Scene.h"
#include "Config.h"
#include "MenuList.h"

class ConfigScene : public Scene
{
public:

	//ConfigScene(SDL_Renderer* win = nullptr, sf::Music* bgm = 0);
	ConfigScene(SDL_Renderer* win = nullptr, MIX_Mixer* mix = nullptr);
	~ConfigScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	SDL_Renderer* _Window;
	SDLMenuList _MenuList;
	
	//sf::Music* _BackgroundMusic;

	//sf::SoundBuffer _MenuMoveSFX;
	//sf::SoundBuffer _MenuSelectSFX;
	//sf::Sound _Player;
	MIX_Audio* _MenuMoveSFX;
	MIX_Audio* _MenuSelectSFX;
	MIX_Audio* _Music;
	MIX_Track* _MusicTrack;
	MIX_Mixer* _Player;

	//sf::Font _Font;
	TTF_Font* _Font = nullptr;
	SDL_Texture* _FontTex = nullptr;
};

#endif