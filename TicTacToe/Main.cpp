//#include <SFML/Graphics.hpp>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

#include "ext/Timer.h"

#include "src/Scene.h"

#include "src/MenuScene.h"
#include "src/TTTScene.h"

SDL_Renderer* renderer = nullptr;
SDL_Window* window = nullptr;
MIX_Mixer* mixer = nullptr;

int main()
{
	//int FramesPerSecond = 60;
	//float deltaT = 0.f;
	//sf::Clock UpdateClock;
	Timer UpdateClock;

	//sf::RenderWindow _Window;
	//_Window.create(sf::VideoMode(624, 624), "Tic-Tac-Toe");
	SDL_CreateWindowAndRenderer("Tic-Tac-Toe", 624, 624, NULL, &window, &renderer);

	if (!TTF_Init())
	{
		std::cout << "Couldn't init SDL_TTF :" << SDL_GetError() << std::endl;
		return SDL_APP_FAILURE;
	}
	if (!MIX_Init())
	{
		const char* error = SDL_GetError();
		std::cout << "Couldn't init SDL_Mixer :" << error << std::endl;
		return SDL_APP_FAILURE;
	}

	mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);

	if (!mixer)
	{
		const char* error = SDL_GetError();
		std::cout << "Couldn't create mixer : " << error << std::endl;
		return SDL_APP_FAILURE;
	}

	SceneManager SCM;
	//SCM.PushScene(new MenuScene(&_Window));
	SCM.PushScene(new MenuScene(renderer,mixer));
	
	//UpdateClock.restart();
	UpdateClock.Reset();
	while (SCM.GetActiveScenePntr() != 0)
	{
		//SCM.GetActiveScenePntr()->Update(UpdateClock.restart().asSeconds());
		SCM.GetActiveScenePntr()->Update(UpdateClock.Lap() / 1000.f);
		//_Window.clear();
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SCM.GetActiveScenePntr()->DrawScreen();
		//_Window.display();
		SDL_RenderPresent(renderer);
		SCM.CullScenes();
	}
	
	MIX_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return SDL_APP_SUCCESS;
}