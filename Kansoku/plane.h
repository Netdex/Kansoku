#pragma once
#include "primitive.h"
struct plane : primitive
{
	ray3 plane_ray;

	plane(ray3 plane_ray, SDL_Color color);
	~plane();

	intersection get_intersection(const ray3 &ray) override;
};

