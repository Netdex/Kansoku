#include "camera.h"


camera::camera(world &_world, vec3 _pos, vec3 _dir, SDL_Color sky_color, int pixel_width, int pixel_height, int pixel_size)
	: _world(_world), _pos(_pos), _forward(_dir),
	PIXEL_WIDTH(pixel_width), PIXEL_HEIGHT(pixel_height), PIXEL_SIZE(pixel_size),
	WINDOW_WIDTH(PIXEL_WIDTH * PIXEL_SIZE), WINDOW_HEIGHT(PIXEL_HEIGHT * PIXEL_SIZE),
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
	for(int y = 0; y < PIXEL_HEIGHT; ++y)
	{
		for(int x = 0; x < PIXEL_WIDTH; ++x)
		{
			SDL_Color col = get_trace_color(ray3(_pos, get_point(x, y, right, up)));
			r = { x * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE };
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
	if(RENDER_SHADOWS)
	{
		vec3 shadow_ray_targ = _world.light - i.point;
		ray3 shadow_ray = ray3(i.point, shadow_ray_targ);
		ray3 adj_ray = ray3(shadow_ray.get_point(0.01), shadow_ray_targ);
		intersection si = _world.min_intersection(adj_ray);
		if(si.object)
		{
			// TODO shadow accuracy check
			darken(color, 0.5f);
		}
	}
	return color;
}

float camera::recenter_x(float x) const
{
	return (x - (PIXEL_WIDTH / 2.0f)) / (2.0f * PIXEL_WIDTH);
}

float camera::recenter_y(float y) const
{
	return -(y - (PIXEL_HEIGHT / 2.0f)) / (2.0f * PIXEL_HEIGHT);
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
