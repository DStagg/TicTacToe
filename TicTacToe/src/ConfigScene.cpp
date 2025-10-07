#include "ConfigScene.h"

//ConfigScene::ConfigScene(SDL_Renderer* win, sf::Music* bgm)
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
	//_Font.loadFromFile("Roboto-regular.ttf");
	_Font = TTF_OpenFont("res/Roboto-Regular.ttf", 18.0f);
	SDL_Color color;
	color.r = color.g = color.b = color.a = 255;
	SDL_Surface* text = TTF_RenderText_Blended(_Font, "Config", 0, color);
	_FontTex = SDL_CreateTextureFromSurface(_Window, text);
	SDL_DestroySurface(text);


	_MenuList.Populate({ "Music","SFX","AI","Quit" });
	int w, h;
	SDL_GetRenderOutputSize(_Window, &w, &h);
	_MenuList.Format(_Window, _Font, (w / 2.f), (h / 2.f) - 100.f, SDLMenuList::Center);
	_MenuList.SetBuffers(10.f, 50.f);
	TTF_CloseFont(_Font);

	//_MenuMoveSFX.loadFromFile("MenuMove.wav");
	//_MenuSelectSFX.loadFromFile("MenuSelect.wav");
	_MenuMoveSFX = MIX_LoadAudio(_Player, "res/MenuMove.wav", true);
	if (!_MenuMoveSFX) std::cout << "MenuMove failed to load." << std::endl;
	_MenuSelectSFX = MIX_LoadAudio(_Player, "res/MenuSelect.wav", true);
	if (!_MenuSelectSFX) std::cout << "MenuSelect failed to load." << std::endl;
	//_Music = MIX_LoadAudio(_Player, "res/Paradox.ogg", true);
	//if (!_Music) std::cout << "Music failed to load." << std::endl;

	//MIX_SetTrackAudio(_MusicTrack, _Music);
	/*
	if (Config::C()->_MusicOn)
	{
		SDL_PropertiesID options = SDL_CreateProperties();
		SDL_SetNumberProperty(options, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
		SDL_SetNumberProperty(options, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER, 2000);
		MIX_PlayTrack(_MusicTrack, options);
		SDL_DestroyProperties(options);
		//_Music.play();
	}*/
};
void ConfigScene::End()
{
	Config::C()->SaveToFile("Config.txt");
};
void ConfigScene::Pause()
{

};
void ConfigScene::Resume()
{

};
void ConfigScene::Update(float dt)
{
	//sf::Event Event;
	//while (_Window->pollEvent(Event))
	SDL_Event e;
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
				if (Config::C()->_SFXOn) MIX_PlayAudio(_Player, _MenuMoveSFX);
				break;
			//case sf::Keyboard::Down:
			case SDLK_DOWN:
				_MenuList.IncChoice();
				//_Player.setBuffer(_MenuMoveSFX);
				if (Config::C()->_SFXOn) MIX_PlayAudio(_Player, _MenuMoveSFX);
				break;
			//case sf::Keyboard::Return:
			case SDLK_RETURN:
				//_Player.setBuffer(_MenuSelectSFX);
				if (Config::C()->_SFXOn && _MenuList.GetChoice() != 1) MIX_PlayAudio(_Player, _MenuSelectSFX);
				switch (_MenuList.GetChoice())
				{
				case 0:
					Config::C()->_MusicOn = !Config::C()->_MusicOn;
					if (Config::C()->_MusicOn) MIX_ResumeTrack(_MusicTrack);
					else MIX_PauseTrack(_MusicTrack);
					//if ((_BackgroundMusic != 0) && (Config::C()->_MusicOn))
					//	_BackgroundMusic->play();
					//else if ((_BackgroundMusic != 0) && (!Config::C()->_MusicOn))
					//	_BackgroundMusic->stop();
					break;
				case 1:
					Config::C()->_SFXOn = !Config::C()->_SFXOn;
					if (Config::C()->_SFXOn) MIX_PlayAudio(_Player, _MenuSelectSFX);
					break;
				case 2:
					Config::C()->_AILvl = Config::C()->_AILvl + 1;
					if (Config::C()->_AILvl > 2) Config::C()->_AILvl = 0;
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
			//if ((_Player.getStatus() != sf::Sound::Playing) && (Config::C()->_SFXOn) )
			//	_Player.play();
		}
	}
	// TODO: redraw menu text
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
};
void ConfigScene::DrawScreen()
{
	//sf::Text titleText;
	//titleText.setString("Config");
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

	//	The below was commented out when I cloned this from GitHub (06/10/25). I don't remember why.
	/*
	sf::Text MusicText;
	if (Config::C()->_MusicOn)
		MusicText.setString("Music: On");
	else
		MusicText.setString("Music: Off");
	MusicText.setFont(_Font);
	if (_MenuChoice == 0) MusicText.setStyle(sf::Text::Underlined);
	MusicText.setPosition((_Window->getSize().x - MusicText.getLocalBounds().width) / 2.f, (_Window->getSize().y / 2.f) - 50.f);
	_Window->draw(MusicText);

	sf::Text SFXText;
	if (Config::C()->_SFXOn)
		SFXText.setString("SFX: On");
	else
		SFXText.setString("SFX: Off");
	SFXText.setFont(_Font);
	if (_MenuChoice == 1) SFXText.setStyle(sf::Text::Underlined);
	SFXText.setPosition((_Window->getSize().x - SFXText.getLocalBounds().width) / 2.f, (_Window->getSize().y / 2.f));
	_Window->draw(SFXText);

	sf::Text AIText;
	if (Config::C()->_AILvl == 0)
		AIText.setString("AI: Easy");
	else if (Config::C()->_AILvl == 1)
		AIText.setString("AI: Medium");
	else
		AIText.setString("AI: Hard");
	AIText.setFont(_Font);
	if (_MenuChoice == 2) AIText.setStyle(sf::Text::Underlined);
	AIText.setPosition((_Window->getSize().x - AIText.getLocalBounds().width) / 2.f, (_Window->getSize().y / 2.f) + 50.f);
	_Window->draw(AIText);

	sf::Text quitText;
	quitText.setString("Quit");
	quitText.setFont(_Font);
	if (_MenuChoice == 3) quitText.setStyle(sf::Text::Underlined);
	quitText.setPosition((_Window->getSize().x - quitText.getLocalBounds().width) / 2.f, (_Window->getSize().y / 2.f) + 100.f);
	_Window->draw(quitText);
	*/
};