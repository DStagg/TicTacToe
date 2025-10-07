#pragma once

#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

class MenuList
{
public:

	MenuList();
	~MenuList();

	void Populate(std::vector<std::string> list);

	int GetChoice();
	void SetChoice(int choice);
	void IncChoice();
	void DecChoice();

	void SetLoop(bool b);
	bool GetLoop();

	int CountList();
	std::string GetList(int id);
	void SetList(int id, std::string text);

protected:

	int _Choice;
	bool _Loop;
	std::vector<std::string> _List;
};

class SDLMenuList : public MenuList
{
public:

	SDLMenuList();
	~SDLMenuList();

	void Format(SDL_Renderer* renderer, TTF_Font* font, float x = 0.f, float y = 0.f, int orientation = SDLMenuList::Left);

	void SetBuffers(float x, float y);

	void Draw(SDL_Renderer* renderer);

	enum Orientation
	{
		Left,
		Center,
		Right
	};

private:

	float _XBuffer, _YBuffer;
	float _X, _Y;
	TTF_Font* _Font;
	int _Orientation;
	std::vector<SDL_Texture*> _Textures;
};
