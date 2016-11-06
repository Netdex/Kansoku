#include "ray3.h"
#include <algorithm>


ray3::ray3()
{
}

ray3::ray3(vec3 _pos, vec3 _dir) : pos(_pos), dir(_dir)
{
	dir.normalize();
}

ray3::ray3(const ray3& other)
	: pos(other.pos),
	dir(other.dir)
{
}

ray3::ray3(ray3&& other) noexcept
	: pos(std::move(other.pos)),
	dir(std::move(other.dir))
{
}

ray3& ray3::operator=(const ray3& other)
{
	if (this == &other)
		return *this;
	pos = other.pos;
	dir = other.dir;
	return *this;
}

ray3& ray3::operator=(ray3&& other) noexcept
{
	if (this == &other)
		return *this;
	pos = std::move(other.pos);
	dir = std::move(other.dir);
	return *this;
}

ray3::~ray3()
{
}

vec3 ray3::get_point(float t) const
{
	return pos + dir * t;
}
