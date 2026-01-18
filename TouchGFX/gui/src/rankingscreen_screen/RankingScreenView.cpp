#include <gui/rankingscreen_screen/RankingScreenView.hpp>

RankingScreenView::RankingScreenView()
{

}

void RankingScreenView::setupScreen()
{
    RankingScreenViewBase::setupScreen();
}

void RankingScreenView::tearDownScreen()
{
    RankingScreenViewBase::tearDownScreen();
}

void RankingScreenView::showHighScores(int* scores)
{
    Unicode::snprintf(textScore0Buffer, TEXTSCORE0_SIZE, "%d", scores[0]);
    textScore0.invalidate();

    Unicode::snprintf(textScore1Buffer, TEXTSCORE1_SIZE, "%d", scores[1]);
    textScore1.invalidate();

    Unicode::snprintf(textScore2Buffer, TEXTSCORE2_SIZE, "%d", scores[2]);
    textScore2.invalidate();

    Unicode::snprintf(textScore3Buffer, TEXTSCORE3_SIZE, "%d", scores[3]);
    textScore3.invalidate();

    Unicode::snprintf(textScore4Buffer, TEXTSCORE4_SIZE, "%d", scores[4]);
    textScore4.invalidate();
}

void RankingScreenView::highlightRank(int rankIndex)
{
    if (rankIndex >= 0 && rankIndex < 5)
    {
        int startY = 70;
        int stepY = 40;
        int newY = startY + (rankIndex * stepY);

        highlightContainer.setY(newY);

        highlightContainer.setVisible(true);
        highlightContainer.invalidate();
    }
    else
    {
        highlightContainer.setVisible(false);
        highlightContainer.invalidate();
    }
}

