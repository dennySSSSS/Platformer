#pragma once

#include "SDL2/SDL.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern const Uint8* keyStates;
extern Uint8 lastKeyStates[SDL_NUM_SCANCODES];

extern bool isRunning;

extern bool loadContent();
extern void startGame();
extern void endGame();
extern void update(float dt);
extern void draw(float dt);