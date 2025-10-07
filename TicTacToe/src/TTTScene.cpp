#include "TTTScene.h"

TTTScene::TTTScene(SDL_Renderer* win, MIX_Mixer* mix, MIX_Track* bgm)
{
	_Window = win;
	_Player = mix;
	_MusicTrack = bgm;
};
TTTScene::~TTTScene()
{

};

void TTTScene::Begin()
{
	_DelayTimer = 0.0f;
	_PlayerTurn = true;

	_Cells.Create(3, 3, 0);

	//sf::Color transparent(163, 73, 164);
	//sf::Image img;
	//if ((!img.loadFromFile("Pieces.png")) || (img.getSize().x != 256 ) || (img.getSize().y != 128 ) )
	//{
	//	img.create(256, 128, sf::Color::Blue);
	//	for (int x = 128; x < 256; x++)
	//		for (int y = 0; y < 128; y++)
	//			img.setPixel(x, y, sf::Color::Red);
	//}
	//img.createMaskFromColor(transparent);
	//_X.loadFromImage(img, sf::IntRect(0, 0, 128, 128));
	//_O.loadFromImage(img, sf::IntRect(128,0,128,128));

	//_Font.loadFromFile("Roboto-Regular.ttf");
	
	_Pieces = IMG_LoadTexture(_Window, "res/Pieces.png");
	if (!_Pieces) std::cout << "Failed to load texture 'Pieces': " << SDL_GetError() << std::endl;
	_X.w = _X.h = _O.w = _O.h = 128;
	_X.x = _X.y = _O.y = 0;
	_O.x = 128;

	//_PlaceSFX.loadFromFile("Place.wav");
	//_VictorySFX.loadFromFile("Victory.wav");
	//_DrawSFX.loadFromFile("Draw.wav");
	_PlaceSFX = MIX_LoadAudio(_Player, "res/Place.wav", true);
	if (!_PlaceSFX) std::cout << "Place failed to load." << std::endl;
	_VictorySFX = MIX_LoadAudio(_Player, "res/Victory.wav", true);
	if (!_VictorySFX) std::cout << "Victory failed to load." << std::endl;
	_DrawSFX = MIX_LoadAudio(_Player, "res/Draw.wav", true);
	if (!_DrawSFX) std::cout << "Draw failed to load." << std::endl;
	//_Music = MIX_LoadAudio(_Player, "res/Paradox.ogg", true);
	//if (!_Music) std::cout << "Music failed to load." << std::endl;
	//int width = (_XMargin * 2) + (_XBuffer * 4) + (_X.getSize().x * 3 );
	//int height = (_YMargin * 2) + (_YBuffer * 4) + (_X.getSize().y * 3);

	//_MusicTrack = MIX_CreateTrack(_Player);
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
	SDL_GetGlobalMouseState(&_MouseX, &_MouseY);
	_Done = false;

	_AI = new EasyAI();
};
void TTTScene::End()
{
	//MIX_StopTrack(_MusicTrack, 0);
};
void TTTScene::Pause()
{

};
void TTTScene::Resume()
{

};
void TTTScene::Update(float dt)
{
	_DelayTimer += dt;

	if (_PlayerTurn || _Done)
	{
		//sf::Event Event;
		SDL_Event e;
		//while (_Window->pollEvent(Event))
		while (SDL_PollEvent(&e))
		{
			//if (Event.type == sf::Event::Closed)
			if (e.type == SDL_EVENT_QUIT)
			{
				GetManager()->Quit();
			}
			//else if ((Event.type == sf::Event::MouseButtonPressed) && (Event.mouseButton.button == sf::Mouse::Left))
			else if ((e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) && (e.button.button == SDL_BUTTON_LEFT))
			{
				if (CheckForWin())
					break;

				if (_DelayTimer < _TurnDelay)
					break;

				_DelayTimer = 0.f;
				int w, h;
				SDL_GetRenderOutputSize(_Window, &w, &h);
				int col = (_MouseX - _XMargin) / (_XBuffer + _X.w);//(sf::Mouse::getPosition(*_Window).x - _XMargin) / (_XBuffer + _X.getSize().x);
				int row = (_MouseY - _YMargin) / (_YBuffer + _X.h);//(sf::Mouse::getPosition(*_Window).y - _YMargin) / (_YBuffer + _X.getSize().y);
				

				if ((_MouseX < _XMargin) || (_MouseY < _YMargin) || (col < 0) || (col >= 3) || (row < 0) || (row >= 3))
					break;

				if (_Cells.GetCell(col,row) == 0)
				{
					_Cells.SetCell(col, row, (_PlayerTurn) ? 1 : 2);
					_PlayerTurn = !_PlayerTurn;
					//_Player.setBuffer(_PlaceSFX);
					if (Config::C()->_SFXOn) MIX_PlayAudio(_Player, _PlaceSFX);
					//if ((_Player.getStatus() != sf::Sound::Playing) && (Config::C()->_SFXOn)) _Player.play();
				}
			}
			//else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::R))
			else if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_R))
			{
				Refresh();
			}
			//else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
			else if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_ESCAPE))
			{
				GetManager()->PushScene(new PauseScene(_Window, _Player));
			}
			else if (e.type == SDL_EVENT_MOUSE_MOTION)
			{
				_MouseX = e.motion.x;
				_MouseY = e.motion.y;
			}
		}
	}
	else if ((_DelayTimer >= _TurnDelay)&&(!_Done))
	{
		//	Where the AI acts
		_DelayTimer = 0.f;
		_AI->TakeMove(&_Cells);
		_PlayerTurn = !_PlayerTurn;
		if (Config::C()->_SFXOn) MIX_PlayAudio(_Player, _PlaceSFX);
		//_Player.setBuffer(_PlaceSFX);
		//if ((_Player.getStatus() != sf::Sound::Playing) && (Config::C()->_SFXOn)) _Player.play();
	}

	if ((!_Done)&& (CheckForWin() != 0))
	{
		//MIX_PauseTrack(_MusicTrack);
		//_Player.stop();
		if (CheckForWin() == 3 && Config::C()->_SFXOn) MIX_PlayAudio(_Player, _DrawSFX);//_Player.setBuffer(_DrawSFX);
		else if (Config::C()->_SFXOn) MIX_PlayAudio(_Player, _VictorySFX); //_Player.setBuffer(_VictorySFX);
		//if ( Config::C()->_SFXOn ) _Player.play();
		//MIX_ResumeTrack(_MusicTrack);
		_Done = true;
	}
	

};
void TTTScene::DrawScreen()
{

	for (int x = 0; x < 3; x++)
	{
		if (x != 2)
		{
			SDL_SetRenderDrawColor(_Window, 255, 255, 255, 255);

			SDL_FRect line;
			line.w = _XBuffer;
			line.h = (_XBuffer * 2) + (_X.h * 3);
			line.x = _XMargin + ((x + 1) * (_X.w + _XBuffer));
			line.y = _YMargin + _YBuffer;
			SDL_RenderFillRect(_Window, &line);

			line.w = (_YBuffer * 2) + (_X.w * 3);
			line.h = _YBuffer;
			line.x = _XMargin + _XBuffer;
			line.y = _YMargin + ((x + 1) * (_X.h + _YBuffer));
			SDL_RenderFillRect(_Window, &line);

			//sf::RectangleShape coldiv;
			//coldiv.setSize(sf::Vector2f(_XBuffer, (_XBuffer * 2) + (_X.getSize().y * 3)));
			//coldiv.setPosition(_XMargin + ((x + 1)*(_X.getSize().x + _XBuffer)), _YMargin + _YBuffer);
			//coldiv.setFillColor(sf::Color::White);
			//_Window->draw(coldiv);

			//sf::RectangleShape rowdiv;
			//rowdiv.setSize(sf::Vector2f((_YBuffer * 2) + (_X.getSize().x * 3), _YBuffer));
			//rowdiv.setPosition( _XMargin + _XBuffer, _YMargin + ((x + 1)*(_X.getSize().y + _YBuffer)));
			//rowdiv.setFillColor(sf::Color::White);
			//_Window->draw(rowdiv);
		}

		for (int y = 0; y < 3; y++)
		{
			if (_Cells.GetCell(x,y) == 0)
				continue;
			//sf::Sprite cellSprite;
			SDL_FRect cellSprite;
			cellSprite.x = _XMargin + (x * _X.w) + ((x + 1) * _XBuffer);
			cellSprite.y = _YMargin + (y * _X.h) + ((y + 1) * _YBuffer);
			cellSprite.w = _X.w;
			cellSprite.h = _X.h;
			//cellSprite.setPosition((float)(_XMargin + (x * _X.getSize().x) + ((x + 1) * _XBuffer)),
			//	(float)(_YMargin + (y * _X.getSize().y) + ((y + 1) * _YBuffer)));
			if (_Cells.GetCell(x, y) == 1)
				SDL_RenderTexture(_Window, _Pieces, &_X, &cellSprite);
				//cellSprite.setTexture(_X);
			else
				SDL_RenderTexture(_Window, _Pieces, &_O, &cellSprite);
				//cellSprite.setTexture(_O);
			//_Window->draw(cellSprite);
		}
	}

	if (CheckForWin() == 0)
	{
		//sf::Text turntext;
		//turntext.setString("Turn: Player " + IntToString(_PlayerTurn ? 1 : 2 ));
		//turntext.setFont(_Font);
		//turntext.setPosition((_Window->getSize().x - turntext.getLocalBounds().width) / 2.f, (_YMargin - turntext.getLocalBounds().height) / 2.f);
		//_Window->draw(turntext);
		int w, h;
		SDL_GetRenderOutputSize(_Window, &w, &h);
		SDL_SetRenderDrawColor(_Window, 255, 255, 255, 255);
		std::stringstream msg;
		msg << "Turn: Player " << (_PlayerTurn ? 1 : 2);
		SDL_RenderDebugTextFormat(_Window,
			(w - 40.f) / 2.f,
			(_YMargin - 140.f) / 2.f,
			msg.str().c_str());
	}
	else if ((CheckForWin() == 1) || (CheckForWin() == 2 ) )
	{
		//sf::Text victorytext;
		//victorytext.setString("Victory to Player " + IntToString(CheckForWin()));
		//victorytext.setFont(_Font);
		//victorytext.setPosition((_Window->getSize().x - victorytext.getLocalBounds().width) / 2.f, (_YMargin - victorytext.getLocalBounds().height) / 2.f);
		//_Window->draw(victorytext);
		int w, h;
		SDL_GetRenderOutputSize(_Window, &w, &h);
		SDL_SetRenderDrawColor(_Window, 255, 255, 255, 255);
		std::stringstream msg;
		msg << "Victory to Player " << CheckForWin();
		SDL_RenderDebugTextFormat(_Window,
			(w - 40.f) / 2.f,
			(_YMargin - 10.f) / 2.f,
			msg.str().c_str() );
	}
	else if (CheckForWin() == 3)
	{
		//sf::Text drawtext;
		//drawtext.setString("Draw");
		//drawtext.setFont(_Font);
		//drawtext.setPosition((_Window->getSize().x - drawtext.getLocalBounds().width) / 2.f, (_YMargin - drawtext.getLocalBounds().height) / 2.f);
		//_Window->draw(drawtext);
		int w, h;
		SDL_GetRenderOutputSize(_Window, &w, &h);
		SDL_SetRenderDrawColor(_Window, 255, 255, 255, 255);
		SDL_RenderDebugTextFormat(_Window,
			(w - 40.f) / 2.f,
			(_YMargin - 10.f) / 2.f,
			"Draw");
	}

};

int TTTScene::CheckForWin()
{
	for (int check = 1; check <= 2; check++)
	{
		for (int x = 0; x < 3; x++)
		{
			if ((_Cells.GetCell(x,0) == check) && (_Cells.GetCell(x,1) == check) && (_Cells.GetCell(x,2) == check))
				return check;
		}
		for (int y = 0; y < 3; y++)
		{
			if ((_Cells.GetCell(0,y) == check) && (_Cells.GetCell(1,y) == check) && (_Cells.GetCell(2,y) == check))
				return check;
		}
		if ((_Cells.GetCell(0,0) == check) && (_Cells.GetCell(1,1) == check) && (_Cells.GetCell(2,2) == check))
			return check;
		if ((_Cells.GetCell(2,0) == check) && (_Cells.GetCell(1,1) == check) && (_Cells.GetCell(0,2) == check))
			return check;
	}

	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			if (_Cells.GetCell(x,y) == 0)
				return 0;	//	Ongoing

	return 3;	//	Draw
};

void TTTScene::Refresh()
{
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			_Cells.SetCell(x,y,0);
	_PlayerTurn = true;
	_Done = false;
};