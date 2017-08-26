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

	if (_Window == 0 )
		_Window->create(sf::VideoMode(624, 624), "Tic-Tac-Toe");

	_MenuChoice = 0;
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
				_MenuChoice = 0;
				break;
			case sf::Keyboard::Down:
				_MenuChoice = 1;
				break;
			case sf::Keyboard::Return:
				if (_MenuChoice == 0) SetRunning(false);
				else if (_MenuChoice == 1) GetManager()->Quit(2);
				break;
			default:
				break;
			}
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
	back.setSize(sf::Vector2f(200.f, 200.f));
	back.setPosition((_Window->getSize().x - back.getSize().x) / 2.f, (_Window->getSize().y - back.getSize().y) / 2.f);
	_Window->draw(back);

	sf::Text pauseText;
	pauseText.setString("PAUSED");
	pauseText.setFont(_Font);
	pauseText.setPosition((_Window->getSize().x - pauseText.getLocalBounds().width) / 2.f, (_Window->getSize().y / 2.f) - 75.f);
	_Window->draw(pauseText);

	sf::Text resumeText;
	resumeText.setString("Resume");
	resumeText.setFont(_Font);
	if (_MenuChoice == 0) resumeText.setStyle(sf::Text::Underlined);
	resumeText.setPosition((_Window->getSize().x - resumeText.getLocalBounds().width) / 2.f, (_Window->getSize().y / 2.f));
	_Window->draw(resumeText);

	sf::Text quitText;
	quitText.setString("Quit");
	quitText.setFont(_Font);
	if (_MenuChoice == 1) quitText.setStyle(sf::Text::Underlined);
	quitText.setPosition((_Window->getSize().x - quitText.getLocalBounds().width) / 2.f, (_Window->getSize().y / 2.f) + 50.f);
	_Window->draw(quitText);

};