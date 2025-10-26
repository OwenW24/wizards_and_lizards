#include "envItem.h"

EnvItem::EnvItem(Rectangle rect, int blocking, Color color)
{
    this->rect = rect;
    this->blocking = blocking;
    this->color = color;
}