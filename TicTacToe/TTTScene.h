#ifndef TTTSCENE_H
#define TTTSCENE_H

#include <SFML\Graphics.hpp>
#include "Utility.h"
#include "Scene.h"
#include "PauseScene.h"

class TTTScene : public Scene
{
public:

	TTTScene(sf::RenderWindow* win = 0);
	~TTTScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

	int CheckForWin();
	void Refresh();

private:

	float	_DelayTimer;
	float _TurnDelay = 0.5f;
	bool _PlayerTurn;

	sf::RenderWindow* _Window;
	sf::Texture _X;
	sf::Texture _O;
	sf::Font _Font;

	int _Cells[3][3];

	int _XMargin = 100;
	int _YMargin = 100;
	int _XBuffer = 10;
	int _YBuffer = 10;

	sf::SoundBuffer _PlaceSFX;
	sf::SoundBuffer _VictorySFX;
	sf::SoundBuffer _DrawSFX;
	sf::Sound _Player;

	bool _Done;

};

#endif