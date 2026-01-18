#ifndef TILEITEM_HPP
#define TILEITEM_HPP

#include <gui_generated/containers/TileItemBase.hpp>

class TileItem : public TileItemBase
{
public:
    TileItem();
    virtual ~TileItem() {}

    virtual void initialize();

    void setNumber(int number);
protected:
};

#endif // TILEITEM_HPP
