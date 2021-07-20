#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

typedef struct Sprite {
	SDL_Texture *sdlTexture;
	int width;
	int height;
} Sprite;

Sprite* loadSprite(SDL_Renderer *renderer, const char* path);

void freeSprite(Sprite *sprite);

void drawSprite(SDL_Renderer *renderer, Sprite *sprite,
	SDL_Rect src, SDL_Rect dst);

void drawSpriteTransformed(SDL_Renderer* renderer, Sprite* sprite,
		SDL_Rect src, SDL_Rect dst,
		double angle, SDL_Point* center, SDL_RendererFlip flip);
