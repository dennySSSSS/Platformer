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
SDL_Rect grassLeftSrc = {0, 0, 16, 16 };
SDL_Rect grassMiddleSrc = { 16, 0, 16, 16 };
SDL_Rect grassRightSrc = { 32, 0 , 16, 16 };
SDL_Rect dirtLeftSrc = { 0, 16, 16, 16 };
SDL_Rect dirtSrc = { 16, 16, 16, 16 };
SDL_Rect dirtRightSrc = { 32, 16, 16, 16 };
SDL_Rect dirtBotLeftSrc = { 0, 32, 16, 16 };
SDL_Rect dirtBotSrc = { 16, 32, 16, 16 };
SDL_Rect dirtBotRightSrc = { 32, 32, 16, 16 };
SDL_Rect rockSrc = { 16, 64, 16, 16 };
SDL_Rect rock2Src = { 16, 80 , 16, 16 };
SDL_Rect bushSrc = { 16, 48, 16, 16 };