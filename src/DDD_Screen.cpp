#ifndef DDD_SCREEN_CPP
#define DDD_SCREEN_CPP

#include "DDD_Screen.h"
#include "Clock.h"

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

    fader_Pause = 50;

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

BITMAP *DDD_Screen::open_VirtualScreen(const int &screenWidth, const int &screenHeight)
{
    BITMAP *newBitmap;

    newBitmap = create_system_bitmap(screenWidth, screenHeight);
    if(!newBitmap)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Couldn't open a virtual Screen.")
        #endif // DEBUG

        allegro_message("Couldn't open a virtual Screen.");
    }

    return newBitmap;

} // open_VirtualScreen

void DDD_Screen::render_Screen(BITMAP *virtualScreen)
{
    blit(virtualScreen, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    //show_video_bitmap(virtualScreen);

} // render_Screen

void DDD_Screen::render_Object(BITMAP *Object, BITMAP *virtualScreen,
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

} // render_Object

void DDD_Screen::write_Text(BITMAP *virtualScreen, FONT *currFont,
                       std::string Text,
                       const int &textPos_x, const int &textPos_y,
                       const int &foregroundColor, const int &backgroundColor)
{
    textout_ex(virtualScreen, currFont, Text.c_str(), textPos_x, textPos_y, foregroundColor, backgroundColor);

} // write_Text

void DDD_Screen::close_VirtualScreen(BITMAP *currScreen)
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

void DDD_Screen::fade_In(int speed, BITMAP *to_Fadein)
{
    Clock *Pause;
    Pause = new Clock();

    if (speed <= 0) speed = 16;

    for (int a = 0 + speed; a <= 255; a+=speed)
    {
        set_trans_blender(0,0,0,a);
        draw_trans_sprite(screen, to_Fadein, 0, 0);
        vsync();
        Pause->set_MilliSeconds(fader_Pause);
        while(!Pause->wait())
        {
        }

    } // for a

    blit(to_Fadein, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    delete Pause;

} // fade_In

void DDD_Screen::fade_Out(int speed, BITMAP *to_Fadeout)
{
    BITMAP *bmp_buff;
    Clock *Pause;
    Pause = new Clock();

    if ((bmp_buff = create_system_bitmap(SCREEN_W, SCREEN_H)))
    {
        blit(screen, to_Fadeout, 0,0, 0,0, SCREEN_W, SCREEN_H);
        if (speed <= 0)
        {
            speed = 16;

        } // if speed

        for (int a = 255-speed; a > 0; a-=speed)
        {
            clear_bitmap(bmp_buff);
            set_trans_blender(0,0,0,a);
            draw_trans_sprite(bmp_buff, to_Fadeout, 0, 0);
            vsync();
            blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            Pause->set_MilliSeconds(fader_Pause);
            while(!Pause->wait())
            {
            }

        } // for a

        destroy_bitmap(bmp_buff);

    } // if((bmp_buff)

    delete Pause;
    rectfill(screen, 0,0, SCREEN_W,SCREEN_H, makecol(0,0,0));
    // Fade out end ---------------------------------

} // fade_Out

void DDD_Screen::set_Faderpause(int Pause)
{
    if(Pause <= 0)
    {
        Pause = 1;

    } // Pause

    fader_Pause = Pause;

} // set_Faderpause

#endif // DDD_Screen_CPP
