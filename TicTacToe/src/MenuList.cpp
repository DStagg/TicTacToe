#include "MenuList.h"

MenuList::MenuList()
{
	
};
MenuList::~MenuList()
{

};

void MenuList::Populate(std::vector<std::string> list)
{
	_List = list;
	SetChoice(0);
};

int MenuList::GetChoice()
{
	return _Choice;
};
void MenuList::SetChoice(int c)
{
	if (c < 0)
		c = 0;
	else if ((int)_List.size() == 0)
		c = 0;
	else if (c >= (int)_List.size())
		c = (int)_List.size() - 1;
	
	_Choice = c;
};
void MenuList::IncChoice()
{
	_Choice++;
	if (_Choice >= (int)_List.size())
	{
		if (GetLoop())
			SetChoice(0);
		else
			SetChoice((int)_List.size() - 1);
	}
};
void MenuList::DecChoice()
{
	_Choice--;
	if (_Choice < 0)
	{
		if (GetLoop())
			SetChoice((int)_List.size() - 1);
		else
			SetChoice(0);
	}
};

void MenuList::SetLoop(bool b)
{
	_Loop = b;
};
bool MenuList::GetLoop()
{
	return _Loop;
};

int MenuList::CountList()
{
	return (int)_List.size();
};
std::string MenuList::GetList(int id)
{
	if (id < 0)
		id = 0;
	if (id >= CountList())
		id = CountList() - 1;

	return _List[id];
};
void MenuList::SetList(int id, std::string tex)
{
	if (id < 0)
		id = 0;
	if (id >= CountList())
		id = CountList() - 1;

	_List[id] = tex;
};

///
/*
SFMLMenuList::SFMLMenuList()
{
	
};
SFMLMenuList::~SFMLMenuList()
{

};

void SFMLMenuList::Format(sf::Font font, float x, float y, int orientation)
{
	_Font = font;
	_X = x;
	_Y = y;
	_Orientation = orientation;
}

void SFMLMenuList::SetBuffers(float x, float y)
{
	_XBuffer = x;
	_YBuffer = y;
};

void SFMLMenuList::Draw(sf::RenderWindow* rw)
{
	for (int i = 0; i < CountList(); i++)
	{
		sf::Text tex;
		tex.setString(GetList(i));
		tex.setFont(_Font);
		if (i == GetChoice())
			tex.setStyle(sf::Text::Underlined);
		
		if (_Orientation == SFMLMenuList::Left)
			tex.setPosition(_X + _XBuffer, _Y + (i * _YBuffer));
		else if (_Orientation == SFMLMenuList::Center)
			tex.setPosition(_X - (tex.getLocalBounds().width / 2.f), _Y + (i * _YBuffer));
		else
			tex.setPosition(_X - (tex.getLocalBounds().width + _XBuffer), _Y + (i * _YBuffer));

		rw->draw(tex);
	};
};
*/
SDLMenuList::SDLMenuList()
{

};
SDLMenuList::~SDLMenuList()
{

};

void SDLMenuList::Format(SDL_Renderer* renderer, TTF_Font* font, float x, float y, int orientation)
{
	_Font = font;
	_X = x;
	_Y = y;
	_Orientation = orientation;

	if (CountList() == 0) return;

	for (int i = 0; i < CountList(); i++)
	{
		std::string msg = GetList(i);
		SDL_Color color;
		color.r = color.g = color.b = color.a = 255;
		SDL_Surface* text = TTF_RenderText_Blended(_Font, msg.c_str(), 0, color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text);
		SDL_DestroySurface(text);
		_Textures.push_back(texture);
	}
}

void SDLMenuList::SetBuffers(float x, float y)
{
	_XBuffer = x;
	_YBuffer = y;
};

void SDLMenuList::Draw(SDL_Renderer* renderer)
{
	for (int i = 0; i < CountList(); i++)
	{
		SDL_FRect dstrect;
		switch (_Orientation)
		{
		case SDLMenuList::Left:
			dstrect.x = _X + _XBuffer;
			break;
		case SDLMenuList::Center:
			dstrect.x = _X - (_Textures[i]->w / 2.f);
			break;
		default:
			dstrect.x = _X - (_Textures[i]->w + _XBuffer);
			break;
		}
		dstrect.y = _Y + (i * _YBuffer);
		dstrect.w = _Textures[i]->w;
		dstrect.h = _Textures[i]->h;

		if (i == GetChoice())
		{
			dstrect.x -= 10.f;
			dstrect.y -= 10.f;
			dstrect.w += 20.f;
			dstrect.h += 20.f;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderRect(renderer, &dstrect);
		}

		SDL_RenderTexture(renderer, _Textures[i], NULL, &dstrect);
	};
};