#include <allegro.h>
/*
#include <iostream>
#include <string>
#include <allegro/graphics.h>

#include "Allegro_Input.h"
#include "Allegro_Output.h"
#include "Allegro_Datafile.h"
#include "UniText.h"
#include "Mapinterface.h"
#include "Clock.h"
*/

#include "game.h"

using namespace std;

#ifdef DEBUG

#include "Logfile.h"

CLog ErrorLog("data/Logfile.txt");

#endif // DEBUG

void shade(BITMAP *dest, float howMuch);

int main()
{
/*
    const int Screenwidth = 640;
    const int Screenheight = 480;
    const int Screendepth = 16;
    const int ConsoleText_x = 10;
    const int ConsoleText_y = 324;
    const int ConsoleTextheight = 10;
    const int ConsoleRows = 14;
    const int StatusText_x = 387;
    const int StatusText_y = 12;
    const int StatusTextheight = ConsoleTextheight;
    const int StatusRows = 30;
    const int Playfield_x = 0;
    const int Playfield_y = 0;
    const int Playfield_columns = 12;
    const int Playfield_rows = 10;
    const int Playfield_tileWidth = 32;
    const int Playfield_tileHeight = 32;


    const std::string Datafilename = "data/gfx.dat";
    const std::string Indexfilename = "data/gfx.idx";
    const std::string Language = "data/DDD_Language.txt";
    const std::string Inifile = "data/DDD_Ini.txt";

*/
    allegro_init();


    game *MyGame;
    MyGame = new game();

    if(!MyGame)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Couldn't open Gameclass.")
        #endif // DEBUG
        allegro_message("Couldn't open Gameclass");
        allegro_exit();

    } // if !MyGame

    MyGame->init();

    MyGame->run();

    MyGame->exit();

    if(MyGame)
    {
        delete MyGame;
        MyGame = nullptr;

    } // if MyGame

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Programm exited.")
#endif // DEBUG

    return 0;
} // main
END_OF_MAIN()


// If howMuch is 1, dest is turned black.  If howMuch is 0, dest is left unchanged
void shade(BITMAP *dest, float howMuch)
{
    const int val = (int)(howMuch * 0xff);

    set_trans_blender(0x20, 0x20, 0x20, val);
    drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
    rectfill(dest, 0, 0, dest->w, dest->h, makeacol32(0xff, 0xff, 0xff, val));
    drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
}
