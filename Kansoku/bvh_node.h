#pragma once
#include "box.h"
#include <vector>

class bvh_node : intersectable
{
public:
	intersectable *neg;
	intersectable *pos;
	box bounds;

	bvh_node(box bounds);
	~bvh_node();

	intersection get_intersection(const ray3 &r) override;

	static bvh_node* construct_bvh(const std::vector<primitive*> * intersects);
};

