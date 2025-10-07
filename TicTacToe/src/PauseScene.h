#ifndef PAUSESCENE_H
#define PAUSESCENE_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

#include "Scene.h"
#include "TTTScene.h"
#include "Config.h"
#include "MenuList.h"

class PauseScene : public Scene
{
public:

	PauseScene(SDL_Renderer* win = nullptr, MIX_Mixer* mix = nullptr);
	~PauseScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	SDLMenuList _MenuList;

	SDL_Renderer* _Window;
	TTF_Font* _Font = nullptr;
	SDL_Texture* _FontTex = nullptr;

	MIX_Audio* _MenuMoveSFX;
	MIX_Audio* _MenuSelectSFX;
	MIX_Mixer* _Player;
};

#endif