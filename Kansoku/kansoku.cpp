#include <cstdlib>
#include <cstdio>
#include <SDL.h>
#include "constants.h"
#include "world.h"
#include "camera.h"
#include <cmath>
#include "box.h"
#include "plane.h"

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
	return true;
}

bool close() {
	SDL_FreeSurface(screen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return true;
}

int main(int argc, char* argv[])
{
	world w;
	w.a_rectangle(vec3(-1, 1, 10), vec3(1, -1, 10), { 255, 255, 255, 255 });
	plane p(ray3(vec3(), vec3(0, -1, 0)), { 0, 255, 0, 255 });
	w.intersects.push_back(&p);
	//w.intersects.push_back(&p);
	camera c(w, vec3(0, 0, 0), vec3(0, 0, 1), { 0x00, 0x22, 0xFF, 0xFF },
		PIXEL_WIDTH, PIXEL_HEIGHT, PIXEL_SIZE);

	if (!init()) {
		printf("Failed to initialize SDL!");
		exit(1);
	}

	vec3 MOVE_SPEED = vec3(.1, 0, .1);

	const Uint8 *state;
	SDL_Event e;
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
	do {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		state = SDL_GetKeyboardState(NULL);

		vec3 dir = c._forward;
		dir.normalize();
		dir = dir * MOVE_SPEED;
		
		if (state[SDL_SCANCODE_W]) {
			c._pos = c._pos + dir;
		}
		if (state[SDL_SCANCODE_S]) {
			c._pos = c._pos - dir;
		}
		if (state[SDL_SCANCODE_A]) {
			vec3 dd = dir;
			dd.rot_y(M_PI / 2.0f);
			c._pos = c._pos - dd;
		}
		if (state[SDL_SCANCODE_D]) {
			vec3 dd = dir;
			dd.rot_y(-M_PI / 2.0f);
			c._pos = c._pos - dd;
		}
		if (state[SDL_SCANCODE_SPACE]) {
			vec3 dd = vec3(0, 0.1, 0);
			c._pos = c._pos + dd;
		}
		if (state[SDL_SCANCODE_LSHIFT]) {
			vec3 dd = vec3(0, 0.1, 0);
			c._pos = c._pos - dd;
		}
		if (state[SDL_SCANCODE_UP]) {
			vec3 dd = vec3::cross(c._forward, c.DOWN);
			c._forward.rotate_axis(dd, -0.05);
		}
		if (state[SDL_SCANCODE_DOWN]) {
			vec3 dd = vec3::cross(c._forward, c.DOWN);
			c._forward.rotate_axis(dd, 0.05);
		}
		if (state[SDL_SCANCODE_LEFT]) {
			c._forward.rot_y(-0.05);
		}
		if (state[SDL_SCANCODE_RIGHT]) {
			c._forward.rot_y(0.05);
		}
		
		printf("%f %f %f | %f %f %f                      \r", c._pos.x, c._pos.y, c._pos.z, 
			c._forward.get_ang_x() * 180 / M_PI, c._forward.get_ang_y() * 180 / M_PI, c._forward.get_ang_z() * 180 / M_PI);
		c.render(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	} while (!quit);
	close();
	return 0;
}
