#include "bvh_node.h"
#include <algorithm>


bvh_node::bvh_node(box bounds) : bounds(bounds)
{
	
}


bvh_node::~bvh_node()
{
	delete neg;
	delete pos;
}

intersection bvh_node::get_intersection(const ray3& r)
{
	return bounds.get_intersection(r);
}

bvh_node* bvh_node::construct_bvh(const std::vector<primitive*>* intersects)
{
	std::vector<intersectable*> neg;
	std::vector<intersectable*> pos;

	vec3 min(INFINITY, INFINITY, INFINITY);
	vec3 max(-INFINITY, -INFINITY, -INFINITY);
	for(auto i = intersects->begin(); i != intersects->end(); ++i)
	{
		box b = (*i)->get_bounds();
		min.x = std::min(b.min.x, min.x);
		min.y = std::min(b.min.y, min.y);
		min.z = std::min(b.min.z, min.z);
		max.x = std::max(b.max.x, max.x);
		max.y = std::max(b.max.y, max.y);
		max.z = std::max(b.max.z, max.z);
	}

}
