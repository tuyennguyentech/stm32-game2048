#include <gui/containers/TileItem.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

TileItem::TileItem()
{
}

void TileItem::initialize()
{
    TileItemBase::initialize();
}

void TileItem::setNumber(int number)
{
    if (number == 0)
    {

        valueText.setVisible(false);
    }
    else
    {
        valueText.setVisible(true);
        Unicode::snprintf(valueTextBuffer, VALUETEXT_SIZE, "%d", number);
    }

    switch (number)
    {
    case 0:
        bgBox.setColor(touchgfx::Color::getColorFromRGB(205, 193, 180));
        break;
    case 2:
        bgBox.setColor(touchgfx::Color::getColorFromRGB(238, 228, 218));
        break;
    case 4:
        bgBox.setColor(touchgfx::Color::getColorFromRGB(237, 224, 200));
        break;
    case 8:
        bgBox.setColor(touchgfx::Color::getColorFromRGB(242, 177, 121));
        break;
    case 16:
        bgBox.setColor(touchgfx::Color::getColorFromRGB(245, 149, 99));
        break;
    case 32:
        bgBox.setColor(touchgfx::Color::getColorFromRGB(246, 124, 95));
        break;
    case 64:
        bgBox.setColor(touchgfx::Color::getColorFromRGB(246, 94, 59));
        break;

    case 128:
    case 256:
    case 512:
        bgBox.setColor(touchgfx::Color::getColorFromRGB(237, 207, 114));
        break;

    case 1024:
    case 2048:
        bgBox.setColor(touchgfx::Color::getColorFromRGB(237, 197, 63));
        break;

    default:
        bgBox.setColor(touchgfx::Color::getColorFromRGB(205, 193, 180));
        break;
    }


    bgBox.invalidate();
    valueText.invalidate();
}
