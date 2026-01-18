#include <gui/gamescreen_screen/GameScreenView.hpp>
#include <gui/gamescreen_screen/GameScreenPresenter.hpp>

GameScreenPresenter::GameScreenPresenter(GameScreenView& v)
    : view(v)
{

}

void GameScreenPresenter::activate()
{

}

void GameScreenPresenter::deactivate()
{

}

void GameScreenPresenter::startNewGame()
{
    model->newGame();
}

void GameScreenPresenter::updateGridDisplay(int grid[4][4])
{
    view.updateBoardFromMatrix(grid);
}

void GameScreenPresenter::updateScore(int score)
{
    view.setScore(score);
}

void GameScreenPresenter::switchToGameOver()
{
	int currentScore = model->getScore();
	int rank = model->updateHighScores(currentScore);
	if (rank != -1)
	{
		static_cast<FrontendApplication*>(touchgfx::Application::getInstance())->gotoRankingScreenScreenSlideTransitionWest();
	}
	else
	{
		static_cast<FrontendApplication*>(touchgfx::Application::getInstance())->gotoGameOverScreenScreenSlideTransitionWest();
	}
}
