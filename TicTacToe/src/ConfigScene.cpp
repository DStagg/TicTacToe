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

	_MenuList.Populate({ "Music","SFX","AI","Quit" });
	_MenuList.Format( _Font, (_Window->getSize().x / 2.f), (_Window->getSize().y / 2.f) - 100.f, SFMLMenuList::Center);
	_MenuList.SetBuffers(10.f, 50.f);

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
				_MenuList.DecChoice();
				_Player.setBuffer(_MenuMoveSFX);
				break;
			case sf::Keyboard::Down:
				_MenuList.IncChoice();
				_Player.setBuffer(_MenuMoveSFX);
				break;
			case sf::Keyboard::Return:
				_Player.setBuffer(_MenuSelectSFX);
				switch (_MenuList.GetChoice())
				{
				case 0:
					Config::C()->_MusicOn = !Config::C()->_MusicOn;
					if ((_BackgroundMusic != 0) && (Config::C()->_MusicOn))
						_BackgroundMusic->play();
					else if ((_BackgroundMusic != 0) && (!Config::C()->_MusicOn))
						_BackgroundMusic->stop();
					break;
				case 1:
					Config::C()->_SFXOn = !Config::C()->_SFXOn;
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
			if ((_Player.getStatus() != sf::Sound::Playing) && (Config::C()->_SFXOn) )
				_Player.play();
		}
	}

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
	sf::Text titleText;
	titleText.setString("Config");
	titleText.setFont(_Font);
	titleText.setPosition((_Window->getSize().x - titleText.getLocalBounds().width) / 2.f, titleText.getLocalBounds().height);
	_Window->draw(titleText);
	
	_MenuList.Draw(_Window);

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