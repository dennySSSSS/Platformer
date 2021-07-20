// Needded to deal with windows main function linking
#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "SDL2/SDL.h"
#include "config.hpp"
#include "sprite.hpp"
#include "game.hpp"

// Extern variables from game.h
SDL_Window* window;
SDL_Renderer* renderer;
const Uint8* keyStates;
Uint8 lastKeyStates[SDL_NUM_SCANCODES];
bool isRunning = true;

void printSDLVersion();
bool initialize();
void closeApp();

// Runtime and timing
int fps = 0;
Uint32 lastTick = SDL_GetTicks();
float deltaTime;

int main(int argc, char* argv[])
{
	// Needded to deal with windows main function linking.
	SDL_SetMainReady();

	if (!initialize())
		return 2;

	if (!loadContent())
		return 2;

	//FPS counter
	Uint32 frameCounter = 0;
	Uint32 tickCounter = 0;
	float timeAcc = 0;

	// Setup keyboard
	keyStates = SDL_GetKeyboardState(NULL);
	memset(lastKeyStates, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);

	printf("Starting game.\n");
	startGame();

	while (isRunning) {
		SDL_Event e;
		// Process messages
		// SDL_PollEvents already calls SDL_PumpEvents
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) isRunning = false;
		}

		// Calculate deltaTime
		Uint32 totalTicks = SDL_GetTicks();
		tickCounter = totalTicks - lastTick;
		deltaTime = tickCounter / 1000.0f;
		lastTick = totalTicks;

		// Count and show fps
		timeAcc += deltaTime;
		frameCounter++;
		if (timeAcc >= 1.0) {
			fps = frameCounter;
			frameCounter = 0;
			timeAcc -= 1.0;
			// printf("FPS: %d; deltaTime: %f\n", fps, deltaTime);
		}

		// Update and draw
		update(deltaTime);
		draw(deltaTime);

		// Swap buffers
		SDL_RenderPresent(renderer);

		// update last keyboard state
		memcpy(lastKeyStates, keyStates, sizeof(Uint8) * SDL_NUM_SCANCODES);

		// Timing for FPS cap
		totalTicks = SDL_GetTicks();
		tickCounter = totalTicks - lastTick;
		if (tickCounter < SCREEN_TICK_INTERVAL)
			SDL_Delay(SCREEN_TICK_INTERVAL - tickCounter);
	}

	closeApp();
	return 0;
}

void printSDLVersion()
{
	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("Compiled against SDL version %d.%d.%d\n", compiled.major, compiled.minor, compiled.patch);
	printf("Linking against SDL version %d.%d.%d\n", linked.major, linked.minor, linked.patch);
}

bool initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
		return false;
	}

	/*
	Texture filtering
	0 or nearest - nearest pixel sampling
	2 or linear - linear filtering (supported by OpenGL and Direct3D)
	2 or best - anisotropic filtering (supported by Direct3D)
	*/
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
	{
		fprintf(stderr, "Testure filtering not enabled: %s\n", SDL_GetError());
	}

	/*
	Create window
	Flags:
	SDL_WINDOW_FULLSCREEN - fullscreen
	SDL_WINDOW_SHOWN - ignored (standard window)
	*/
	window = SDL_CreateWindow("The Game",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (!window)
	{
		fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
		return false;
	}

	/*
	Initialize renderer
	SDL_RENDERER_PRESENTVSYNC - VSync
	*/
	renderer = SDL_CreateRenderer(window, -2, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		fprintf(stderr, "SDL_CreateRenderer error: %s\n", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	return true;
}

void closeApp()
{
	// Free renderer and window
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	// Quit all subsystems
	SDL_Quit();

	printf("Terminating...\n");
}
