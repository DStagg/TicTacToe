#include "PauseScene.h"

PauseScene::PauseScene(SDL_Renderer* win, MIX_Mixer* mix)
{
	_Window = win;
	_Player = mix;
};
PauseScene::~PauseScene()
{

};

void PauseScene::Begin()
{
	_Font = TTF_OpenFont("res/Roboto-Regular.ttf", 18.0f);
	SDL_Color color;
	color.r = color.g = color.b = color.a = 255;
	SDL_Surface* text = TTF_RenderText_Blended(_Font, "PAUSED", 0, color);
	_FontTex = SDL_CreateTextureFromSurface(_Window, text);
	SDL_DestroySurface(text);

	_MenuList.Populate({ "Resume","Restart","Quit to Menu" });
	int w, h;
	SDL_GetRenderOutputSize(_Window, &w, &h);
	_MenuList.Format(_Window, _Font, w / 2.f, (h / 2.f) - 50.f, SDLMenuList::Center);
	_MenuList.SetBuffers(10.f, 50.f);
	TTF_CloseFont(_Font);

	_MenuMoveSFX = MIX_LoadAudio(_Player, "res/MenuMove.wav", true);
	if (!_MenuMoveSFX) std::cout << "MenuMove failed to load." << std::endl;
	_MenuSelectSFX = MIX_LoadAudio(_Player, "res/MenuSelect.wav", true);
	if (!_MenuSelectSFX) std::cout << "MenuSelect failed to load." << std::endl;

};

void PauseScene::End()
{

};
void PauseScene::Pause()
{

};
void PauseScene::Resume()
{

};
void PauseScene::Update(float dt)
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		if (e.type == SDL_EVENT_QUIT)
		{
			SetRunning(false);
		}
		else if (e.type == SDL_EVENT_KEY_DOWN)
		{
			switch (e.key.key)
			{
			case SDLK_UP:
				_MenuList.DecChoice();
				if (Config::C()->_SFXOn) MIX_PlayAudio(_Player, _MenuMoveSFX);
				break;
			case SDLK_DOWN:
				_MenuList.IncChoice();
				if (Config::C()->_SFXOn) MIX_PlayAudio(_Player, _MenuMoveSFX);
				break;
			case SDLK_RETURN:
				if (Config::C()->_SFXOn) MIX_PlayAudio(_Player, _MenuSelectSFX);
				switch (_MenuList.GetChoice())
				{
				case 0:
					SetRunning(false);
					break;
				case 1:
					((TTTScene*)GetParent())->Refresh();
					SetRunning(false);
					break;
				case 2:
					GetManager()->Quit(2);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}
};
void PauseScene::DrawScreen()
{

	GetParent()->DrawScreen();

	int w, h;
	SDL_GetRenderOutputSize(_Window, &w, &h);
	SDL_FRect back;
	back.w = 200.f;
	back.h = 300.f;
	back.x = (w - back.w) / 2.f;
	back.y = (h - back.h) / 2.f;

	SDL_SetRenderDrawColor(_Window, 0, 0, 0, 255);
	SDL_RenderFillRect(_Window, &back);
	SDL_SetRenderDrawColor(_Window, 255, 255, 255, 255);
	SDL_RenderRect(_Window, &back);

	SDL_FRect dstrect;
	dstrect.w = _FontTex->w;
	dstrect.h = _FontTex->h;
	dstrect.x = (w - dstrect.w) / 2.f;
	dstrect.y = (h / 2.f) - 100.f;
	SDL_RenderTexture(_Window, _FontTex, NULL, &dstrect);

	_MenuList.Draw(_Window);
	
};