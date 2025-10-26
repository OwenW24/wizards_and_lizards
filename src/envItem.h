#ifndef ENVITEM_H
#define ENVITEM_H
#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

class EnvItem
{
    public:
        Rectangle rect;
        int blocking;
        int base;
        Color color;
        EnvItem(Rectangle rect, Color color, int blocking, int base=0);

};

#endif