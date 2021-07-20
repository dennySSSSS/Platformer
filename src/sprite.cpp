#include "sprite.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "stdio.h"

Sprite* loadSprite(SDL_Renderer *renderer, const char* path)
{
	if (!renderer)
	{
		fprintf(stderr, "loadTexture error: NULL renderer device.\n");
		return NULL;
	}

	SDL_Surface *surface = IMG_Load(path);
	if (surface == NULL)
	{
		fprintf(stderr, "IMG_Load error: %s\n", IMG_GetError());
		return NULL;
	}

	SDL_Texture *sdlTexture = SDL_CreateTextureFromSurface(renderer, surface);
	if (sdlTexture == NULL) {
		fprintf(stderr, "SDL_CreateTextureFromSurface error: %s\n", SDL_GetError());
		return NULL;
	}

	Sprite *texture = (Sprite*)malloc(sizeof(*texture));
	texture->sdlTexture = sdlTexture;
	texture->width = surface->w;
	texture->height = surface->h;

	SDL_FreeSurface(surface);
	return texture;
}

void freeSprite(Sprite *sprite)
{
	if (!sprite)
		return;

	if (sprite->sdlTexture)
	{
		SDL_DestroyTexture(sprite->sdlTexture);
		printf("Cleaning sprite\n");
	}
	free(sprite);
}

void drawSprite(SDL_Renderer *renderer, Sprite *sprite,
	SDL_Rect src, SDL_Rect dst)
{
	if (!sprite)
		return;

	SDL_RenderCopy(renderer, sprite->sdlTexture, &src, &dst);
}

void drawSpriteTransformed(SDL_Renderer* renderer, Sprite* sprite,
	SDL_Rect src, SDL_Rect dst,
	double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (!sprite)
		return;

	SDL_RenderCopyEx(renderer, sprite->sdlTexture, &src, &dst, angle, center, flip);
}
