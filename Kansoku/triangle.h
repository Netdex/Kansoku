#pragma once
#include "primitive.h"
#include "box.h"

struct triangle : primitive
{
	vec3 a, b, c;

	triangle(vec3 a, vec3 b, vec3 c, SDL_Color color);
	~triangle();

	bool operator==(const primitive &o) override;

	intersection get_intersection(const ray3 &r) override;
	box get_bounds() override;

};

