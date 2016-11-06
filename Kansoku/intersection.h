#pragma once
#include "ray3.h"
#include "intersectable.h"
#include <SDL.h>
#include "box.h"

struct intersection
{
	ray3 ray;
	vec3 point;	
	intersectable& object; 
	float distance;
	SDL_Color color;

	intersection(ray3 ray, vec3 point, intersectable &object, float distance, SDL_Color color);
	~intersection();
};

const static intersection NO_INTERSECTION = intersection(ray3(), vec3(), box(vec3(), vec3(), SDL_Color()), -9999, SDL_Color());