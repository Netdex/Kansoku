#pragma once
#include "vec3.h"

class ray3
{
public:
	vec3 pos;
	vec3 dir;

	ray3(vec3 pos, vec3 dir);
	ray3(const ray3& other);
	ray3(ray3&& other) noexcept;
	ray3& operator=(const ray3& other);
	ray3& operator=(ray3&& other) noexcept;
	~ray3();

	vec3 get_point(float t) const;
};

