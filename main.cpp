#include <iostream>
#include <allegro.h>
#include <string>

#include "Allegro_Input.h"
#include "Allegro_Output.h"
#include "Allegro_Datafile.h"
#include "UniText.h"

using namespace std;

#ifdef DEBUG

#include "Logfile.h"

CLog ErrorLog("data/Logfile.txt");

#endif // DEBUG

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

    } // if !MyOutput

    MyOutput->setConsole(ConsoleText_x, ConsoleText_y, ConsoleTextheight, ConsoleRows);
    MyOutput->setStatuswindow(StatusText_x, StatusText_y, StatusTextheight, StatusRows);
    MyOutput->setPlayfieldwindow(Playfield_x, Playfield_y, Playfield_tileWidth, Playfield_tileHeight, Playfield_columns, Playfield_rows);

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

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Programmstart.")
#endif // DEBUG

#ifdef DEBUG
    Log("Index for Datafile created.")
#endif // DEBUG

    Allegro_Output::gfx_Text renderText;
    Allegro_Output::gfx_Object renderTile;

    renderText.Foregroundcolor = MyData->findIndex("[COL_yellow]").Number;
    renderText.Backgroundcolor = MyData->findIndex("[COL_transparent]").Number;
    renderText.Pos_x = 10;
    renderText.Pos_y = (MyData->findIndex("[INI_Screenheight]").Number) - 40; //Screenheight - 30;

#ifdef DEBUG
    Log("Screenheight = " << MyData->findIndex("[INI_Screenheight]").Number)
#endif // DEBUG

    renderText.Text = Translator->Print("[Loading]");
    renderText.Text = renderText.Text + Datafilename;
    renderText.Text = renderText.Text + ".";
    renderText.toConvert = true;

    MyOutput->writeOnScreen(&renderText);
    MyOutput->renderScreen();

#ifdef DEBUG
    Log(renderText.Text.c_str())
#endif // DEBUG

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Files loaded.")
#endif // DEBUG


    MyOutput->setFont(MyData->getFont("[FNT_Title_big]"));
    MyOutput->setPalette(MyData->getPalette("[PAL_Font_Title_big]"));

    MyOutput->clearScreen(true);

    // Set up the Logo
    renderTile.Sheet = MyData->getBitmap("[SHE_Logo]");
    renderTile.Sheetpos_x = 0;
    renderTile.Sheetpos_y = 0;
    renderTile.Width = MyData->findIndex("[INI_Logowidth]").Number;                              // starting Height of the Logo
    renderTile.Height = MyData->findIndex("[INI_Logoheight]").Number;
    renderTile.Destinationpos_y = 0;
    renderTile.Destinationpos_x = (MyOutput->getScreenWidth() / 2) - (renderTile.Width / 2);
    renderTile.transparency = false;

    MyOutput->renderObject(&renderTile);
    MyOutput->writeOnScreen(&renderText);
    MyOutput->renderScreen();
    MyOutput->clearScreen(true);
    renderTile.Height = 0;

    for(int Logomove_y = 0; Logomove_y < 150; ++Logomove_y)
    {
        renderTile.Height = Logomove_y * 10;

        if(renderTile.Height > MyData->findIndex("[INI_Logoheight]").Number)
        {
            renderTile.Height = MyData->findIndex("[INI_Logoheight]").Number;

        } // if renderTile.Height

        renderTile.Destinationpos_y = Logomove_y;

        MyOutput->renderObject(&renderTile);                 // and render it
        MyOutput->writeOnScreen(&renderText);                // write the Loading-Screen
        MyOutput->renderScreen();

        MyOutput->clearScreen(true);                         // Clear the vitual Bitmap
        MyInput->setMiliSeconds(500);
        while(!MyInput->wait())
        {
            rest(1);
        } // wait 10 Miliseconds

    } // for Logomove_y

    renderText.Foregroundcolor = MyData->findIndex("[COL_transparent]").Number;
    renderText.Text = Translator->Print("[Presskey]");

    MyOutput->renderObject(&renderTile);
    MyOutput->writeOnScreen(&renderText);
    MyOutput->renderScreen();
    MyInput->getKey();
