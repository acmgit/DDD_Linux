#ifndef STATUSWINDOW_H
#define STATUSWINDOW_H

#include <allegro/gfx.h>
#include <allegro/font.h>
#include <vector>
#include <string>

class Statuswindow
{
    public:
        struct StatusText
        {
            int Row;                                // the Row, where the Text should be writed
            int Tab;                                // Tabinformation in Pixel
            int Foreground;                         // Forgroundcolor
            int Background;                         // Backgroundcolor
            std::string Text;                       // Text for the Statuswindowrow
        };

        Statuswindow(BITMAP *currScreen, FONT *currFont, const int &Pos_x, const int &Pos_y, const int &TextHeight, const int &Rows);
        ~Statuswindow();
        void addRow(const StatusText &newLine);
        void writeStatus();

        void resetStatuswindow(BITMAP *currScreen, FONT *currFont, const int &Pos_x, const int &Pos_y, const int &Textheight, const int &Rows);

    protected:
    private:

    BITMAP *statusScreen;
    FONT *statusFont;

    int statusPos_x;
    int statusPos_y;
    int statusTextheight;
    int maxRows;

    std::vector<StatusText> Rows;

}; // Statuswindow

#endif // STATUSWINDOW_H
