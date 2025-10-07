#include "MenuScene.h"

MenuScene::MenuScene(SDL_Renderer* win, MIX_Mixer* mix)
{
	_Window = win;
	_Player = mix;
};
MenuScene::~MenuScene()
{

};

void MenuScene::Begin()
{
	_Font = TTF_OpenFont("res/Roboto-Regular.ttf", 18.0f);
	SDL_Color color;
	color.r = color.g = color.b = color.a = 255;
	SDL_Surface* text = TTF_RenderText_Blended(_Font, "TIC-TAC-TOE", 0, color);
	_FontTex = SDL_CreateTextureFromSurface(_Window, text);
	SDL_DestroySurface(text);
	
	_MenuList.Populate({ "Play","Config","Quit" });
	int w, h;
	SDL_GetRenderOutputSize(_Window, &w, &h);
	_MenuList.Format(_Window, _Font, w / 2.f, h / 2.f, SDLMenuList::Center);
	_MenuList.SetBuffers(10.f, 50.f);
	TTF_CloseFont(_Font);

	_MenuMoveSFX = MIX_LoadAudio(_Player, "res/MenuMove.wav", true);
	if (!_MenuMoveSFX) std::cout << "MenuMove failed to load." << std::endl;
	_MenuSelectSFX = MIX_LoadAudio(_Player, "res/MenuSelect.wav", true);
	if (!_MenuSelectSFX) std::cout << "MenuSelect failed to load." << std::endl;
	_Music = MIX_LoadAudio(_Player, "res/Paradox.ogg", true);
	if (!_Music) std::cout << "Music failed to load." << std::endl;

	_MusicTrack = MIX_CreateTrack(_Player);
	
	if (!MIX_SetTrackAudio(_MusicTrack, _Music))
	{
		const char* error = SDL_GetError();
		std::cout << "Couldn't create music track: " << error << std::endl;
	}

	SDL_PropertiesID options = SDL_CreateProperties();
	SDL_SetNumberProperty( options, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
	SDL_SetNumberProperty(options, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER, 2000);
	MIX_PlayTrack(_MusicTrack, options);
	if (!Config::C()->_MusicOn) MIX_PauseTrack(_MusicTrack);
	SDL_DestroyProperties(options);
};
void MenuScene::End()
{
	MIX_StopTrack(_MusicTrack, 0);
};
void MenuScene::Pause()
{

};
void MenuScene::Resume()
{

};
void MenuScene::Update(float dt)
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
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
					GetManager()->PushScene(new TTTScene(_Window, _Player, _MusicTrack));
					break;
				case 1:
					GetManager()->PushScene(new ConfigScene(_Window, _Player, _MusicTrack));
					break;
				case 2:
					GetManager()->Quit(1);
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
void MenuScene::DrawScreen()
{
	int w, h;
	SDL_GetRenderOutputSize(_Window, &w, &h);
	SDL_FRect srcrect;
	srcrect.x = srcrect.y = 0;
	srcrect.w = _FontTex->w;
	srcrect.h = _FontTex->h;
	SDL_FRect dstrect;
	dstrect.w = srcrect.w;
	dstrect.h = srcrect.h;
	dstrect.x = (w - dstrect.w) / 2.f;
	dstrect.y = dstrect.h;
	SDL_RenderTexture(_Window, _FontTex, &srcrect, &dstrect);

	_MenuList.Draw(_Window);
};