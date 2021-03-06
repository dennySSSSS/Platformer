#include "content.hpp"
#include <stdlib.h>
#include <time.h>
#include <string>

const int levelWidth = 20;
const int levelHeight = 12;
const int tileSize = 64;
SDL_Rect walkable[levelHeight][levelWidth];
char level[levelHeight][levelWidth] = {
	{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'0', 'G', 'G', 'G', 'G', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'0', 'G', 'G', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'0', 'D', 'D', 'G', 'G', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'0', 'D', 'D', 'D', 'D', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'0', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', '0'},
	{'0', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', '0'}};

const int movingUp = 0;
const int movingRight = 1;
const int movingDown = 2;
const int movingLeft = 3;
int maxHeight;
SDL_Rect updatedPlayer;

Player player;

void startGame()
{
	player.direction = movingRight;
	player.isMoving = false;

	player.dst = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, charSize * 2, charSize * 2};
	initSpriteAnimation(&moving, sheet, movingFirstFrame, 3, 7);
}

bool loadContent()
{
	sheet = loadSprite(renderer, "assets/tileset_16x16.png");

	if (sheet)
		return true;
	return false;
}

void jump()
{
	if (player.isJumping)
	{
		player.dst.y -= 10;

		// head bang
		for (int row = 0; row < levelHeight; row++)
			for (int col = 0; col < levelWidth; col++)
			{
				while (SDL_HasIntersection(&player.dst, &walkable[row][col]))
				{
					player.dst.y++;		// Gets updated player on the edge of block
					player.isJumping = false;
				}
			}

		if (player.dst.y <= maxHeight)
			player.isJumping = false;
	}
}

void movement(float dt)
{
	if (keyStates[SDL_SCANCODE_SPACE] && !player.isJumping && !player.isFalling)
	{
		player.isJumping = true;
		maxHeight = player.dst.y - 250;
	}
	if (keyStates[SDL_SCANCODE_A])
	{
		if (player.direction != movingLeft)
		{
			resetAnimation(&moving);
			player.direction = movingLeft;
		}
		player.dst.x -= player.speed * dt;
		player.isMoving = true;
		updateAnimation(&moving, dt);
		return;
	}
	if (keyStates[SDL_SCANCODE_D])
	{
		if (player.direction != movingRight)
		{
			resetAnimation(&moving);
			player.direction = movingRight;
		}
		player.dst.x += player.speed * dt;
		player.isMoving = true;
		updateAnimation(&moving, dt);
		return;
	}

	player.isMoving = false;
	resetAnimation(&moving);
}

void update(float dt)
{
	if (keyStates[SDL_SCANCODE_ESCAPE] && !lastKeyStates[SDL_SCANCODE_ESCAPE])
		isRunning = false;

	movement(dt);
	if(player.isJumping)
		jump();

	// Falling
	updatedPlayer = player.dst;
	updatedPlayer.y++;
	player.isFalling = true;
	if (!player.isJumping)
	{
		for (int row = 0; row < levelHeight; row++)
			for (int col = 0; col < levelWidth; col++)
			{
				if (SDL_HasIntersection(&updatedPlayer, &walkable[row][col]))
				{
					player.isFalling = false;
					while (SDL_HasIntersection(&player.dst, &walkable[row][col]))
						player.dst.y--;
				}
			}
		if (player.isFalling)
			player.dst.y += 8;
	}

	// Jumping
}

void draw(float dt)
{
	// clear screen
	SDL_SetRenderDrawColor(renderer, 95, 205, 228, 255);
	SDL_RenderClear(renderer);

	// background
	for (int row = 0; row < levelHeight; row++)
	{
		for (int col = 0; col < levelWidth; col++)
		{
			SDL_Rect dst = {col * tileSize, row * tileSize, tileSize, tileSize};
			if (level[row][col] == 'D')
			{
				// drawSprite(renderer, sheet, dirtSrc, dst);
				walkable[row][col] = dst;

				if (level[row][col + 1] == 'D' && level[row][col - 1] == 'D' && level[row + 1][col] == '0')
					drawSprite(renderer, sheet, dirtBotSrc, dst); // dirt bottom
				else if (level[row + 1][col] == '0' && level[row][col + 1] == '0')
					drawSprite(renderer, sheet, dirtBotRightSrc, dst); // dirt bottom right
				else if (level[row + 1][col] == '0' && level[row][col - 1] == '0')
					drawSprite(renderer, sheet, dirtBotLeftSrc, dst); // dirt bottom left
				else if (level[row][col + 1] == '0' && level[row + 1][col] == 'D')
					drawSprite(renderer, sheet, dirtRightSrc, dst); // dir right
				else if (level[row][col - 1] == '0' && level[row + 1][col] == 'D')
					drawSprite(renderer, sheet, dirtLeftSrc, dst); // dirt left
				else
					drawSprite(renderer, sheet, dirtSrc, dst); // dirt middle
			}
			else if (level[row][col] == 'G')
			{
				// drawSprite(renderer, sheet, grassMiddleSrc, dst);
				walkable[row][col] = dst;

				if (level[row][col + 1] == '0')
					drawSprite(renderer, sheet, grassRightSrc, dst);
				else if (level[row][col - 1] == '0')
					drawSprite(renderer, sheet, grassLeftSrc, dst);
				else
					drawSprite(renderer, sheet, grassMiddleSrc, dst);
			}
		}
	}

	drawAnimatedSprite(renderer, &moving, player.dst);
}
void endGame()
{
	freeSprite(sheet);
}