#pragma once

#include "SDL2/SDL.h"
#include "spriteAnimation.h"
#include "config.h"
#include "sprite.h"
#include "game.h"
#include "level.h"
#include <stdlib.h>

// Sheet
const int charSize = 16;
Sprite* sheet = NULL;

SpriteAnimation moving;
SDL_Rect movingFirstFrame = { 4 * charSize, 5 * charSize, charSize, charSize };

bool loadContent()
{
	sheet = loadSprite(renderer, "assets/tileset_16x16.png");

	if (sheet)
		return true;
	return false;
}


SDL_Rect fullScreen = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

// tilesSheet
