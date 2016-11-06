#include "world.h"



world::world()
{
}


world::~world()
{
}

void world::a_rectangle(vec3 topleft, vec3 bottomright, SDL_Color color)
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
	// TODO this method has a pointer return issue
	float mind = 1 << 30;
	intersection* mini = nullptr;

	for(auto i = intersects.begin(); i != intersects.end(); ++i)
	{
		// TODO bounds check before primitive check
		intersection is = (*i)->get_intersection(r);
		if(is.distance >= 0)
		{
			if (is.distance < mind) {
				mind = is.distance;
				mini = &is;
			}
		}
	}
	return *mini;
}
