#include "plane.h"


plane::plane(ray3 plane_ray, SDL_Color color) : primitive(color), plane_ray(plane_ray)
{
}

plane::~plane()
{
}

bool plane::operator==(const primitive& o)
{
	// TODO
	return false;
}

intersection plane::get_intersection(const ray3& r)
{
	float denom = vec3::dot(plane_ray.dir, r.dir);
	if (denom < 0.00001f)
		return intersection(r, r.pos, this, -1, color);
	vec3 p0l0 = plane_ray.pos - r.pos;
	float t = vec3::dot(p0l0, plane_ray.dir) / denom;
	return intersection(r, r.get_point(t), this, t, color);
}
