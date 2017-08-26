#include "ConfigScene.h"

ConfigScene::ConfigScene(sf::RenderWindow* win, sf::Music* bgm)
{
	_Window = win;
	_BackgroundMusic = bgm;
};
ConfigScene::~ConfigScene()
{

};

void ConfigScene::Begin()
{
	if (_Window == 0)
	{
		_Window = new sf::RenderWindow();
		_Window->create(sf::VideoMode(624, 624), "Tic-Tac-Toe");
	}

	_Font.loadFromFile("Roboto-regular.ttf");
	_MenuChoice = 0;
	_MenuMoveSFX.loadFromFile("MenuMove.wav");
	_MenuSelectSFX.loadFromFile("MenuSelect.wav");
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
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
		{
			SetRunning(false);
		}
		else if (Event.type == sf::Event::KeyPressed)
		{
			switch (Event.key.code)
			{
			case sf::Keyboard::Up:
				_MenuChoice -= 1;
				if (_MenuChoice < 0) _MenuChoice = 0;
				_Player.setBuffer(_MenuMoveSFX);
				break;
			case sf::Keyboard::Down:
				_MenuChoice += 1;
				if (_MenuChoice > 2) _MenuChoice = 2;
				_Player.setBuffer(_MenuMoveSFX);
				break;
			case sf::Keyboard::Return:
				_Player.setBuffer(_MenuSelectSFX);
				if (_MenuChoice == 0)
				{
					Config::C()->_MusicOn = !Config::C()->_MusicOn;
					if ((_BackgroundMusic != 0) && (Config::C()->_MusicOn))
						_BackgroundMusic->play();
					else if ((_BackgroundMusic != 0) && (!Config::C()->_MusicOn))
						_BackgroundMusic->stop();
				}
				else if (_MenuChoice == 1) Config::C()->_SFXOn = !Config::C()->_SFXOn;
				else if (_MenuChoice == 2) GetManager()->Quit(1);
				break;
			default:
				break;
			}
			if ((_Player.getStatus() != sf::Sound::Playing) && (Config::C()->_SFXOn) )
				_Player.play();
		}
	}
};
void ConfigScene::DrawScreen()
{
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

	sf::Text quitText;
	quitText.setString("Quit");
	quitText.setFont(_Font);
	if (_MenuChoice == 2) quitText.setStyle(sf::Text::Underlined);
	quitText.setPosition((_Window->getSize().x - quitText.getLocalBounds().width) / 2.f, (_Window->getSize().y / 2.f) + 50.f);
	_Window->draw(quitText);
};