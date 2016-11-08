#include "box.h"
#include "intersection.h"
#include <algorithm>


box::box(vec3 a, vec3 b, SDL_Color color) : primitive(color)
{
	min = vec3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
	max = vec3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

box::box(vec3 a, vec3 b) : box(a, b, {0,0,0,0})
{
}

box::~box()
{
}

bool box::operator==(const primitive& o)
{
	const box *op = dynamic_cast<const box*>(&o);
	if (op)
		return op->min == min && op->max == max;
	return false;
}

int sgn(float x)
{
	if (x < 0) return 1;
	return 0;
}

intersection box::get_intersection(const ray3 &r)
{
	float tx1 = (min.x - r.pos.x) / r.dir.x;
	float tx2 = (max.x - r.pos.x) / r.dir.x;

	float tmin = std::min(tx1, tx2);
	float tmax = std::max(tx1, tx2);

	float ty1 = (min.y - r.pos.y) / r.dir.y;
	float ty2 = (max.y - r.pos.y) / r.dir.y;

	tmin = std::max(tmin, std::min(ty1, ty2));
	tmax = std::min(tmax, std::max(ty1, ty2));

	float tz1 = (min.z - r.pos.z) / r.dir.z;
	float tz2 = (max.z - r.pos.z) / r.dir.z;

	tmin = std::max(tmin, std::min(tz1, tz2));
	tmax = std::min(tmax, std::max(tz1, tz2));

	if (tmax >= tmin)
		return intersection(r, r.get_point(tmin), this, tmin, this->color);
	return intersection(r, r.pos, this, -1, this->color);
}

box box::get_bounds()
{
	return *this;
}
