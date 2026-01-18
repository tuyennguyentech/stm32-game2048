#ifndef RANKINGSCREENVIEW_HPP
#define RANKINGSCREENVIEW_HPP

#include <gui_generated/rankingscreen_screen/RankingScreenViewBase.hpp>
#include <gui/rankingscreen_screen/RankingScreenPresenter.hpp>

class RankingScreenView : public RankingScreenViewBase
{
public:
    RankingScreenView();
    virtual ~RankingScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void showHighScores(int *scores);
    void highlightRank(int rankIndex);
protected:
};

#endif // RANKINGSCREENVIEW_HPP
