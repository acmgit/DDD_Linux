#include <iostream>
#include <allegro.h>
#include <string>
#include <allegro/graphics.h>

#include "Allegro_Input.h"
#include "Allegro_Output.h"
#include "Allegro_Datafile.h"
#include "UniText.h"
#include "Mapinterface.h"
#include "Clock.h"

using namespace std;

#ifdef DEBUG

#include "Logfile.h"

CLog ErrorLog("data/Logfile.txt");

#endif // DEBUG

void shade(BITMAP *dest, float howMuch);

int main()
{
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


    allegro_init();

    Allegro_Output::screenData startScreen;

    startScreen.screenHeight = Screenheight;
    startScreen.screenWidth = Screenwidth;
    startScreen.screenDepth = Screendepth;
    startScreen.Fullscreen = false;

    Allegro_Output *MyOutput = nullptr;
    MyOutput = new Allegro_Output(startScreen);

    if(!MyOutput)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Couldn't open Allegro_Outputscreen.")
        #endif // DEBUG
        allegro_message("Couldn't open Allegro_Outputscreen");
        allegro_exit();

    } // if !MyOutputfind_Index

    MyOutput->set_Console(ConsoleText_x, ConsoleText_y, ConsoleTextheight, ConsoleRows);
    MyOutput->set_Statuswindow(StatusText_x, StatusText_y, StatusTextheight, StatusRows);
    MyOutput->set_Playfieldwindow(Playfield_x, Playfield_y, Playfield_tileWidth, Playfield_tileHeight, Playfield_columns, Playfield_rows);

    Allegro_Datafile *MyData = nullptr;
    MyData = new Allegro_Datafile(Datafilename, Indexfilename, Inifile);

    if(!MyData)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Couldn't open Allegro_Dataclass.")
        #endif // DEBUG
        allegro_message("Couldn't open Allegro_Dataclass");
        allegro_exit();

    } // if !MyOutput

    Allegro_Input *MyInput = nullptr;
    MyInput = new Allegro_Input();

    if(!MyData)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Couldn't open Allegro_Inputclass.")
        #endif // DEBUG
        allegro_message("Couldn't open Allegro_Dataclass");
        allegro_exit();

    } // if !MyOutput

    UniText *Translator = nullptr;
    Translator = new UniText(Language);

    if(!Translator)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Couldn't open Unitext.")
        #endif // DEBUG
        allegro_message("Couldn't open Unitext");
        allegro_exit();

    } // if !MyOutput

    Mapinterface *currMaps = nullptr;
    currMaps = new Mapinterface(MyData);

    if(!currMaps)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Couldn't open Mapinterface.")
        #endif // DEBUG
        allegro_message("Couldn't open Mapinterface");
        allegro_exit();

    } // if currBattlemap

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Programmstart.")
#endif // DEBUG

#ifdef DEBUG
    Log("Index for Datafile created.")
#endif // DEBUG

    Allegro_Output::gfx_Text renderText;
    Allegro_Output::gfx_Object renderTile;

    renderText.Foregroundcolor = MyData->find_Index("[COL_yellow]").Number;
    renderText.Backgroundcolor = MyData->find_Index("[COL_transparent]").Number;
    renderText.Pos_x = 10;
    renderText.Pos_y = (MyData->find_Index("[INI_Screenheight]").Number) - 40; //Screenheight - 30;

#ifdef DEBUG
    Log("Screenheight = " << MyData->find_Index("[INI_Screenheight]").Number)
#endif // DEBUG

    renderText.Text = Translator->Print("[Loading]");
    renderText.Text = renderText.Text + Datafilename;
    renderText.Text = renderText.Text + ".";
    renderText.toConvert = true;

    MyOutput->write_OnScreen(&renderText);
    MyOutput->render_Screen();

#ifdef DEBUG
    Log(renderText.Text.c_str())
