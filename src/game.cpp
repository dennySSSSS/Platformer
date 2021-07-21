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
	{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
	{'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D'}};

const int movingUp = 0;
const int movingRight = 1;
const int movingDown = 2;
const int movingLeft = 3;
int maxHeight;

struct Player
{
	bool isMoving;
	bool isJumping;
	bool isFalling;
	int direction;
	int speed = 250;
	SDL_Rect dst;
};
Player player;

void startGame()
{
	player.direction = movingRight;
	player.isMoving = false;

	player.dst = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, charSize * 2, charSize * 2};
	initSpriteAnimation(&moving, sheet, movingFirstFrame, 3, 7);
}

void movement(float dt)
{
	if (keyStates[SDL_SCANCODE_SPACE] && !player.isJumping && !player.isFalling)
	{
		player.isJumping = true;
		maxHeight = player.dst.y - 100;
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

	// Falling
	SDL_Rect updatedPlayer = player.dst;
	updatedPlayer.y++;
	player.isFalling = true;
	if (!player.isJumping)
	{
		for (int row = 0; row < levelHeight; row++)
			for (int col = 0; col < levelWidth; col++)
				if (SDL_HasIntersection(&updatedPlayer, &walkable[row][col]))
				{
					player.isFalling = false;
					break;
				}
		if (player.isFalling)
			player.dst.y += 8;
	}

	// Jumping
	if (player.isJumping)
	{
		player.dst.y -= 8;
		if (player.dst.y <= maxHeight)
			player.isJumping = false;
	}
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
				drawSprite(renderer, sheet, dirtSrc, dst);
				walkable[row][col] = dst;
			}
			else if (level[row][col] == 'G')
			{
				drawSprite(renderer, sheet, grassMiddleSrc, dst);
				walkable[row][col] = dst;
			}
		}
	}

	drawAnimatedSprite(renderer, &moving, player.dst);
}
void endGame()
{
	freeSprite(sheet);
}