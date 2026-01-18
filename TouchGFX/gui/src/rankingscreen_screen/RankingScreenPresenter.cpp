#include <gui/rankingscreen_screen/RankingScreenView.hpp>
#include <gui/rankingscreen_screen/RankingScreenPresenter.hpp>

RankingScreenPresenter::RankingScreenPresenter(RankingScreenView& v)
    : view(v)
{

}

void RankingScreenPresenter::activate()
{
	view.showHighScores(model->getHighScores());
	view.highlightRank(model->getNewRankIndex());
}

void RankingScreenPresenter::deactivate()
{
	model->clearNewRankIndex();
}