#endif // DEBUG

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Files loaded.")
#endif // DEBUG


    MyOutput->set_Font(MyData->get_Font("[FNT_Title_big]"));
    MyOutput->set_Palette(MyData->get_Palette("[PAL_Font_Title_big]"));

    MyOutput->clear_Screen(true);

    // Set up the Logo
    renderTile.Sheet = MyData->get_Bitmap("[SHE_Logo]");
    renderTile.Sheetpos_x = 0;
    renderTile.Sheetpos_y = 0;
    renderTile.Width = MyData->find_Index("[INI_Logowidth]").Number;                              // starting Height of the Logo
    renderTile.Height = MyData->find_Index("[INI_Logoheight]").Number;
    renderTile.Destinationpos_y = 0;
    renderTile.Destinationpos_x = (MyOutput->get_ScreenWidth() / 2) - (renderTile.Width / 2);
    renderTile.transparency = false;

    MyOutput->render_Object(&renderTile);
    MyOutput->write_OnScreen(&renderText);
    MyOutput->render_Screen();
    MyOutput->clear_Screen(true);
    renderTile.Height = 0;

    for(int Logomove_y = 0; Logomove_y < 150; ++Logomove_y)
    {
        renderTile.Height = Logomove_y * 10;

        if(renderTile.Height > MyData->find_Index("[INI_Logoheight]").Number)
        {
            renderTile.Height = MyData->find_Index("[INI_Logoheight]").Number;

        } // if renderTile.Height

        renderTile.Destinationpos_y = Logomove_y;

        MyOutput->render_Object(&renderTile);                 // and render it
        MyOutput->write_OnScreen(&renderText);                // write the Loading-Screen
        MyOutput->render_Screen();

        MyOutput->clear_Screen(true);                         // Clear the vitual Bitmap
        MyInput->set_MilliSeconds(500);
        while(!MyInput->wait())
        {
            rest(1);
        } // wait 10 Miliseconds

    } // for Logomove_y

    renderText.Foregroundcolor = MyData->find_Index("[COL_transparent]").Number;
    renderText.Text = Translator->Print("[Presskey]");

    MyOutput->render_Object(&renderTile);
    MyOutput->write_OnScreen(&renderText);
    MyOutput->render_Screen();
    MyInput->get_Key();
