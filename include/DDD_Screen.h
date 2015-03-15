#ifndef DDD_SCREEN_H
#define DDD_SCREEN_H

#include <allegro/gfx.h>
#include <allegro/graphics.h>
#include <allegro/system.h>

#include <string>

class DDD_Screen
{
    public:
        DDD_Screen(int screenWidth, int screenHeight, int screenDepth, bool fullScreen);
        ~DDD_Screen();

        // Screenfunctions
        BITMAP *open_VirtualScreen(const int &screenWidth, const int &screenHeight);
        void close_VirtualScreen(BITMAP *currScreen);

        // Faderfunctions
        void fade_In(int speed, BITMAP *to_Fadein);
        void fade_Out(int speed, BITMAP *to_Fadeout);
        void set_Faderpause(int Pause);

        // drawing Functions
        void render_Screen(BITMAP *virtualScreen);
        void render_Object(BITMAP *Object, BITMAP *virtualScreen,
                          const int &Object_x, const int &Object_y,
                          const int &virtualScreen_x, const int virtualScreen_y,
                          const int &Width, const int Height, const bool &transparency);

        // writing Functions
        void write_Text(BITMAP *virtualScreen, FONT *currFont,
                       std::string Text,
                       const int &textPos_x, const int &textPos_y,
                       const int &foregroundColor, const int &backgroundColor);


    private:
        BITMAP *openScreen(const int &screenWidth, const int &screenHeight, const int &screenDepth, const bool &fullScreen);

        int fader_Pause;
};

#endif // DDD_Screen_H
