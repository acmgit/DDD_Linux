#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include <allegro/gfx.h>
#include <allegro/graphics.h>

class Playfield
{
    public:
        Playfield(BITMAP *currScreen, const int &Pos_x, const int &Pos_y, const int &Tilewidth, const int &Tileheight, const int &Tilecolumns, const int &Tilerows);
        ~Playfield();

        void drawTile(BITMAP *Sheet, const int &Sheetpos_x, const int &Sheetpos_y, int Column, int Row, const bool &transparency);

        void resetPlayfield(BITMAP *currScreen, const int &Pos_x, const int &Pos_y, const int &Tilewidth, const int &Tileheight, const int &Tilecolumns, const int &Tilerows);

    protected:
    private:

    BITMAP* Playfieldscreen;

    int Playfieldpos_x;
    int Playfieldpos_y;
    int Playfieldtileswidth;
    int Playfieldtilesheight;
    int Playfieldtilecolumns;
    int Playfieldtilerows;

};

#endif // PLAYFIELD_H
