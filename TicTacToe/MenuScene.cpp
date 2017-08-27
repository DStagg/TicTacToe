#include "MenuScene.h"

MenuScene::MenuScene(sf::RenderWindow* win)
{
	_Window = win;
};
MenuScene::~MenuScene()
{

};

void MenuScene::Begin()
{
	_Font.loadFromFile("Roboto-Regular.ttf");

	_MenuList.Populate({ "Play","Config","Quit" });
	_MenuList.Format(_Font, _Window->getSize().x / 2.f, _Window->getSize().y / 2.f, SFMLMenuList::Center);
	_MenuList.SetBuffers(10.f, 50.f);

	if (!_MenuMoveSFX.loadFromFile("MenuMove.wav"))
		std::cout << "MenuMove.wav failed to load!" << std::endl;
	if (!_MenuSelectSFX.loadFromFile("MenuSelect.wav"))
		std::cout << "MenuSelect.wav failed to load!" << std::endl;

	if ( _Window == 0 )
		_Window->create(sf::VideoMode(624, 624), "Tic-Tac-Toe");

	if (!_Music.openFromFile("Paradox.ogg"))
		std::cout << "Paradox.ogg failed to load!" << std::endl;
	_Music.setVolume(25.f);

	if (Config::C()->_MusicOn)
		_Music.play();
};
void MenuScene::End()
{
	_Music.stop();
};
void MenuScene::Pause()
{

};
void MenuScene::Resume()
{
	if (!Config::C()->_MusicOn) _Music.stop();
	else if (_Music.getStatus() != sf::Music::Playing) _Music.play();
};
void MenuScene::Update(float dt)
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
					GetManager()->PushScene(new TTTScene(_Window));
					break;
				case 1:
					GetManager()->PushScene(new ConfigScene(_Window, &_Music));
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
			if ((_Player.getStatus() != sf::Sound::Playing) && (Config::C()->_SFXOn))
				_Player.play();
		}
	}
};
void MenuScene::DrawScreen()
{
	sf::Text titleText;
	titleText.setString("TIC-TAC-TOE");
	titleText.setFont(_Font);
	titleText.setPosition((_Window->getSize().x - titleText.getLocalBounds().width) / 2.f, titleText.getLocalBounds().height);
	_Window->draw(titleText);

	_MenuList.Draw(_Window);
};