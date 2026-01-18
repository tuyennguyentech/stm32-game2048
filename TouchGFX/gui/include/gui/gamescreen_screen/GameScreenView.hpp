#ifndef GAMESCREENVIEW_HPP
#define GAMESCREENVIEW_HPP

#include <gui_generated/gamescreen_screen/GameScreenViewBase.hpp>
#include <gui/gamescreen_screen/GameScreenPresenter.hpp>
#include <gui/containers/TileItem.hpp>

class GameScreenView : public GameScreenViewBase
{
public:
    GameScreenView();
    virtual ~GameScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void updateBoardFromMatrix(int matrix[4][4]);
    void requestNewGame();
    void setScore(int score);
protected:
    TileItem* tiles[4][4];
};

#endif // GAMESCREENVIEW_HPP
