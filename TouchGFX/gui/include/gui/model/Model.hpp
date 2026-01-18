#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    int grid[4][4];
    long score;

    void newGame();
    void spawnRandomTile();
    int getScore() { return score; }

    int* getHighScores() { return highScores; }
    int updateHighScores(int newScores);
    int getNewRankIndex() { return newRankIndex; }
    void clearNewRankIndex() { newRankIndex = - 1; }

protected:
    ModelListener* modelListener;

    bool hasEmptyTile();
    void rotateGrid();

	bool moveLeftInternal();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	bool isGameOver;
	int gameOverCounter;

	bool checkGameOver();

	int highScores[5];
	int newRankIndex;
};

#endif // MODEL_HPP
