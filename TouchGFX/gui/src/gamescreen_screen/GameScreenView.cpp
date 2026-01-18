#include <gui/gamescreen_screen/GameScreenView.hpp>
#include <touchgfx/Utils.hpp>
#include <texts/TextKeysAndLanguages.hpp>

GameScreenView::GameScreenView()
{

}

void GameScreenView::setupScreen()
{
    GameScreenViewBase::setupScreen();

    tiles[0][0] = &tile00;
	tiles[0][1] = &tile01;
	tiles[0][2] = &tile02;
	tiles[0][3] = &tile03;

	tiles[1][0] = &tile10;
	tiles[1][1] = &tile11;
	tiles[1][2] = &tile12;
	tiles[1][3] = &tile13;

	tiles[2][0] = &tile20;
	tiles[2][1] = &tile21;
	tiles[2][2] = &tile22;
	tiles[2][3] = &tile23;

	tiles[3][0] = &tile30;
	tiles[3][1] = &tile31;
	tiles[3][2] = &tile32;
	tiles[3][3] = &tile33;

	presenter->startNewGame();
	setScore(0);
}

void GameScreenView::tearDownScreen()
{
    GameScreenViewBase::tearDownScreen();
}

void GameScreenView::requestNewGame()
{
    presenter->startNewGame();
}

void GameScreenView::updateBoardFromMatrix(int matrix[4][4])
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            tiles[i][j]->setNumber(matrix[i][j]);
        }
    }
}

void GameScreenView::setScore(int score)
{
    Unicode::snprintf(scoreValueBuffer, SCOREVALUE_SIZE, "%d", score);
    scoreValue.invalidate();
}
