#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <vector>

#include <allegro/gfx.h>
#include <allegro/graphics.h>
#include <allegro/font.h>

class Console
{
    public:

        struct ConsoleText
        {
            int Col;                                        // Color of the Text
            std::string CText;                              // Text
        };

        Console(BITMAP* CurrScreen, FONT* CurrFont, const int &Pos_x, const int &Pos_y, const int &TextHeight, const int &CRows);

        void writeOnConsole(ConsoleText currText);

    protected:
    private:

    std::vector<ConsoleText> Row;

    int startPos_x;
    int startPos_y;

    int textHeight;
    int maxRows;
    int nextRow;

    BITMAP* consoleScreen;
    FONT* consoleFont;

}; // Console

#endif // CONSOLE_H
