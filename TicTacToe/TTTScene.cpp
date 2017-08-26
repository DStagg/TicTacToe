#include "TTTScene.h"

TTTScene::TTTScene(sf::RenderWindow* win)
{
	_Window = win;
};
TTTScene::~TTTScene()
{

};

void TTTScene::Begin()
{
	_DelayTimer = 0.0f;
	_PlayerTurn = true;

	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			_Cells[x][y] = 0;

	sf::Color transparent(163, 73, 164);
	sf::Image img;
	if ((!img.loadFromFile("Pieces.png")) || (img.getSize().x != 256 ) || (img.getSize().y != 128 ) )
	{
		img.create(256, 128, sf::Color::Blue);
		for (int x = 128; x < 256; x++)
			for (int y = 0; y < 128; y++)
				img.setPixel(x, y, sf::Color::Red);
	}
	img.createMaskFromColor(transparent);
	_X.loadFromImage(img, sf::IntRect(0, 0, 128, 128));
	_O.loadFromImage(img, sf::IntRect(128,0,128,128));

	_Font.loadFromFile("Roboto-Regular.ttf");

	int width = (_XMargin * 2) + (_XBuffer * 4) + (_X.getSize().x * 3 );
	int height = (_YMargin * 2) + (_YBuffer * 4) + (_X.getSize().y * 3);

	if (_Window == 0)
	{
		_Window = new sf::RenderWindow();
		_Window->create(sf::VideoMode(width, height), "Tic-Tac-Toe");
	}
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

	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
		{
			GetManager()->Quit();
		}
		else if ((Event.type == sf::Event::MouseButtonPressed) && (Event.mouseButton.button == sf::Mouse::Left) )
		{
			if (CheckForWin())
				break;

			if (_DelayTimer < _TurnDelay)
				break;

			_DelayTimer = 0.f;
			int col = (sf::Mouse::getPosition(*_Window).x - _XMargin) / (_XBuffer + _X.getSize().x);
			int row = (sf::Mouse::getPosition(*_Window).y - _YMargin) / (_YBuffer + _X.getSize().y);

			if ((col < 0) || (col >= 3) || (row < 0) || (row >= 3))
				break;

			if (_Cells[col][row] == 0)
			{
				_Cells[col][row] = (_PlayerTurn) ? 1 : 2;
				_PlayerTurn = !_PlayerTurn;
			}
		}
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::R))
		{
			for (int x = 0; x < 3; x++)
				for (int y = 0; y < 3; y++)
					_Cells[x][y] = 0;
			_PlayerTurn = true;
		}
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
		{
			GetManager()->PushScene(new PauseScene(_Window));
		}
	}

};
void TTTScene::DrawScreen()
{

	for (int x = 0; x < 3; x++)
	{
		if (x != 2)
		{
			sf::RectangleShape coldiv;
			coldiv.setSize(sf::Vector2f(_XBuffer, (_XBuffer * 2) + (_X.getSize().y * 3)));
			coldiv.setPosition(_XMargin + ((x + 1)*(_X.getSize().x + _XBuffer)), _YMargin + _YBuffer);
			coldiv.setFillColor(sf::Color::White);
			_Window->draw(coldiv);

			sf::RectangleShape rowdiv;
			rowdiv.setSize(sf::Vector2f((_YBuffer * 2) + (_X.getSize().x * 3), _YBuffer));
			rowdiv.setPosition( _XMargin + _XBuffer, _YMargin + ((x + 1)*(_X.getSize().y + _YBuffer)));
			rowdiv.setFillColor(sf::Color::White);
			_Window->draw(rowdiv);
		}

		for (int y = 0; y < 3; y++)
		{
			if (_Cells[x][y] == 0)
				continue;
			sf::Sprite cellSprite;
			cellSprite.setPosition((float)(_XMargin + (x * _X.getSize().x) + ((x + 1) * _XBuffer)),
				(float)(_YMargin + (y * _X.getSize().y) + ((y + 1) * _YBuffer)));
			if (_Cells[x][y] == 1)
				cellSprite.setTexture(_X);
			else
				cellSprite.setTexture(_O);
			_Window->draw(cellSprite);
		}
	}

	if (CheckForWin() == 0)
	{
		sf::Text turntext;
		turntext.setString("Turn: Player " + IntToString(_PlayerTurn ? 1 : 2 ));
		turntext.setFont(_Font);
		turntext.setPosition((_Window->getSize().x - turntext.getLocalBounds().width) / 2.f, (_YMargin - turntext.getLocalBounds().height) / 2.f);
		_Window->draw(turntext);
	}
	else if ((CheckForWin() == 1) || (CheckForWin() == 2 ) )
	{
		sf::Text victorytext;
		victorytext.setString("Victory to Player " + IntToString(CheckForWin()));
		victorytext.setFont(_Font);
		victorytext.setPosition((_Window->getSize().x - victorytext.getLocalBounds().width) / 2.f, (_YMargin - victorytext.getLocalBounds().height) / 2.f);
		_Window->draw(victorytext);
	}
	else if (CheckForWin() == 3)
	{
		sf::Text drawtext;
		drawtext.setString("Draw");
		drawtext.setFont(_Font);
		drawtext.setPosition((_Window->getSize().x - drawtext.getLocalBounds().width) / 2.f, (_YMargin - drawtext.getLocalBounds().height) / 2.f);
		_Window->draw(drawtext);
	}

};

int TTTScene::CheckForWin()
{
	for (int check = 1; check <= 2; check++)
	{
		for (int x = 0; x < 3; x++)
		{
			if ((_Cells[x][0] == check) && (_Cells[x][1] == check) && (_Cells[x][2] == check))
				return check;
		}
		for (int y = 0; y < 3; y++)
		{
			if ((_Cells[0][y] == check) && (_Cells[1][y] == check) && (_Cells[2][y] == check))
				return check;
		}
		if ((_Cells[0][0] == check) && (_Cells[1][1] == check) && (_Cells[2][2] == check))
			return check;
		if ((_Cells[2][0] == check) && (_Cells[1][1] == check) && (_Cells[0][2] == check))
			return check;
	}

	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			if (_Cells[x][y] == 0)
				return 0;	//	Ongoing

	return 3;	//	Draw
};