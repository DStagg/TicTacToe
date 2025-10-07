#ifndef CONFIGSCENE_H
#define CONFIGSCENE_H
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "Scene.h"
#include "Config.h"
#include "MenuList.h"

class ConfigScene : public Scene
{
public:

	ConfigScene(SDL_Renderer* win = nullptr, MIX_Mixer* mix = nullptr, MIX_Track* bgm = nullptr);
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
	

	MIX_Audio* _MenuMoveSFX;
	MIX_Audio* _MenuSelectSFX;
	MIX_Track* _MusicTrack;
	MIX_Mixer* _Player;

	TTF_Font* _Font = nullptr;
	SDL_Texture* _FontTex = nullptr;
};

#endif