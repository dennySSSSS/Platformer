#include "spriteAnimation.h"
#include "sprite.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

/*
typedef struct SpriteAnimation {
	Sprite* sheet;
	float frameInterval;
	float targetInterval;
	int nOfFrames;
	int frameIndex;
	SDL_Rect frameRect;
} SpriteAnimation;
*/

void initSpriteAnimation(SpriteAnimation* animation, Sprite* sheet,
	SDL_Rect firstFrame, int nOfFrames, int framesPerSec)
{
	// Init provided values
	animation->sheet = sheet;
	animation->frameRect = firstFrame;
	animation->nOfFrames = nOfFrames;

	// Init runtime values
	animation->frameIndex = 0;
	animation->frameInterval = .0f;
	// e.g. 4 frames per sec => 1 / 4 = 0.25f
	animation->targetInterval = 1.0f / framesPerSec;
}

void updateAnimation(SpriteAnimation* animation, float dt)
{
	animation->frameInterval += dt;
	if (animation->frameInterval >= animation->targetInterval)
	{
		// Update to next frame
		animation->frameIndex++;
		if (animation->frameIndex >= animation->nOfFrames)
			animation->frameIndex = 0;

		animation->frameRect.x = animation->frameRect.w * animation->frameIndex;

		// Update timer
		animation->frameInterval -= animation->targetInterval;
	}
}

void drawAnimatedSprite(SDL_Renderer *renderer, SpriteAnimation* animation, SDL_Rect destination)
{
	drawSprite(renderer, animation->sheet, animation->frameRect, destination);
}


// void drawAnimatedSpriteInverted(SDL_Renderer *renderer, SpriteAnimation* animation, SDL_Rect destination)
// {
// 	flip = SDL_FLIP_HORIZONTAL;
// 	SDL_RendercopyEx(renderer, animation->sheet, aninmation->frameRect, destination, NULL, NULL, flip);
// }

void resetAnimation(SpriteAnimation* animation)
{
	animation->frameInterval = .0f;
	animation->frameIndex = 0;
	animation->frameRect.x = animation->frameRect.w * animation->frameIndex;
}
