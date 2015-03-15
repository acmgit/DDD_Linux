#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <vector>

#include <allegro/gfx.h>
#include <allegro/graphics.h>
#include <allegro/font.h>
#include "DDD_Screen.h"

class Console
{
    public:

        struct ConsoleText
        {
            int Foreground;                                         // Forgroundcolor of the Text
            int Background;                                         // Backgroundcolor of the Text
            std::string CText;                                      // Text
        };

        Console(DDD_Screen *aktivScreen, FONT* CurrFont, BITMAP *VirtualScreen, const int &Pos_x, const int &Pos_y, const int &TextHeight, const int &CRows);
        ~Console();

        /*  Writes the given Text to the Console
            CurrText contains the Datas of the Text
            nextLine:   if true, then writes to the next Line of the Console
                        if false, then the new Text will append to the old Line and overwrite it with the given Colors of the Text to append
        */
        void write_OnConsole(ConsoleText currText, const bool nextLine);
        void reset_Console(DDD_Screen *aktivScreen, FONT* CurrFont, const int &Pos_x, const int &Pos_y, const int &TextHeight, const int &CRows);


    protected:
    private:

        void refresh_Console();

    std::vector<ConsoleText> Row;

    int startPos_x;
    int startPos_y;

    int textHeight;
    int maxRows;
    int nextRow;

    DDD_Screen *currScreen;
    BITMAP *virtualScreen;
    FONT* consoleFont;

}; // Console

#endif // CONSOLE_H
