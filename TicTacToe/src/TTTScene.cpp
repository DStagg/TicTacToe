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

	_Pieces = IMG_LoadTexture(_Window, "res/Pieces.png");
	if (!_Pieces) std::cout << "Failed to load texture 'Pieces': " << SDL_GetError() << std::endl;
	_X.w = _X.h = _O.w = _O.h = 128;
	_X.x = _X.y = _O.y = 0;
	_O.x = 128;

	_PlaceSFX = MIX_LoadAudio(_Player, "res/Place.wav", true);
	if (!_PlaceSFX) std::cout << "Place failed to load." << std::endl;
	_VictorySFX = MIX_LoadAudio(_Player, "res/Victory.wav", true);
	if (!_VictorySFX) std::cout << "Victory failed to load." << std::endl;
	_DrawSFX = MIX_LoadAudio(_Player, "res/Draw.wav", true);
	if (!_DrawSFX) std::cout << "Draw failed to load." << std::endl;

	SDL_GetGlobalMouseState(&_MouseX, &_MouseY);
	_Done = false;

	_AI = new EasyAI();
};
void TTTScene::End()
{

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
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_EVENT_QUIT)
			{
				GetManager()->Quit();
			}
			else if ((e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) && (e.button.button == SDL_BUTTON_LEFT))
			{
				if (CheckForWin())
					break;

				if (_DelayTimer < _TurnDelay)
					break;

				_DelayTimer = 0.f;
				int w, h;
				SDL_GetRenderOutputSize(_Window, &w, &h);
				int col = (_MouseX - _XMargin) / (_XBuffer + _X.w);
				int row = (_MouseY - _YMargin) / (_YBuffer + _X.h);
				

				if ((_MouseX < _XMargin) || (_MouseY < _YMargin) || (col < 0) || (col >= 3) || (row < 0) || (row >= 3))
					break;

				if (_Cells.GetCell(col,row) == 0)
				{
					_Cells.SetCell(col, row, (_PlayerTurn) ? 1 : 2);
					_PlayerTurn = !_PlayerTurn;
					if (Config::C()->_SFXOn) MIX_PlayAudio(_Player, _PlaceSFX);
				}
			}
			else if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_R))
			{
				Refresh();
			}
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
	}

	if ((!_Done)&& (CheckForWin() != 0))
	{
		if (CheckForWin() == 3 && Config::C()->_SFXOn) MIX_PlayAudio(_Player, _DrawSFX);
		else if (Config::C()->_SFXOn) MIX_PlayAudio(_Player, _VictorySFX);

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
		}

		for (int y = 0; y < 3; y++)
		{
			if (_Cells.GetCell(x,y) == 0)
				continue;

			SDL_FRect cellSprite;
			cellSprite.x = _XMargin + (x * _X.w) + ((x + 1) * _XBuffer);
			cellSprite.y = _YMargin + (y * _X.h) + ((y + 1) * _YBuffer);
			cellSprite.w = _X.w;
			cellSprite.h = _X.h;

			if (_Cells.GetCell(x, y) == 1)
				SDL_RenderTexture(_Window, _Pieces, &_X, &cellSprite);
			else
				SDL_RenderTexture(_Window, _Pieces, &_O, &cellSprite);
		}
	}

	if (CheckForWin() == 0)
	{
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