#pragma once
#include <SDL.h>

struct intersectable;

#include "ray3.h"

struct intersection
{
	ray3 ray;
	vec3 point;	
	const intersectable* object; 
	float distance;
	SDL_Color color;

	intersection(ray3 ray, vec3 point, const intersectable *object, float distance, SDL_Color color);
	~intersection();
};