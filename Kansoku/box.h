#pragma once
#include <SDL.h>
#include "primitive.h"

struct box : primitive
{
	vec3 min;
	vec3 max;

	box(vec3 minbound, vec3 maxbound, SDL_Color color);
	box(vec3 minbound, vec3 maxbound);
	~box();

	bool operator==(const primitive &o) override;
	intersection get_intersection(const ray3 &ray) override;
	box get_bounds() override;
};

