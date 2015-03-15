#ifndef ALLEGRO_OUTPUT_H
#define ALLEGRO_OUTPUT_H

#include "Console.h"
#include "Statuswindow.h"
#include "Playfield.h"
#include "DDD_Screen.h"

#include <allegro/gfx.h>
#include <allegro/graphics.h>
#include <allegro/font.h>

#include <string>

class Allegro_Output
{
    public:

        struct screenData
        {
            int screenWidth;
            int screenHeight;
            int screenDepth;
            bool Fullscreen;
        };

        struct tileData
        {
            int Sheetpos_x;
            int Sheetpos_y;
            int Column;
            int Row;
            bool transparency;
            BITMAP *Sheet;
        };

        struct gfx_Object
        {
            int Sheetpos_x;
            int Sheetpos_y;
            int Destinationpos_x;
            int Destinationpos_y;
            int Width;
            int Height;
            bool transparency;
            BITMAP *Sheet;
        };

        struct gfx_Text
        {
            int Pos_x;
            int Pos_y;
            int Foregroundcolor;
            int Backgroundcolor;
            std::string Text;
            bool toConvert;
        };

        Allegro_Output(const screenData &Data);

        ~Allegro_Output();

        void render_Screen();                                         // Renders the whole virtual Screen to Display

        void write_OnScreen(gfx_Text *Text);
        void write_OnConsole(const int FCol, const int BCol, const std::string CText, const bool nextLine);

        void add_StatusLine(const int &Row, const int &Tab, const int &FCol, const int &BCol, const std::string &SText);
        void write_Status();

        void render_Object(gfx_Object *Object);
        void render_Tile(const tileData Tile);

        void clear_Screen(bool Virtual);                              // Clears the Virtual Screen if true, else the Display
        void set_Faderpause(const int Pause);
        void screen_FadeIn(const int speed, BITMAP *to_Fadein);
        void screen_FadeOut(const int speed, BITMAP *to_Fadeout);

        void set_Font(FONT *newFont);
        void set_Palette(PALETTE *newPalette);
        void set_Console(const int &Pos_x, const int &Pos_y, const int &TextHeight, const int &Rows);
        void set_Statuswindow(const int &Pos_x, const int &Pos_y, const int &TextHeight, const int &Rows);
        void set_Playfieldwindow(const int &Pos_x, const int &Pos_y, const int &Tilewidth, const int &Tileheight, const int &Tilecolumns, const int &Tilerows);

        int get_ScreenWidth();
        int get_ScreenHeight();
        int get_ScreenDepth();

        BITMAP *get_VirtualScreen();
    private:

        void replace_all(std::string& text, const std::string& fnd, const std::string& rep);
        std::string convert_Text(std::string Text);

        BITMAP *Display;
        BITMAP *VirtualScreen;
        FONT *currFont;

        DDD_Screen *outputScreen;
        Console *outputConsole;
        Statuswindow *outputStatus;
        Playfield *outputPlayfield;

        int Screenwidth;
        int Screenheight;
        int Screendepth;

}; // Allegro_Output

#endif // ALLEGRO_OUTPUT_H
