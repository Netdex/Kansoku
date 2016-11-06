#pragma once
#include <SDL.h>
#include "primitive.h"

struct box : primitive
{
	vec3 bounds[2];

	box(vec3 minbound, vec3 maxbound, SDL_Color color);
	~box();

	bool operator==(const primitive &o) override;
	intersection get_intersection(ray3 &ray) override;
};

