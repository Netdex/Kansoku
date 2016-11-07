#include "camera.h"


camera::camera(world &_world, vec3 _pos, vec3 _dir, SDL_Color sky_color, int pixel_width, int pixel_height, int pixel_size)
	: p_width(pixel_width), p_height(pixel_height), p_size(pixel_size),
	w_width(p_width * p_size), w_height(p_height * p_size),
	w_center_x(p_width * p_size / 2), w_center_y(p_height * p_size / 2), _world(_world),
	_pos(_pos), _forward(_dir),
	sky_color(sky_color)
{

}

camera::~camera()
{

}

void camera::render(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	vec3 right = vec3::cross(_forward, DOWN).normalize() * FOV;
	vec3 up = vec3::cross(_forward, right).normalize() * FOV;

	SDL_Rect r;
	for (int y = 0; y < p_height; ++y)
	{
		for (int x = 0; x < p_width; ++x)
		{
			SDL_Color col = get_trace_color(ray3(_pos, get_point(x, y, right, up)));
			r = { x * p_size, y * p_size, p_size, p_size };
			SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
			SDL_RenderFillRect(renderer, &r);
		}
	}
}

SDL_Color camera::get_trace_color(const ray3& ray)
{
	intersection i = _world.min_intersection(ray);
	if (!i.object)
		return sky_color;

	SDL_Color color = i.color;
	if (RENDER_SHADOWS)
	{
		vec3 shadow_ray_targ = _world.light - i.point;
		vec3 adj = (i.point - i.ray.pos).normalize() * 0.01;
		ray3 adj_ray = ray3(i.point - adj, shadow_ray_targ);
		intersection si = _world.min_intersection(adj_ray);
		if (si.object)
		{
			darken(color, 0.5f);
		}
	}
	return color;
}

float camera::recenter_x(float x) const
{
	return (x - (p_width / 2.0f)) / (2.0f * p_width);
}

float camera::recenter_y(float y) const
{
	return -(y - (p_height / 2.0f)) / (2.0f * p_height);
}

vec3 camera::get_point(float x, float y, const vec3& right, const vec3& up) const
{
	vec3 reright = right * recenter_x(x);
	vec3 reup = up * recenter_y(y);
	vec3 p = _forward + reright + reup;
	p.normalize();
	return p;
}

void camera::darken(SDL_Color& col, float perc)
{
	col.r *= perc;
	col.g *= perc;
	col.b *= perc;
}