// ---- End of Intro ------

    MyOutput->setFont(MyData->getFont("[FNT_Game]"));

    MyOutput->setConsole(   MyData->findIndex("[INI_Consoletext_x]").Number,
                            MyData->findIndex("[INI_Consoletext_y]").Number,
                            MyData->findIndex("[INI_Textheight]").Number,
                            MyData->findIndex("[INI_Consolerowsmax]").Number);

    MyOutput->setStatuswindow(  MyData->findIndex("[INI_Statustext_x]").Number,
                                MyData->findIndex("[INI_Statustext_y]").Number,
                                MyData->findIndex("[INI_Textheight]").Number,
                                MyData->findIndex("[INI_Statusrowsmax]").Number);


    MyOutput->setPlayfieldwindow(   MyData->findIndex("[INI_Playfield_x]").Number,
                                    MyData->findIndex("[INI_Playfield_y]").Number,
                                    MyData->findIndex("[INI_Worldtileswidth]").Number,
                                    MyData->findIndex("[INI_Worldtilesheight]").Number,
                                    MyData->findIndex("[INI_Playfieldcolumns]").Number,
                                    MyData->findIndex("[INI_Playfieldrows]").Number);

    MyOutput->clearScreen(true);


    // Writes a Testtext on the Console
    for(int Consoleline = 0; Consoleline < 30; ++Consoleline)
    {
        MyOutput->clearScreen(true);             // Here it must be, because this is only a Test with more than max Rows (not mor needed in Game)
        if(Consoleline%4)
        {
            MyOutput->writeOnConsole(MyData->findIndex("[COL_yellow]").Number, MyData->findIndex("[COL_transparent]").Number, Translator->Print("[Waiting]") + MyData->inttostr(Consoleline), true);

        }
        else
        {
            MyOutput->writeOnConsole(MyData->findIndex("[COL_red]").Number, MyData->findIndex("[COL_transparent]").Number, Translator->Print("[Waiting]") + MyData->inttostr(Consoleline), false);

        } // if(i%2)

    } // for (Consoleline)

    // Writes a Testtext to the Statusscreen
    for(int Statusline = 0; Statusline <= MyData->findIndex("[INI_Statusrowsmax]").Number; ++Statusline)
    {
        if(Statusline%2)
        {
            MyOutput->addStatusLine(Statusline, 0, MyData->findIndex("[COL_green]").Number, MyData->findIndex("[COL_transparent]").Number, Translator->Print("[Statustesttext]") + MyData->inttostr(Statusline));

        }
        else
        {
            MyOutput->addStatusLine(Statusline, 0, MyData->findIndex("[COL_cyan]").Number, MyData->findIndex("[COL_transparent]").Number, Translator->Print("[Statustesttext]") + MyData->inttostr(Statusline));

        } // if(Statusline%2)

    } // for(Statusline)
    MyOutput->writeStatus();

    // Draw the Playfield
    Allegro_Output::tileData Tile;
    Tile.Sheet = MyData->getBitmap("[SHE_Worldtile]");
    Tile.Sheetpos_x = MyData->findIndex("[WTI_Gras]").Number;
    Tile.Sheetpos_y = 0;
    Tile.transparency = false;

    for(int Tile_Row = 0; Tile_Row < MyData->findIndex("[INI_Playfieldrows]").Number; ++Tile_Row)
    {
        for(int Tile_Column = 0; Tile_Column < MyData->findIndex("[INI_Playfieldcolumns]").Number; ++ Tile_Column)
        {
            #ifdef DEBUG
            Log("Row = " << Tile_Row << " Column = " << Tile_Column)
            #endif // DEBUG

            Tile.Column = Tile_Column;
            Tile.Row = Tile_Row;
            MyOutput->renderTile(Tile);

        } // for Tiles_Rows

    } // for Tiles_Columns

    // Enemy Skull
    Tile.transparency = true;
    Tile.Sheet = MyData->getBitmap("[SHE_Worldenemy]");
    Tile.Sheetpos_x = MyData->findIndex("[WEN_Skeleton]").Number;
    Tile.Column = 7;
    Tile.Row = 5;
    MyOutput->renderTile(Tile);

    // Enemy Bandit
    Tile.Sheetpos_x = MyData->findIndex("[WEN_Bandit]").Number;
    Tile.Column = 6;
    MyOutput->renderTile(Tile);

    // Enemy Zombie
    Tile.Sheetpos_x = MyData->findIndex("[WEN_Zombie]").Number;
    Tile.Column = 5;
    MyOutput->renderTile(Tile);

    // Hero
    Tile.Sheet = MyData->getBitmap("[SHE_Hero]");
    Tile.Sheetpos_x = MyData->findIndex("[HER_Sword]").Number;
    Tile.Column = 6;
    Tile.Row = 6;
    MyOutput->renderTile(Tile);

    // Town
    Tile.Sheet = MyData->getBitmap("[SHE_Towntile]");
    Tile.Sheetpos_x = MyData->findIndex("[TWN_Gaht]").Number;
    Tile.Column = 3;
    Tile.Row = 2;
    MyOutput->renderTile(Tile);

    // draws the Frame on the Screen
    renderTile.Sheet = MyData->getBitmap("[SHE_Frame]");
    renderTile.Sheetpos_x = 0;
    renderTile.Sheetpos_y = 0;
    renderTile.Destinationpos_x = 0;
    renderTile.Destinationpos_y = 0;
    renderTile.Width = MyOutput->getScreenWidth();
    renderTile.Height = MyOutput->getScreenHeight();
    renderTile.transparency = true;
    MyOutput->renderObject(&renderTile);

    // yeah, draw it Baby, draw it ...
    MyOutput->renderScreen();

    // and wait 10 Seconds for a Key
    MyInput->readKey(10);

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
