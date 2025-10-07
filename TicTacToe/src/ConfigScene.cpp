#include "ConfigScene.h"

ConfigScene::ConfigScene(SDL_Renderer* win, MIX_Mixer* mix, MIX_Track* bgm)
{
	_Window = win;
	_Player = mix;
	_MusicTrack = bgm;
};
ConfigScene::~ConfigScene()
{

};

void ConfigScene::Begin()
{
	_Font = TTF_OpenFont("res/Roboto-Regular.ttf", 18.0f);
	SDL_Color color;
	color.r = color.g = color.b = color.a = 255;
	SDL_Surface* text = TTF_RenderText_Blended(_Font, "Config", 0, color);
	_FontTex = SDL_CreateTextureFromSurface(_Window, text);
	SDL_DestroySurface(text);

	_MenuList.Populate({ "Music","SFX","AI","Quit" });
	if (Config::C()->_MusicOn)
		_MenuList.SetList(0, "Music: On");
	else
		_MenuList.SetList(0, "Music: Off");

	if (Config::C()->_SFXOn)
		_MenuList.SetList(1, "SFX: On");
	else
		_MenuList.SetList(1, "SFX: Off");

	if (Config::C()->_AILvl == 0)
		_MenuList.SetList(2, "AI: Easy");
	else if (Config::C()->_AILvl == 1)
		_MenuList.SetList(2, "AI: Medium");
	else
		_MenuList.SetList(2, "AI: Hard");
	int w, h;
	SDL_GetRenderOutputSize(_Window, &w, &h);
	_MenuList.Format(_Window, _Font, (w / 2.f), (h / 2.f) - 100.f, SDLMenuList::Center);
	_MenuList.SetBuffers(10.f, 50.f);
	
	_MenuMoveSFX = MIX_LoadAudio(_Player, "res/MenuMove.wav", true);
	if (!_MenuMoveSFX) std::cout << "MenuMove failed to load." << std::endl;
	_MenuSelectSFX = MIX_LoadAudio(_Player, "res/MenuSelect.wav", true);
	if (!_MenuSelectSFX) std::cout << "MenuSelect failed to load." << std::endl;

};
void ConfigScene::End()
{
	Config::C()->SaveToFile("Config.txt");
	TTF_CloseFont(_Font);
};
void ConfigScene::Pause()
{

};
void ConfigScene::Resume()
{

};
void ConfigScene::Update(float dt)
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
				if (Config::C()->_SFXOn && _MenuList.GetChoice() != 1) MIX_PlayAudio(_Player, _MenuSelectSFX);
				switch (_MenuList.GetChoice())
				{
				case 0:
					Config::C()->_MusicOn = !Config::C()->_MusicOn;
					if (Config::C()->_MusicOn) MIX_ResumeTrack(_MusicTrack);
					else MIX_PauseTrack(_MusicTrack);
					if (Config::C()->_MusicOn) _MenuList.SetList(0, "Music: On");
					else _MenuList.SetList(0, "Music: Off");
					_MenuList.RedrawMenuItem(_Window, 0, _MenuList.GetList(0));
					break;
				case 1:
					Config::C()->_SFXOn = !Config::C()->_SFXOn;
					if (Config::C()->_SFXOn) MIX_PlayAudio(_Player, _MenuSelectSFX);
					if (Config::C()->_SFXOn) _MenuList.SetList(1, "SFX: On");
					else _MenuList.SetList(1, "SFX: Off");
					_MenuList.RedrawMenuItem(_Window, 1, _MenuList.GetList(1));
					break;
				case 2:
					Config::C()->_AILvl = Config::C()->_AILvl + 1;
					if (Config::C()->_AILvl > 2) Config::C()->_AILvl = 0;
					if (Config::C()->_AILvl == 0) _MenuList.SetList(2, "AI: Easy");
					else if (Config::C()->_AILvl == 1) _MenuList.SetList(2, "AI: Medium");
					else _MenuList.SetList(2, "AI: Hard");
					_MenuList.RedrawMenuItem(_Window, 2, _MenuList.GetList(2));
					break;
				case 3:
					GetManager()->Quit(1);
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
	}

};
void ConfigScene::DrawScreen()
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
