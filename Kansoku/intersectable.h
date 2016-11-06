#pragma once
#include "intersection.h"

struct intersectable
{
	intersectable();
	virtual ~intersectable();
	virtual intersection get_intersection(const ray3 &ray) = 0;
};

