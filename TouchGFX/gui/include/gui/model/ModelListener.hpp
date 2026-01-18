#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    virtual void updateGridDisplay(int grid[4][4]) {}

    virtual void updateScore(int score) {}

    virtual void switchToGameOver() {}
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
