#ifndef ENVITEM_H
#define ENVITEM_H

#include "raylib.h"
#include "raymath.h"

class EnvItem
{
    public:
        Rectangle rect;
        int blocking;
        Color color;

        EnvItem(Rectangle rect, int blocking, Color color);

};

#endif