#include "triangle.h"
#include <cmath>
#include <algorithm>

triangle::triangle(vec3 a, vec3 b, vec3 c, SDL_Color color) : primitive(color), a(a), b(b), c(c)
{
}

triangle::~triangle()
{
}

bool triangle::operator==(const primitive& o)
{
	const triangle *op = dynamic_cast<const triangle*>(&o);
	if (op)
		return a == op->a && b == op->b && c == op->c;
	return false;
}

intersection triangle::get_intersection(const ray3& r)
{
	vec3 v0v1 = b - a;
	vec3 v0v2 = c - a;
	vec3 pvec = vec3::cross(r.dir, v0v2);

	float det = vec3::dot(v0v1, pvec);
	if (abs(det) < 0.00001f)
		return intersection(r, r.pos, this, -1, color);
	float invDet = 1 / det;

	vec3 tvec = r.pos - a;
	float u = vec3::dot(tvec, pvec) * invDet;
	if (u < 0 || u > 1)
		return intersection(r, r.pos, this, -1, color);

	vec3 qvec = vec3::cross(tvec, v0v1);
	float v = vec3::dot(r.dir, qvec) * invDet;
	if (v < 0 || u + v > 1)
		return intersection(r, r.pos, this, -1, color);

	float t = vec3::dot(v0v2, qvec) * invDet;
	if (t < 0)
		return intersection(r, r.pos, this, -1, color);
	return intersection(r, r.get_point(t), this, t, color);
}

box triangle::get_bounds()
{
	vec3 min(INFINITY, INFINITY, INFINITY);
	vec3 max(-INFINITY, -INFINITY, -INFINITY);
	min.x = std::min(a.x, std::min(b.x, c.x));
	min.y = std::min(a.y, std::min(b.y, c.y));
	min.z = std::min(a.z, std::min(b.z, c.z));
	max.x = std::max(a.x, std::max(b.x, c.x));
	max.y = std::max(a.y, std::max(b.y, c.y));
	max.z = std::max(a.z, std::max(b.z, c.z));
	return box(min, max, { 0,0,0,0 });
}
