#pragma once
#include "intersectable.h"
#include <SDL.h>

struct box;

struct primitive : intersectable
{
	SDL_Color color;

	primitive(SDL_Color color);
	virtual ~primitive();

	virtual bool operator==(const primitive &o) = 0;
	virtual box get_bounds() = 0;
};

