#pragma once
#include "vec3.h"
#include "world.h"

class camera
{
public:
	const vec3 DOWN = vec3(0, -1, 0);
	const bool RENDER_SHADOWS = true;
	const float FOV = 1.5f;

	const int p_width;
	const int p_height;
	const int p_size;
	const int w_width;
	const int w_height;
	const int w_center_x;
	const int w_center_y;

	world _world;
	vec3 _pos;
	vec3 _forward;
	
	SDL_Color sky_color;

	camera(world &, vec3 pos, vec3 dir, SDL_Color sky, int p_width, int p_height, int p_size);
	~camera();

	void render(SDL_Renderer *renderer);
private:
	SDL_Color get_trace_color(const ray3 &ray);
	float recenter_x(float x) const;
	float recenter_y(float y) const;
	vec3 get_point(float x, float y, const vec3 &right, const vec3 &up) const;
	static void darken(SDL_Color &col, float perc);
};

