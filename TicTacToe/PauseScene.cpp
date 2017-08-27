#include "PauseScene.h"

PauseScene::PauseScene(sf::RenderWindow* win)
{
	_Window = win;
};
PauseScene::~PauseScene()
{

};

void PauseScene::Begin()
{
	_Font.loadFromFile("Roboto-Regular.ttf");

	std::vector<std::string> list;
	list.push_back("Resume");
	list.push_back("Restart");
	list.push_back("Quit to Menu");
	_MenuList.Create(list, _Font, false, _Window->getSize().x / 2.f, (_Window->getSize().y / 2.f) - 50.f, SFMLMenuList::Center);
	_MenuList.SetBuffers(10.f, 50.f);

	_MenuMoveSFX.loadFromFile("MenuMove.wav");
	_MenuSelectSFX.loadFromFile("MenuSelect.wav");

	if (_Window == 0)
	{
		_Window = new sf::RenderWindow();
		_Window->create(sf::VideoMode(624, 624), "Tic-Tac-Toe");
	}

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
			if ((_Player.getStatus() != sf::Sound::Playing) && (Config::C()->_SFXOn))
				_Player.play();
		}
	}
};
void PauseScene::DrawScreen()
{

	GetParent()->DrawScreen();

	sf::RectangleShape back;
	back.setFillColor(sf::Color::Black);
	back.setOutlineThickness(5.f);
	back.setOutlineColor(sf::Color::White);
	back.setSize(sf::Vector2f(200.f, 300.f));
	back.setPosition((_Window->getSize().x - back.getSize().x) / 2.f, (_Window->getSize().y - back.getSize().y) / 2.f);
	_Window->draw(back);

	sf::Text pauseText;
	pauseText.setString("PAUSED");
	pauseText.setFont(_Font);
	pauseText.setPosition((_Window->getSize().x - pauseText.getLocalBounds().width) / 2.f, (_Window->getSize().y / 2.f) - 100.f);
	_Window->draw(pauseText);

	_MenuList.Draw(_Window);
	
};