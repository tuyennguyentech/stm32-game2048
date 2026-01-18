#include <gui/gameoverscreen_screen/GameOverScreenView.hpp>
#include <gui/gameoverscreen_screen/GameOverScreenPresenter.hpp>

GameOverScreenPresenter::GameOverScreenPresenter(GameOverScreenView& v)
    : view(v)
{

}

void GameOverScreenPresenter::activate()
{
	int finalScore = model->getScore();
	view.setFinalScore(finalScore);
}

void GameOverScreenPresenter::deactivate()
{

}
