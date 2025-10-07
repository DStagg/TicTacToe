#pragma once

#include <sstream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "Utility.h"
#include "Scene.h"
#include "PauseScene.h"
#include "Config.h"
#include "AI.h"

#include "Grid.h"

class TTTScene : public Scene
{
public:

	TTTScene(SDL_Renderer* win = nullptr, MIX_Mixer* mix = nullptr, MIX_Track* bgm = nullptr);
	~TTTScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

	int CheckForWin();
	void Refresh();

private:

	float	_DelayTimer;
	float _TurnDelay = 0.5f;
	bool _PlayerTurn;

	SDL_Renderer* _Window;
	SDL_Texture* _Pieces;
	SDL_FRect _X;
	SDL_FRect _O;

	Grid _Cells;

	int _XMargin = 100;
	int _YMargin = 100;
	int _XBuffer = 10;
	int _YBuffer = 10;

	MIX_Audio* _PlaceSFX;
	MIX_Audio* _VictorySFX;
	MIX_Audio* _DrawSFX;
	MIX_Track* _MusicTrack;
	MIX_Mixer* _Player;

	bool _Done;

	AI* _AI;

	float _MouseX;
	float _MouseY;

};
