#ifndef DDD_SCREEN_H
#define DDD_SCREEN_H

#include <allegro/gfx.h>
#include <allegro/graphics.h>
#include <string>

class DDD_Screen
{
    public:
        DDD_Screen(int screenWidth, int screenHeight, int screenDepth, bool fullScreen);
        ~DDD_Screen();

        BITMAP *openVirtualScreen(const int &screenWidth, const int &screenHeight);
        void closeVirtualScreen(BITMAP *currScreen);

        void renderScreen(BITMAP *virtualScreen);

        void renderObject(BITMAP *Object, BITMAP *virtualScreen,
                          const int &Object_x, const int &Object_y,
                          const int &virtualScreen_x, const int virtualScreen_y,
                          const int &Width, const int Height, const bool &transparency);

        void writeText(BITMAP *virtualScreen, FONT *currFont,
                       std::string Text,
                       const int &textPos_x, const int &textPos_y,
                       const int &foregroundColor, const int &backgroundColor);


    private:
        BITMAP *openScreen(const int &screenWidth, const int &screenHeight, const int &screenDepth, const bool &fullScreen);

};

#endif // DDD_Screen_H
