#pragma once
#include "intersection.h"

struct intersectable
{
	intersectable();
	virtual ~intersectable();
	virtual intersection get_intersection(ray3 &ray) const = 0;
};

