#pragma once
#include "intersectable.h"
#include <SDL.h>

struct primitive : intersectable
{
	SDL_Color color;

	primitive(SDL_Color color);
	virtual ~primitive();

	virtual bool operator==(const primitive &o) const = 0;
};

