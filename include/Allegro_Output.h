#ifndef ALLEGRO_OUTPUT_H
#define ALLEGRO_OUTPUT_H

#include "Screeninterface.h"
#include <allegro/gfx.h>
#include <allegro/font.h>

#include <string>

class Allegro_Output: public Screeninterface
{
    public:


        struct gfx_Object
        {
            int Sourcepos_x;
            int Sourcepos_y;
            int Destinationpos_x;
            int Destinationpos_y;
            int Width;
            int Height;
            bool transparency;
            BITMAP *Source;
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

        Allegro_Output(int Width, int Height, int Scrdepth, bool Fullscreen);
        ~Allegro_Output();

        void renderScreen();                                         // Renders the whole virtual Screen to Display
        void writeOnScreen(void *Text);                              // Writes the Text to the virtual Screen
        void renderObject(void *Object);                             // Renders the Object to the virtual Screen

        void clearScreen(bool Virtual);
        void setFont(FONT *newFont);


    private:

        void replace_all(std::string& text, const std::string& fnd, const std::string& rep);
        std::string convertText(std::string Text);

        BITMAP *Display;
        BITMAP *VirtualScreen;
        FONT *currFont;

        int Screenwidth;
        int Screenheight;
        int Screendepth;

}; // Allegro_Output

#endif // ALLEGRO_OUTPUT_H
