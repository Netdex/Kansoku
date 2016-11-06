#include "world.h"



world::world()
{
}


world::~world()
{
}

void world::a_rectangle(const vec3 &topleft, const vec3 &bottomright, const SDL_Color &color)
{
	vec3 topright = vec3(bottomright.x, topleft.y, bottomright.z);
	vec3 bottomleft = vec3(topleft.x, bottomright.y, topleft.z);
	triangle *t1 = new triangle(topleft, topright, bottomleft, color);
	triangle *t2 = new triangle(bottomright, bottomleft, topright, color);
	intersects.push_back(t1);
	intersects.push_back(t2);
}

intersection world::min_intersection(const ray3& r)
{
	intersection mini = intersection(ray3(), vec3(), nullptr, 1 << 30, SDL_Color());

	for(auto i = intersects.begin(); i != intersects.end(); ++i)
	{
		// TODO bounds check before primitive check
		intersection is = (*i)->get_intersection(r);
		if(is.distance >= 0)
		{
			if (is.distance < mini.distance) {
				mini = is;
			}
		}
	}
	return mini;
}
