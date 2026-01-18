#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include <cstdlib>
#include <ctime>
#include "cmsis_os.h"

#ifdef USE_HAL_DRIVER
#include "stm32f4xx_hal.h"
#endif

#define SOUND_START     1
#define SOUND_MERGE     2
#define SOUND_GAMEOVER  3

extern osMessageQueueId_t guiKeyQueue;
extern osMessageQueueId_t soundQueueHandle;

void sendSound(uint8_t type) {
    if (soundQueueHandle != NULL) {
        osMessageQueuePut(soundQueueHandle, &type, 0, 0);
    }
}

Model::Model() : modelListener(0)
{
	#ifdef USE_HAL_DRIVER
    srand(HAL_GetTick());
    #else
    srand(time(0));
    #endif
    newRankIndex = -1;
    highScores[0] = 5000;
	highScores[1] = 4000;
	highScores[2] = 3000;
	highScores[3] = 2000;
	highScores[4] = 1000;
}

void Model::tick()
{
	if (isGameOver)
	{
		gameOverCounter++;

		if (gameOverCounter >= 180)
		{
			if (modelListener)
			{
				modelListener->switchToGameOver();
			}

			isGameOver = false;
			gameOverCounter = 0;
		}

		return;
	}

	if (guiKeyQueue == NULL) return;

	uint8_t receivedKey = 0;
	osStatus_t status;

	status = osMessageQueueGet(guiKeyQueue, &receivedKey, NULL, 0);

	if (status == osOK)
	{
		switch (receivedKey)
		{
			case 1: moveUp();    break;
			case 2: moveDown();  break;
			case 3: moveLeft();  break;
			case 4: moveRight(); break;
		}
	}
}

void Model::newGame()
{
	sendSound(SOUND_START);
	score = 0;
	isGameOver = false;
	gameOverCounter = 0;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			grid[i][j] = 0;
		}
	}

	spawnRandomTile();
	spawnRandomTile();

	if (modelListener != 0)
	{
		modelListener->updateGridDisplay(grid);
	}
}

void Model::spawnRandomTile()
{
    if (!hasEmptyTile()) return;

    int r, c;
    do {
        r = rand() % 4;
        c = rand() % 4;
    } while (grid[r][c] != 0);

    grid[r][c] = (rand() % 10 == 0) ? 4 : 2;
}

bool Model::hasEmptyTile()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if (grid[i][j] == 0) return true;
    return false;
}

void Model::rotateGrid()
{
    int temp[4][4];

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            temp[j][3-i] = grid[i][j];
        }
    }

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            grid[i][j] = temp[i][j];
        }
    }
}

bool Model::moveLeftInternal()
{
    bool isMoved = false;
    bool anyMergeHappened = false;

    for (int i = 0; i < 4; i++)
    {
        int temp[4] = {};
        int pos = 0;

        for (int j = 0; j < 4; j++) {
            if (grid[i][j] != 0) {
                temp[pos] = grid[i][j];
                pos++;
            }
        }

        for (int j = 0; j < 3; j++) {
            if (temp[j] != 0 && temp[j] == temp[j+1]) {
                temp[j] *= 2;
                score += temp[j];
                temp[j+1] = 0;
                anyMergeHappened = true;
            }
        }

        int finalRow[4] = {};
        int p = 0;
        for (int j = 0; j < 4; j++) {
            if (temp[j] != 0) {
                finalRow[p] = temp[j];
                p++;
            }
        }

        for (int j = 0; j < 4; j++) {
            if (grid[i][j] != finalRow[j]) {
                grid[i][j] = finalRow[j];
                isMoved = true;
            }
        }
    }

    if (anyMergeHappened) {
		sendSound(SOUND_MERGE);
	}

    return isMoved;
}

void Model::moveLeft()
{
    if (moveLeftInternal()) {
        spawnRandomTile();
        if (modelListener)
		{
			modelListener->updateGridDisplay(grid);
			modelListener->updateScore(score);
		}
        if (checkGameOver())
		{
        	sendSound(SOUND_GAMEOVER);
			isGameOver = true;
			gameOverCounter = 0;
		}
    }
}

void Model::moveRight()
{
    rotateGrid();
    rotateGrid();

    if (moveLeftInternal()) {
        spawnRandomTile();
        rotateGrid();
        rotateGrid();

        if (modelListener)
		{
			modelListener->updateGridDisplay(grid);
			modelListener->updateScore(score);
		}
        if (checkGameOver())
		{
        	sendSound(SOUND_GAMEOVER);
			isGameOver = true;
			gameOverCounter = 0;
		}
    } else {
        rotateGrid();
        rotateGrid();
    }
}

void Model::moveUp()
{
    rotateGrid();
    rotateGrid();
    rotateGrid();

    if (moveLeftInternal()) {
        spawnRandomTile();
        rotateGrid();
        if (modelListener)
		{
			modelListener->updateGridDisplay(grid);
			modelListener->updateScore(score);
		}
        if (checkGameOver())
		{
        	sendSound(SOUND_GAMEOVER);
			isGameOver = true;
			gameOverCounter = 0;
		}
    } else {
        rotateGrid();
    }
}

void Model::moveDown()
{
    rotateGrid();

    if (moveLeftInternal()) {
        spawnRandomTile();
        rotateGrid();
        rotateGrid();
        rotateGrid();
        if (modelListener)
		{
			modelListener->updateGridDisplay(grid);
			modelListener->updateScore(score);
		}
        if (checkGameOver())
		{
        	sendSound(SOUND_GAMEOVER);
			isGameOver = true;
			gameOverCounter = 0;
		}
    } else {
        rotateGrid();
        rotateGrid();
        rotateGrid();
    }
}

bool Model::checkGameOver()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (grid[i][j] == 0) return false;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i][j] == grid[i][j+1]) return false;

    for (int j = 0; j < 4; j++)
        for (int i = 0; i < 3; i++)
            if (grid[i][j] == grid[i+1][j]) return false;

    return true;
}

int Model::updateHighScores(int newScore) {
	newRankIndex = -1;
	if (newScore < highScores[4]) return -1;

	int i;

	for (i = 4; i > 0; i--)
	{
		if (newScore > highScores[i-1])
		{
			highScores[i] = highScores[i-1];
		}
		else
		{
			break;
		}
	}

	highScores[i] = newScore;
	newRankIndex = i;
	return i;
}
