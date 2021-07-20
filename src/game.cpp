#include "content.h"
#include <stdlib.h>
#include <time.h>

const int levelWidth = 20;
const int levelHeight = 12;
const int tileSize = 64;
char level[levelHeight][levelWidth] = {
	{'W', 'W', 'W', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'W', 'W', 'W', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'W', 'W', 'W', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'W', 'W', 'W', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'W', 'W', 'W', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'W', 'W', 'W', 'W', 'F', 'F', 'F', 'F', 'F', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'W', 'W', 'W', 'W', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'W', 'W', 'W', 'W', '0', '0', '0', '0', 'W', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'W', 'W', 'W', 'W', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'W', 'W', 'W', 'W', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'W', 'W', 'W', 'W', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'}};

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

	movement(dt);
}

void draw(float dt)
{
	// clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// background
/*
	for (int row = 0; row < levelHeight; row++)
	{
		for (int col = 0; col < levelWidth; col++)
		{
			SDL_Rect dst = { col * tileSize, row * tileSize, tileSize, tileSize };
			if(level[row][col] == 'W')
				drawSprite(renderer, wallsSheet, wallSrc, dst);
			else if(level[row][col] == 'F')
			{
				//drawSprite(renderer, wallsSheet, wallSrc, dst);
				drawSprite(renderer, tilesSheet, floorSrc, dst);
			}

		}
	}
*/
	drawAnimatedSprite(renderer, &moving, playerDst);

}
void endGame()
{
	freeSprite(sheet);
}