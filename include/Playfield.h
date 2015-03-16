#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include <allegro/gfx.h>
#include <allegro/graphics.h>

#include "DDD_Screen.h"

class Playfield
{
    public:
        Playfield(DDD_Screen *aktivScreen, const int &Pos_x, const int &Pos_y, const int &Tilewidth, const int &Tileheight, const int &Tilecolumns, const int &Tilerows);
        ~Playfield();

        void draw_Tile(BITMAP *Sheet, BITMAP *virtualScreen, const int &Sheetpos_x, const int &Sheetpos_y, int Column, int Row, const bool &transparency);

        void reset_Playfield(DDD_Screen *aktivScreen, const int &Pos_x, const int &Pos_y, const int &Tilewidth, const int &Tileheight, const int &Tilecolumns, const int &Tilerows);

    private:

    DDD_Screen *currScreen;

    int Playfieldpos_x;
    int Playfieldpos_y;
    int Playfieldtileswidth;
    int Playfieldtilesheight;
    int Playfieldtilecolumns;
    int Playfieldtilerows;

};

#endif // PLAYFIELD_H