// ---- End of Intro ------

    MyOutput->set_Font(MyData->get_Font("[FNT_Game]"));

    MyOutput->set_Console(  MyData->find_Index("[INI_Consoletext_x]").Number,
                            MyData->find_Index("[INI_Consoletext_y]").Number,
                            MyData->find_Index("[INI_Textheight]").Number,
                            MyData->find_Index("[INI_Consolerowsmax]").Number);

    MyOutput->set_Statuswindow( MyData->find_Index("[INI_Statustext_x]").Number,
                                MyData->find_Index("[INI_Statustext_y]").Number,
                                MyData->find_Index("[INI_Textheight]").Number,
                                MyData->find_Index("[INI_Statusrowsmax]").Number);


    MyOutput->set_Playfieldwindow(  MyData->find_Index("[INI_Playfield_x]").Number,
                                    MyData->find_Index("[INI_Playfield_y]").Number,
                                    MyData->find_Index("[INI_Worldtileswidth]").Number,
                                    MyData->find_Index("[INI_Worldtilesheight]").Number,
                                    MyData->find_Index("[INI_Playfieldcolumns]").Number,
                                    MyData->find_Index("[INI_Playfieldrows]").Number);

    MyOutput->clear_Screen(true);


    // Writes a Testtext on the Console
    for(int Consoleline = 0; Consoleline < 30; ++Consoleline)
    {
        MyOutput->clear_Screen(true);             // Here it must be, because this is only a Test with more than max Rows (not mor needed in Game)
        if(Consoleline%4)
        {
            MyOutput->write_OnConsole(MyData->find_Index("[COL_yellow]").Number, MyData->find_Index("[COL_transparent]").Number, Translator->Print("[Waiting]") + " " + MyData->valtostr(Consoleline), true);

        }
        else
        {
            MyOutput->write_OnConsole(MyData->find_Index("[COL_red]").Number, MyData->find_Index("[COL_transparent]").Number, Translator->Print("[Waiting]") + " " + MyData->valtostr(Consoleline), false);

        } // if(i%2)

    } // for (Consoleline)

    // Writes a Testtext to the Statusscreen
    for(int Statusline = 0; Statusline <= MyData->find_Index("[INI_Statusrowsmax]").Number; ++Statusline)
    {
        if(Statusline%2)
        {
            MyOutput->add_StatusLine(Statusline, 0, MyData->find_Index("[COL_green]").Number, MyData->find_Index("[COL_transparent]").Number, Translator->Print("[Statustesttext]") + MyData->valtostr(Statusline));

        }
        else
        {
            MyOutput->add_StatusLine(Statusline, 0, MyData->find_Index("[COL_cyan]").Number, MyData->find_Index("[COL_transparent]").Number, Translator->Print("[Statustesttext]") + MyData->valtostr(Statusline));

        } // if(Statusline%2)

    } // for(Statusline)
    MyOutput->write_Status();

    Allegro_Output::tileData Tile;
    Tile.Sheetpos_y = 0;

    currMaps->generate_Battlemap("Gras");
    Mapinterface::Tiledata currTile;
    Tile.transparency = false;

    // Draw the Battlemap
    for(int Tile_Row = 0; Tile_Row < MyData->find_Index("[INI_Playfieldrows]").Number; ++Tile_Row)
    {
        for(int Tile_Column = 0; Tile_Column < MyData->find_Index("[INI_Playfieldcolumns]").Number; ++Tile_Column)
        {
            currTile = currMaps->get_Tile(Mapinterface::Battlemaptile, Tile_Column, Tile_Row);
            Tile.Sheet = currTile.Sheet;
            Tile.Sheetpos_x = currTile.Index;
            Tile.Column = Tile_Column;
            Tile.Row = Tile_Row;
            MyOutput->render_Tile(Tile);

        } // for Column

    } // for Row
    // Enemy Skull
    Tile.transparency = true;
    Tile.Sheet = MyData->get_Bitmap("[SHE_Worldenemy]");
    Tile.Sheetpos_x = MyData->find_Index("[WEN_Skeleton]").Number;
    Tile.Column = 7;
    Tile.Row = 5;
    MyOutput->render_Tile(Tile);

    // Enemy Bandit
    Tile.Sheetpos_x = MyData->find_Index("[WEN_Bandit]").Number;
    Tile.Column = 6;
    MyOutput->render_Tile(Tile);

    // Enemy Zombie
    Tile.Sheetpos_x = MyData->find_Index("[WEN_Zombie]").Number;
    Tile.Column = 5;
    MyOutput->render_Tile(Tile);

    // Hero
    Tile.Sheet = MyData->get_Bitmap("[SHE_Hero]");
    Tile.Sheetpos_x = MyData->find_Index("[HER_Sword]").Number;
    Tile.Column = 6;
    Tile.Row = 6;
    MyOutput->render_Tile(Tile);

    // Town
    Tile.Sheet = MyData->get_Bitmap("[SHE_Towntile]");
    Tile.Sheetpos_x = MyData->find_Index("[TWN_Gaht]").Number;
    Tile.Column = 3;
    Tile.Row = 2;
    MyOutput->render_Tile(Tile);

    // draws the Frame on the Screen
    renderTile.Sheet = MyData->get_Bitmap("[SHE_Frame]");
    renderTile.Sheetpos_x = 0;
    renderTile.Sheetpos_y = 0;
    renderTile.Destinationpos_x = 0;
    renderTile.Destinationpos_y = 0;
    renderTile.Width = MyOutput->get_ScreenWidth();
    renderTile.Height = MyOutput->get_ScreenHeight();
    renderTile.transparency = true;
    MyOutput->render_Object(&renderTile);

    // yeah, draw it Baby, draw it ...
    MyOutput->set_Faderpause(50);
    MyOutput->screen_FadeIn(10, MyOutput->get_VirtualScreen());

    // and wait 10 Seconds for a Key
    MyInput->read_Key(10);



    //Fade_out(10, MyOutput->get_VirtualScreen());
    MyOutput->screen_FadeOut(10, MyOutput->get_VirtualScreen());

    //MyInput->readKey(5);

    if(currMaps)
    {
        delete currMaps;
        currMaps = nullptr;

    } // if currBattlemap

    if(Translator)
    {
        delete Translator;
        Translator = nullptr;

    } // if Translator

    if(MyInput)
    {
        delete MyInput;
        MyInput = nullptr;

    } // if MyData

    if(MyData)
    {
        delete MyData;
        MyData = nullptr;

    } // if MyData

    if(MyOutput)
    {
        delete MyOutput;
        MyOutput = nullptr;

    } // if MyOutput

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
