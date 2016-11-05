#include <cstdlib>
#include <cstdio>
#include <SDL.h>
#include "constants.h"

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
	if (!init()) {
		printf("Failed to initialize SDL!");
		exit(1);
	}
	SDL_Event e;
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
	do {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	} while (!quit);
	close();
	return 0;
}