#pragma once
class ray3;

class intersectable
{
public:
	intersectable();
	virtual ~intersectable();

	virtual void get_intersection(ray3 &ray) = 0;
};

