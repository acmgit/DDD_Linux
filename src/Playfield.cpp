#ifndef PLAYFIELD_CPP
#define PLAYFIELD_CPP

#include "Playfield.h"
#include "DDD_Screen.h"

#include <allegro/gfx.h>
#include <allegro/graphics.h>

#ifdef DEBUG
#include "Logfile.h"
#endif // DEBUG

Playfield::Playfield(DDD_Screen *aktivScreen, const int &Pos_x, const int &Pos_y, const int &Tilewidth, const int &Tileheight, const int &Tilecolumns, const int &Tilerows)
{
    currScreen = aktivScreen;
    resetPlayfield(aktivScreen, Pos_x, Pos_y, Tilewidth, Tileheight, Tilecolumns, Tilerows);

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Playfieldwindow opened.")
    #endif // DEBUG

} // Playfield

Playfield::~Playfield()
{
    currScreen = nullptr;

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Playfieldwindow closed")
    #endif // DEBUG

} // ~Playfield

void Playfield::resetPlayfield(DDD_Screen *aktivScreen, const int &Pos_x, const int &Pos_y, const int &Tilewidth, const int &Tileheight, const int &Tilecolumns, const int &Tilerows)
{
    currScreen = aktivScreen;
    Playfieldpos_x = Pos_x;
    Playfieldpos_y = Pos_y;
    Playfieldtileswidth = Tilewidth;
    Playfieldtilesheight = Tileheight;
    Playfieldtilecolumns = Tilecolumns;
    Playfieldtilerows = Tilerows;

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Playfieldwindow reseted.")
#endif // DEBUG


} // resetPlayfield

void Playfield::drawTile(BITMAP *Sheetpos, BITMAP *virtualScreen, const int &Sheetpos_x, const int &Sheetpos_y, int Column, int Row, const bool &transparency)
{
    if(Column < Playfieldpos_x)
    {
        Column = Playfieldpos_x;

    } // if Column <

    if(Column > Playfieldtilecolumns)
    {
        Column = Playfieldtilecolumns;

    } // if Column >

    if(Row < Playfieldpos_y)
    {
        Row = Playfieldpos_y;

    } // if Row <

    if(Row > Playfieldtilerows)
    {
        Row = Playfieldtilerows;

    } // if Row >

    currScreen->renderObject(Sheetpos, virtualScreen,
                             Sheetpos_x, Sheetpos_y,
                             Playfieldpos_x + (Column * Playfieldtileswidth), Playfieldpos_y + (Row * Playfieldtileswidth),
                             Playfieldtileswidth, Playfieldtilesheight, transparency);
/*
    if(transparency)
    {
        masked_blit(    Sheetpos, Playfieldscreen,
                        Sheetpos_x, Sheetpos_y,
                        Playfieldpos_x + (Column * Playfieldtileswidth), Playfieldpos_y + (Row * Playfieldtileswidth),
                        Playfieldtileswidth, Playfieldtilesheight);

    }
    else
    {

        blit(   Sheetpos, Playfieldscreen,
                Sheetpos_x, Sheetpos_y,
                Playfieldpos_x + (Column * Playfieldtileswidth), Playfieldpos_y + (Row * Playfieldtileswidth),
                Playfieldtileswidth, Playfieldtilesheight);

    } // if transparency
*/

} // drawTile

#endif // PLAYFIEL_CPP
