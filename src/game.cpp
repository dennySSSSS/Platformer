#include "content.h"
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

int direction;
const int movingUp = 0;
const int movingRight = 1;
const int movingDown = 2;
const int movingLeft = 3;
bool isMoving;
int charSpeed = 100;
int charPosX;
int charPosY;
SDL_Rect playerDst = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, charSize * 2, charSize * 2};

void startGame()
{
	direction = movingRight;
	bool isMoving = false;

	initSpriteAnimation(&moving, sheet, movingFirstFrame, 3, 5);
}

void movement(float dt)
{
	if (keyStates[SDL_SCANCODE_A])
	{
		if (direction != movingLeft)
		{
			resetAnimation(&moving);
			direction = movingLeft;
		}
		playerDst.x -= charSpeed * dt;
		isMoving = true;
		updateAnimation(&moving, dt);
		return;
	}
	if (keyStates[SDL_SCANCODE_D])
	{
		if (direction != movingRight)
		{
			resetAnimation(&moving);
			direction = movingRight;
		}
		playerDst.x += charSpeed * dt;
		isMoving = true;
		updateAnimation(&moving, dt);
		return;
	}

	isMoving = false;
	resetAnimation(&moving);
}

void update(float dt)
{
	if (keyStates[SDL_SCANCODE_ESCAPE] && !lastKeyStates[SDL_SCANCODE_ESCAPE])
		isRunning = false;

	// updateAnimation(&moving, dt);

	movement(dt);

	// falling
	SDL_Rect updatedPlayer = playerDst;
	updatedPlayer.y++;
	bool falling = true;
	for (int row = 0; row < levelHeight; row++)
		for (int col = 0; col < levelWidth; col++)
			if (SDL_HasIntersection(&updatedPlayer, &walkable[row][col]))
			{
				falling = false;
				break;
			}
	if (falling)
		playerDst.y += 5;
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

	drawAnimatedSprite(renderer, &moving, playerDst);
}
void endGame()
{
	freeSprite(sheet);
}