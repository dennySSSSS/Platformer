#pragma once

#include "SDL2/SDL.h"
#include "spriteAnimation.hpp"
#include "config.hpp"
#include "sprite.hpp"
#include "game.hpp"
// #include "level.hpp"

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
SDL_Rect grassMiddleSrc = { 16, 0, 16, 16 };
SDL_Rect dirtSrc = { 16, 16, 16, 16 };