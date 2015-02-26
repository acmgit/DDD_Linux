#ifndef CONSOLE_CPP
#define CONSOLE_CPP

#include "Console.h"

#ifdef DEBUG

#include "Logfile.h"

#endif // DEBUG

#include <allegro/graphics.h>
#include <allegro/gfx.h>
#include <allegro/font.h>

Console::Console(BITMAP* CurrScreen, FONT* CurrFont, const int &Pos_x, const int &Pos_y, const int &TextHeight, const int &CRows)
{

    startPos_x = Pos_x;
    startPos_y = Pos_y;
    textHeight = TextHeight;
    maxRows = CRows;
    nextRow = 0;

#ifdef DEBUG
    Log("Next Row = " << nextRow << " Max Rows: " << maxRows)
#endif // DEBUG

    consoleScreen = CurrScreen;
    consoleFont = CurrFont;

} // Console

void Console::writeOnConsole(ConsoleText currText)
{
    Row.push_back(currText);
    if(nextRow > maxRows)
    {
        Row.erase(Row.begin());         // delete first Row
        nextRow = maxRows;

    } //if nextRow

    std::vector<ConsoleText>::iterator iterateRows;
    int currentRow = 0;

    for( iterateRows = Row.begin(); iterateRows != Row.end(); ++iterateRows)
    {

#ifdef DEBUG
        Log("startPos_y = " << startPos_y << ": currentRow = " << currentRow << ": Text = " << (*iterateRows).CText.c_str())
#endif
        textout_ex(consoleScreen, consoleFont, (*iterateRows).CText.c_str(), startPos_x, (startPos_y + (currentRow * textHeight)), (*iterateRows).Col, -1);
        ++currentRow;
#ifdef DEBUG
        Log("startPos_y = " << startPos_y << ": currentRow = " << currentRow)
#endif

    } // for Row.begin

    ++nextRow;

#ifdef DEBUG
    Log("Next Row: " << nextRow << " Max Rows: " << maxRows)
#endif // DEBUG

} // writeOnConsole

#endif // CONSOLE_CPP
