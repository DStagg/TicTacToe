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
	//_Font.loadFromFile("Roboto-Regular.ttf");
	_Font = TTF_OpenFont("res/Roboto-Regular.ttf", 18.0f);
	SDL_Color color;
	color.r = color.g = color.b = color.a = 255;
	SDL_Surface* text = TTF_RenderText_Blended(_Font, "PAUSED", 0, color);
	_FontTex = SDL_CreateTextureFromSurface(_Window, text);
	SDL_DestroySurface(text);

	_MenuList.Populate({ "Resume","Restart","Quit to Menu" });
	//_MenuList.Format( _Font, _Window->getSize().x / 2.f, (_Window->getSize().y / 2.f) - 50.f, SFMLMenuList::Center);
	int w, h;
	SDL_GetRenderOutputSize(_Window, &w, &h);
	_MenuList.Format(_Window, _Font, w / 2.f, (h / 2.f) - 50.f, SDLMenuList::Center);
	_MenuList.SetBuffers(10.f, 50.f);
	TTF_CloseFont(_Font);

	//_MenuMoveSFX.loadFromFile("MenuMove.wav");
	//_MenuSelectSFX.loadFromFile("MenuSelect.wav");
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
	//sf::Event Event;
	SDL_Event e;
	//while (_Window->pollEvent(Event))
	while(SDL_PollEvent(&e))
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
			//if ((_Player.getStatus() != sf::Sound::Playing) && (Config::C()->_SFXOn))
			//	_Player.play();
		}
	}
};
void PauseScene::DrawScreen()
{

	GetParent()->DrawScreen();
	/*
	sf::RectangleShape back;
	back.setFillColor(sf::Color::Black);
	back.setOutlineThickness(5.f);
	back.setOutlineColor(sf::Color::White);
	back.setSize(sf::Vector2f(200.f, 300.f));
	back.setPosition((_Window->getSize().x - back.getSize().x) / 2.f, (_Window->getSize().y - back.getSize().y) / 2.f);
	_Window->draw(back);
	*/
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

	//sf::Text pauseText;
	//pauseText.setString("PAUSED");
	//pauseText.setFont(_Font);
	//pauseText.setPosition((_Window->getSize().x - pauseText.getLocalBounds().width) / 2.f, (_Window->getSize().y / 2.f) - 100.f);
	//_Window->draw(pauseText);

	_MenuList.Draw(_Window);
	
};