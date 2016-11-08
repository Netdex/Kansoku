#pragma once
#include "primitive.h"
#include "box.h"

struct plane : intersectable
{
	ray3 plane_ray;
	SDL_Color color;

	plane(ray3 plane_ray, SDL_Color color);
	~plane();

	intersection get_intersection(const ray3 &ray) override;
};

