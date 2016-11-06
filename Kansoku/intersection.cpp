#include "intersection.h"

intersection::intersection(ray3 ray, vec3 point, const intersectable &object, float distance, SDL_Color color)
	:ray(ray), point(point), object(object), distance(distance), color(color)
{
}


intersection::~intersection()
{
}
