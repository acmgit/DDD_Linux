#ifndef CONSOLE_CPP
#define CONSOLE_CPP

#include "Console.h"
#include "DDD_Screen.h"

#ifdef DEBUG

#include "Logfile.h"

#endif // DEBUG

#include <allegro/graphics.h>
#include <allegro/gfx.h>
#include <allegro/font.h>

Console::Console(DDD_Screen *aktivScreen, FONT *aktivFont, BITMAP *VirtualScreen, const int &Pos_x, const int &Pos_y, const int &TextHeight, const int &CRows)
{
    virtualScreen = VirtualScreen;
    currScreen = aktivScreen;
    consoleFont = aktivFont;
    reset_Console(currScreen, consoleFont, Pos_x, Pos_y, TextHeight, CRows);

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

void Console::write_OnConsole(ConsoleText currText, const bool nextLine)
{
    if(nextLine)                                                        // Writes a new Consoleline
    {
        Row.push_back(currText);                                        // add new Line on the Console
        #ifdef DEBUG
        Log("(" << ErrorLog.ALLOK << ") Console Line inserted (nextLine=true): " << currText.CText.c_str())
        #endif // DEBUG

        if(nextRow > maxRows)                                           // Console full?
        {
            Row.erase(Row.begin());                                     // delete first Row
            nextRow = maxRows;

        } //if nextRow

        ++nextRow;                                                      // and increase the Rownumber

    }
    else                                                                // add on last Consoleline
    {
        if(!Row.empty())                                                // Console has Lines to add Text
        {
            std::vector<ConsoleText>::iterator iterateRows;
            iterateRows = Row.end();
            --iterateRows;                                              // Sets the Iterator to the last Line

            //currText.CText = (*iterateRows).CText + currText.CText;     // get the last Line and append the new Text to the line
            Row.pop_back();                                             // delete the last Line in Row
            Row.push_back(currText);                                    // and add the new Line on the Row
            #ifdef DEBUG
            Log("(" << ErrorLog.ALLOK << ") Console Line inserted (nextLine=true, !empty): " << currText.CText.c_str())
            #endif // DEBUG

        }
        else                                                            // Console has no Line to append Text
        {

            Row.push_back(currText);                                    // so you can simply add this Line
            #ifdef DEBUG
            Log("(" << ErrorLog.ALLOK << ") Console Line inserted (nextLine=true, empty): " << currText.CText.c_str())
            #endif // DEBUG

        } // if Row.empty

    }   // if(nextLine)

    refresh_Console();

} // write_OnConsole(currText)

void Console::refresh_Console()
{
    clear_Console();
    std::vector<ConsoleText>::iterator iterateRows;

    int currentRow = 0;                                                 // is needed to calculate the next Line

    for( iterateRows = Row.begin(); iterateRows != Row.end(); ++iterateRows)
    {
        currScreen->write_Text(virtualScreen, consoleFont,
                              (*iterateRows).CText,
                              startPos_x, (startPos_y + (currentRow * textHeight)),
                              (*iterateRows).Foreground, (*iterateRows).Background);

        //textout_ex(consoleScreen, consoleFont, (*iterateRows).CText.c_str(), startPos_x, (startPos_y + (currentRow * textHeight)), (*iterateRows).Foreground, (*iterateRows).Background);
        ++currentRow;
        #ifdef DEBUG
        Log("(" << ErrorLog.ALLOK << ") Writing Consoleline: " << (*iterateRows).CText.c_str())
        #endif // DEBUG

    } // for Row.begin()

} // refresh_Console

void Console::clear_Console()
{
    rectfill(virtualScreen, startPos_x, startPos_y, SCREEN_W - 10, SCREEN_H - 10, makecol(0, 0, 0));

} // clear_Console

void Console::reset_Console(DDD_Screen *aktivScreen, FONT *CurrFont, const int &Pos_x, const int &Pos_y, const int &TextHeight, const int &CRows)
{
    currScreen = aktivScreen;
    consoleFont = CurrFont;

    startPos_x = Pos_x;
    startPos_y = Pos_y;
    textHeight = TextHeight;
    maxRows = CRows;
    nextRow = 0;

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Consolewindow reseted.")
#endif // DEBUG

} // reset_Console

#endif // CONSOLE_CPP
