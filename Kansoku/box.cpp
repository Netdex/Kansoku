#include "box.h"
#include "intersection.h"


box::box(vec3 minbound, vec3 maxbound, SDL_Color color) : primitive(color)
{
	bounds[0] = minbound;
	bounds[1] = maxbound;
}


box::~box()
{
}

bool box::operator==(const primitive& o)
{
	const box *op = dynamic_cast<const box*>(&o);
	if(op)
		return op->bounds[0] == bounds[0] && op->bounds[1] == bounds[1];
	return false;
}

intersection box::get_intersection(ray3& r)
{
	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	vec3 invdir = vec3(1 / r.dir.x, 1 / r.dir.y, 1 / r.dir.z);
	int sign[] = { invdir.x < 0 ? 1 : 0, invdir.y < 0 ? 1 : 0, invdir.z < 0 ? 1 : 0};

	tmin = (bounds[sign[0]].x - r.pos.x) * invdir.x;
	tmax = (bounds[1 - sign[0]].x - r.pos.x) * invdir.x;
	tymin = (bounds[sign[1]].y - r.pos.y) * invdir.y;
	tymax = (bounds[1 - sign[1]].y - r.pos.y) * invdir.y;

	if ((tmin > tymax) || (tymin > tmax))
		return intersection(r, r.get_point(tmin), *this, -1, this->color);

	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;

	tzmin = (bounds[sign[2]].z - r.pos.z) * invdir.z;
	tzmax = (bounds[1 - sign[2]].z - r.pos.z) * invdir.z;

	if ((tmin > tzmax) || (tzmin > tmax))
		return intersection(r, r.get_point(tmin), *this, -1, this->color);

	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;

	if (tmin < 0)
		return intersection(r, r.get_point(tmin), *this, -1, this->color);

	return intersection(r, r.get_point(tmin), *this, tmin, this->color);
}
