#ifndef DDD_SCREEN_CPP
#define DDD_SCREEN_CPP

#include "DDD_Screen.h"

#include <allegro/gfx.h>
#include <allegro/graphics.h>
#include <allegro/system.h>

#include <string>

#ifdef DEBUG
#include "Logfile.h"
#endif // DEBUG


DDD_Screen::DDD_Screen(int screenWidth, int screenHeight, int screenDepth, bool fullScreen)
{
    set_color_depth(screenDepth);

    openScreen(screenWidth, screenHeight, screenDepth, fullScreen);

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") DDD_Screenclass opened.")
    #endif // DEBUG

} // DDD_Screen()

DDD_Screen::~DDD_Screen()
{
    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") DDD_Screenclass closed.")
    #endif // DEBUG

} // ~DDD_Screen()

BITMAP *DDD_Screen::openScreen(const int &screenWidth, const int &screenHeight, const int &screenDepth, const bool &fullScreen)
{
    BITMAP *newScreen;

    set_color_depth(screenDepth);

    int screenError;
    if(fullScreen)
    {
        screenError = set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, screenWidth, screenHeight, 0, 0);

    }
    else
    {
        screenError = set_gfx_mode(GFX_AUTODETECT_WINDOWED, screenWidth, screenHeight, 0, 0);

    } // if Fullscreen

    if(screenError)
    {
#ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Fail to open Screen " << screenWidth << "x" << screenHeight << " Depth: " << screenDepth)
#endif // DEBUG

        allegro_message(allegro_error);
        newScreen = nullptr;

    } // if screenError
    else
    {
        newScreen = screen;

    } // if screenError

    return newScreen;

} // openScreen

BITMAP *DDD_Screen::openVirtualScreen(const int &screenWidth, const int &screenHeight)
{
    BITMAP *newBitmap;

    newBitmap = create_bitmap(screenWidth, screenHeight);
    if(!newBitmap)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Couldn't open a virtual Screen.")
        #endif // DEBUG

        allegro_message("Couldn't open a virtual Screen.");
    }

    return newBitmap;

} // openVirtualScreen

void DDD_Screen::renderScreen(BITMAP *virtualScreen)
{
    blit(virtualScreen, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    //show_video_bitmap(virtualScreen);

} // renderScreen

void DDD_Screen::renderObject(BITMAP *Object, BITMAP *virtualScreen,
                          const int &Object_x, const int &Object_y,
                          const int &virtualScreen_x, const int virtualScreen_y,
                          const int &Width, const int Height, const bool &transparency)
{
    if(transparency)
    {
        masked_blit(Object, virtualScreen, Object_x,  Object_y, virtualScreen_x, virtualScreen_y, Width, Height);

    }
    else
    {
        blit(Object, virtualScreen, Object_x,  Object_y, virtualScreen_x, virtualScreen_y, Width, Height);

    } // if transparency

} // renderObject

void DDD_Screen::writeText(BITMAP *virtualScreen, FONT *currFont,
                       std::string Text,
                       const int &textPos_x, const int &textPos_y,
                       const int &foregroundColor, const int &backgroundColor)
{
    textout_ex(virtualScreen, currFont, Text.c_str(), textPos_x, textPos_y, foregroundColor, backgroundColor);

} // writeText

void DDD_Screen::closeVirtualScreen(BITMAP *currScreen)
{
    if(currScreen)
    {
        destroy_bitmap(currScreen);
        #ifdef DEBUG
        Log("(" << ErrorLog.ALLOK << ") Screen closed.")
        #endif // DEBUG
        currScreen = nullptr;

    }
    else
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.ILLEGAL_ACCESS << ") virtual Screen not open.")
        #endif // DEBUG
        allegro_message("Virtual Screen not open ...");

    } // if(currScreen)

} // closeScreen


#endif // DDD_Screen_CPP
