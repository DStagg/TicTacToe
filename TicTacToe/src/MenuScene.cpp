#include "MenuScene.h"

//MenuScene::MenuScene(sf::RenderWindow* win)
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
	//_Font.loadFromFile("Roboto-Regular.ttf");
	_Font = TTF_OpenFont("res/Roboto-Regular.ttf", 18.0f);
	SDL_Color color;
	color.r = color.g = color.b = color.a = 255;
	SDL_Surface* text = TTF_RenderText_Blended(_Font, "TIC-TAC-TOE", 0, color);
	_FontTex = SDL_CreateTextureFromSurface(_Window, text);
	SDL_DestroySurface(text);
	

	_MenuList.Populate({ "Play","Config","Quit" });
	//_MenuList.Format(_Font, _Window->getSize().x / 2.f, _Window->getSize().y / 2.f, SFMLMenuList::Center);
	int w, h;
	SDL_GetRenderOutputSize(_Window, &w, &h);
	_MenuList.Format(_Window, _Font, w / 2.f, h / 2.f, SDLMenuList::Center);
	_MenuList.SetBuffers(10.f, 50.f);
	TTF_CloseFont(_Font);

	//if (!_MenuMoveSFX.loadFromFile("MenuMove.wav"))
	//	std::cout << "MenuMove.wav failed to load!" << std::endl;
	//if (!_MenuSelectSFX.loadFromFile("MenuSelect.wav"))
	//	std::cout << "MenuSelect.wav failed to load!" << std::endl;
	_MenuMoveSFX = MIX_LoadAudio(_Player, "res/MenuMove.wav", true);
	if (!_MenuMoveSFX) std::cout << "MenuMove failed to load." << std::endl;
	_MenuSelectSFX = MIX_LoadAudio(_Player, "res/MenuSelect.wav", true);
	if (!_MenuSelectSFX) std::cout << "MenuSelect failed to load." << std::endl;
	_Music = MIX_LoadAudio(_Player, "res/Paradox.ogg", true);
	if (!_Music) std::cout << "Music failed to load." << std::endl;
	/*
	if ( _Window == 0 )
		_Window->create(sf::VideoMode(624, 624), "Tic-Tac-Toe");
	*/
	//if (!_Music.openFromFile("Paradox.ogg"))
	//	std::cout << "Paradox.ogg failed to load!" << std::endl;
	//_Music.setVolume(25.f);
	_MusicTrack = MIX_CreateTrack(_Player);
	
	if (!MIX_SetTrackAudio(_MusicTrack, _Music))
	{
		const char* error = SDL_GetError();
		std::cout << "Couldn't create music track: " << error << std::endl;
	}

	//if (Config::C()->_MusicOn)
	//{
		SDL_PropertiesID options = SDL_CreateProperties();
		SDL_SetNumberProperty( options, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
		SDL_SetNumberProperty(options, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER, 2000);
		MIX_PlayTrack(_MusicTrack, options);
		if (!Config::C()->_MusicOn) MIX_PauseTrack(_MusicTrack);
		SDL_DestroyProperties(options);
		//_Music.play();
	//}
};
void MenuScene::End()
{
	//_Music.stop();
	MIX_StopTrack(_MusicTrack, 0);
};
void MenuScene::Pause()
{
	//MIX_PauseTrack(_MusicTrack);
};
void MenuScene::Resume()
{
	//if (!Config::C()->_MusicOn) _Music.stop();
	//else if (_Music.getStatus() != sf::Music::Playing) _Music.play();
	//if (Config::C()->_MusicOn)
	//	MIX_ResumeTrack(_MusicTrack);
};
void MenuScene::Update(float dt)
{
	//sf::Event Event;
	SDL_Event e;
	//while (_Window->pollEvent(Event))
	while (SDL_PollEvent(&e))
	{
		//if (Event.type == sf::Event::Closed)
		if (e.type == SDL_EVENT_QUIT)
		{
			SetRunning(false);
		}
		//else if (Event.type == sf::Event::KeyPressed)
		else if (e.type == SDL_EVENT_KEY_DOWN)
		{
			//switch (Event.key.code)
			switch (e.key.key)
			{
			//case sf::Keyboard::Up:
			case SDLK_UP:
				_MenuList.DecChoice();
				//_Player.setBuffer(_MenuMoveSFX);
				MIX_PlayAudio(_Player, _MenuMoveSFX);
				break;
			//case sf::Keyboard::Down:
			case SDLK_DOWN:
				_MenuList.IncChoice();
				//_Player.setBuffer(_MenuMoveSFX); 
				MIX_PlayAudio(_Player, _MenuMoveSFX);
				break;
			//case sf::Keyboard::Return:
			case SDLK_RETURN:
				//_Player.setBuffer(_MenuSelectSFX); 
				MIX_PlayAudio(_Player, _MenuSelectSFX);
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
			//if ((_Player.getStatus() != sf::Sound::Playing) && (Config::C()->_SFXOn))
			//	_Player.play();
		}
	}
};
void MenuScene::DrawScreen()
{
	//sf::Text titleText;
	//titleText.setString("TIC-TAC-TOE");
	//titleText.setFont(_Font);
	int w, h;
	SDL_GetRenderOutputSize(_Window, &w, &h);
	//titleText.setPosition((w - titleText.getLocalBounds().width) / 2.f, titleText.getLocalBounds().height);
	SDL_FRect srcrect;
	srcrect.x = srcrect.y = 0;
	srcrect.w = _FontTex->w;
	srcrect.h = _FontTex->h;
	SDL_FRect dstrect;
	dstrect.w = srcrect.w;
	dstrect.h = srcrect.h;
	dstrect.x = (w - dstrect.w) / 2.f;
	dstrect.y = dstrect.h;
	//_Window->draw(titleText);
	SDL_RenderTexture(_Window, _FontTex, &srcrect, &dstrect);

	_MenuList.Draw(_Window);
};