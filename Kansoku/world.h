#pragma once
#include <vector>
#include "intersectable.h"
#include "triangle.h"

class world
{
public:
	std::vector<intersectable*> intersects;
	vec3 light = vec3(0, 100, 0);

	world();
	~world();

	void a_rectangle(const vec3 &topleft, const vec3 &bottomright, const SDL_Color &color);
	intersection min_intersection(const ray3 &r);
};

