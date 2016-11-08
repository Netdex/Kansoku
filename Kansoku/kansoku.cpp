#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <SDL.h>
#include "constants.h"
#include "world.h"
#include "camera.h"
#include "box.h"
#include "plane.h"
#include <algorithm>

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Renderer *renderer = NULL;

bool quit = false;

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return false;
	window = SDL_CreateWindow("Kansoku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
		SDL_WINDOW_SHOWN);
	screen = SDL_GetWindowSurface(window);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	return true;
}

bool close() {
	SDL_FreeSurface(screen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return true;
}

const vec3 MOVE_SPEED = vec3(.1, 0, .1);
void handle_input(camera &c, const Uint8 *state)
{
	vec3 dir = c._forward;
	dir.normalize();
	dir *= MOVE_SPEED;

	if (state[SDL_SCANCODE_W]) {
		c._pos += dir;
	}
	if (state[SDL_SCANCODE_S]) {
		c._pos -= dir;
	}
	if (state[SDL_SCANCODE_A]) {
		vec3 dd = dir;
		dd.rot_y(M_PI / 2.0f);
		c._pos -= dd;
	}
	if (state[SDL_SCANCODE_D]) {
		vec3 dd = dir;
		dd.rot_y(-M_PI / 2.0f);
		c._pos -= dd;
	}
	if (state[SDL_SCANCODE_SPACE]) {
		vec3 dd = vec3(0, 0.1, 0);
		c._pos += dd;
	}
	if (state[SDL_SCANCODE_LSHIFT]) {
		vec3 dd = vec3(0, 0.1, 0);
		c._pos -= dd;
	}

	int x, y;
	SDL_GetRelativeMouseState(&x, &y);
	if (x != 0)
	{
		vec3 dd = vec3::cross(c._forward, c.DOWN);
		c._forward.rotate_axis(dd, 0.005 * y);
	}
	if (y != 0)
	{
		c._forward.rot_y(0.005 * x);
	}
}

int main(int argc, char* argv[])
{
	// TODO BVH ray check
	world w;
	
	plane p(ray3(vec3(), vec3(0, -1, 0)), { 0, 255, 0, 255 });
	w.intersects.push_back(&p);
	for (int i = 0; i < 5; i++) {
		box *a = new box(vec3(0 + i * 4, 0, 0), vec3(1 + i * 4,1,1), { 255,0,0,255 });
		box *b = new box(vec3(2 + i * 4, 0, 0), vec3(3 + i * 4, 1, 1), { 255,0,0,255 });
		box *c = new box(vec3(1 + i * 4, 1, 0), vec3(2 + i * 4, 5, 1), { 255,0,0,255 });
		w.intersects.push_back(a);
		w.intersects.push_back(b);
		w.intersects.push_back(c);
	}
	

	camera c(w, vec3(0, 0, 0), vec3(0, 0, 1), { 120, 120, 255, 255 },
		PIXEL_WIDTH, PIXEL_HEIGHT, PIXEL_SIZE);

	if (!init()) {
		printf("Failed to initialize SDL!");
		exit(1);
	}

	const Uint8 *state;

	SDL_Event e;
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
	do {
		int start = SDL_GetTicks();
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		state = SDL_GetKeyboardState(NULL);
		handle_input(c, state);

		printf("P[%f, %f, %f] | D[%f, %f, %f]   ", c._pos.x, c._pos.y, c._pos.z,
			c._forward.get_ang_x() * 180 / M_PI, c._forward.get_ang_y() * 180 / M_PI, c._forward.get_ang_z() * 180 / M_PI);

		clock_t begin = clock();
		c.render(renderer);
		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		printf("E%fms          \r", elapsed_secs * 1000);

		SDL_RenderPresent(renderer);

		int time = SDL_GetTicks() - start;
		if (time < 0) continue;
		int sleepTime = 16 - time;
		if (sleepTime > 0)
		{
			SDL_Delay(sleepTime);
		}
	} while (!quit);
	close();
	return 0;
}
