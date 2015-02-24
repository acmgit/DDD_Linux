#ifndef ALLEGRO_OUTPUT_H
#define ALLEGRO_OUTPUT_H

#include "Screeninterface.h"

#include <allegro/gfx.h>
#include <allegro/graphics.h>
#include <allegro/font.h>

#include <string>

class Allegro_Output: public Screeninterface
{
    public:

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

        Allegro_Output(int Width, int Height, int Scrdepth, bool Fullscreen);
        Allegro_Output():Allegro_Output(640, 480, 16, false){};     // delegated Constructor

        ~Allegro_Output();

        void renderScreen();                                         // Renders the whole virtual Screen to Display

        void writeOnScreen(void *Text);                              // Writes the Text to the virtual Screen
        void writeOnScreen(gfx_Text *Text);

        void renderObject(void *Object);                             // Renders the Object to the virtual Screen
        void renderObject(gfx_Object *Object);

        void clearScreen(bool Virtual);                              // Clears the Virtual Screen if true, else the Display

        void setFont(FONT *newFont);
        void setPalette(PALETTE *newPalette);

        int getScreenWidth();
        int getScreenHeight();
        int getScreenDepth();

        void drawAnimation(const int ID);
        void drawAllAnimations();

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
