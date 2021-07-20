#pragma once

#include "sprite.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

typedef struct SpriteAnimation {
	Sprite* sheet;
	float frameInterval;
	float targetInterval;
	int nOfFrames;
	int frameIndex;
	SDL_Rect firstFrame;
	SDL_Rect frameRect;
} SpriteAnimation;

/*!
Anitialize sprite animation.
\param animation Pointer to SpriteAnimation structure
\param sheet Sprite sheet with animation
\param firstFrame Rectangle defining first frame of animation
\param nOfFrames Total number of frames on one row to make an animation
\param framesPerSec Speed of animation
*/
void initSpriteAnimation(SpriteAnimation* animation, Sprite* sheet,
	SDL_Rect firstFrame, int nOfFrames, int framesPerSec
);

/*!
Update animation using delta time in seconds.
\param animation Pointer to SpriteAnimation structure
\param dt Delta time
*/
void updateAnimation(SpriteAnimation* animation, float dt);

/*!
Draw animated sprite at defined position.
\param renderer Game renderer
\param animation Pointer to SpriteAnimation structure
\param destination Destination rectangle on screen
*/
void drawAnimatedSprite(SDL_Renderer *renderer, SpriteAnimation* animation, SDL_Rect destination);
void drawAnimatedSpriteInverted(SDL_Renderer *renderer, SpriteAnimation* animation, SDL_Rect destination);

/*!
Reset animation state to begining.
\param animation Pointer to SpriteAnimation structure
*/
void resetAnimation(SpriteAnimation* animation);
