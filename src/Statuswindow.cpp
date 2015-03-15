#ifndef STATUSWINDOW_CPP
#define STATUSWINDOW_CPP

#include "Statuswindow.h"
#include "DDD_Screen.h"

#include <allegro/gfx.h>
#include <allegro/font.h>
#include <allegro/graphics.h>

#include <vector>
#include <string>

#ifdef DEBUG

#include "Logfile.h"

#endif // DEBUG

Statuswindow::Statuswindow(DDD_Screen *aktivScreen, BITMAP *currScreen, FONT *currFont, const int &Pos_x, const int &Pos_y, const int &TextHeight, const int &Rows)
{
    outputScreen = aktivScreen;
    reset_Statuswindow(currScreen, currFont, Pos_x, Pos_y, TextHeight, Rows);

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Statuswindow opened")
#endif // DEBUG

} // Statuswindow

Statuswindow::~Statuswindow()
{
    statusScreen = nullptr;
    statusFont = nullptr;

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Statuswindow closed")
#endif // DEBUG

} // ~Statuswindow

void Statuswindow::reset_Statuswindow(BITMAP *currStatusScreen, FONT *currStatusFont, const int &Pos_x, const int &Pos_y, const int &TextHeight, const int &Rows)
{
    statusScreen = currStatusScreen;
    statusFont = currStatusFont;

    statusPos_x = Pos_x;
    statusPos_y = Pos_y;
    statusTextheight = TextHeight;
    maxRows = Rows;

} // reset_Statuswindow

void Statuswindow::add_Row(const StatusText &newLine)
{
    Rows.push_back(newLine);

} // add_Row

void Statuswindow::write_Status()
{
    std::vector<StatusText>::iterator currLine;

    for(currLine = Rows.begin(); currLine != Rows.end(); ++currLine)
    {
        if(currLine->Row < 0)
        {
            currLine->Row = 0;

        } // if currLine < 0

        if(currLine->Row > maxRows)
        {
            currLine->Row = maxRows;

        } // if currLine > maxRows

        outputScreen->write_Text(statusScreen, statusFont,
                                currLine->Text,
                                currLine->Tab + statusPos_x, statusPos_y + (currLine->Row * statusTextheight),
                                currLine->Foreground, currLine->Background);

    } // for(currLine)

    Rows.clear();

    #ifdef DEBUG
    Log("Statuswindow written.")
    #endif // DEBUG

} // write_Status
#endif // STATUSWINDOW_CPP
