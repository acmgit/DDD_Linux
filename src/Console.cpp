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

    resetConsole(CurrScreen, CurrFont, Pos_x, Pos_y, TextHeight, CRows);

#ifdef DEBUG
    Log("Next Row = " << nextRow << " Max Rows: " << maxRows)
#endif // DEBUG

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Console opened.")
#endif // DEBUG

} // Console

Console::~Console()
{
#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Console closed.")
#endif // DEBUG

} // ~Console

void Console::writeOnConsole(ConsoleText currText, const bool nextLine)
{
    if(nextLine)                                                        // Writes a new Consoleline
    {
        Row.push_back(currText);                                        // add new Line on the Console

        if(nextRow > maxRows)                                           // Console full?
        {
            Row.erase(Row.begin());                                     // delete first Row
            nextRow = maxRows;

        } //if nextRow

        ++nextRow;                                                      // and increase the Rownumber

    }
    else                                                                // add on last Consoleline
    {
        #ifdef DEBUG
        Log("Write new Text on Console to append <" << currText.CText.c_str() << ">")
        #endif // DEBUG

        if(!Row.empty())                                                // Console has Lines to add Text
        {
            std::vector<ConsoleText>::iterator iterateRows;
            iterateRows = Row.end();
            --iterateRows;                                              // Sets the Iterator to the last Line

            currText.CText = (*iterateRows).CText + currText.CText;     // get the last Line and append the new Text to the line
            Row.pop_back();                                             // delete the last Line in Row
            Row.push_back(currText);                                    // and add the new Line on the Row

        }
        else                                                            // Console has no Line to append Text
        {

            Row.push_back(currText);                                    // so you can simply add this Line

        } // if Row.empty

    }   // if(nextLine)

    refreshConsole();

} // writeOnConsole(currText)

void Console::refreshConsole()
{
    std::vector<ConsoleText>::iterator iterateRows;

    int currentRow = 0;                                                 // is needed to calculate the next Line

    for( iterateRows = Row.begin(); iterateRows != Row.end(); ++iterateRows)
    {
        textout_ex(consoleScreen, consoleFont, (*iterateRows).CText.c_str(), startPos_x, (startPos_y + (currentRow * textHeight)), (*iterateRows).Foreground, (*iterateRows).Background);
        ++currentRow;

    } // for Row.begin()

} // refreshConsole

void Console::resetConsole(BITMAP *CurrScreen, FONT *CurrFont, const int &Pos_x, const int &Pos_y, const int &TextHeight, const int &CRows)
{
    consoleScreen = CurrScreen;
    consoleFont = CurrFont;

    startPos_x = Pos_x;
    startPos_y = Pos_y;
    textHeight = TextHeight;
    maxRows = CRows;
    nextRow = 0;

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Consolewindow reseted.")
#endif // DEBUG

} // resetConsole

#endif // CONSOLE_CPP
