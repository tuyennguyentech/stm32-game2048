#include <gui/gameoverscreen_screen/GameOverScreenView.hpp>

#include <touchgfx/Utils.hpp>

GameOverScreenView::GameOverScreenView()
{

}

void GameOverScreenView::setupScreen()
{
    GameOverScreenViewBase::setupScreen();
}

void GameOverScreenView::tearDownScreen()
{
    GameOverScreenViewBase::tearDownScreen();
}

void GameOverScreenView::setFinalScore(int score)
{
    Unicode::snprintf(textFinalScoreBuffer, TEXTFINALSCORE_SIZE, "%d", score);
    textFinalScore.invalidate();
}
