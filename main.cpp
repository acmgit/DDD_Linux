#include <iostream>
#include <allegro.h>
#include <string>

#include "include/Allegro_Input.h"
#include "include/Allegro_Output.h"
#include "Allegro_Datafile.h"
#include "UniText.h"

using namespace std;

void exit_on_error(const std::string &Errormessage);

#ifdef DEBUG

#include "Logfile.h"

CLog ErrorLog("data/Logfile.txt");

#endif // DEBUG

int main()
{
    const int Screenwidth = 640;
    const int Screenheight = 480;
    const int Screendepth = 16;

    const int WorldTilesheetwidth = 416;
    const int HeroTilesheetwidth = 288;
    const int EnemyTilesheetwidth = 1248;
    const int TownTilesheetwidth = 416;

    const int Logowidth = 240;
    const int Logoheight = 151;

    const int Playfield_x = 0;
    const int Playfield_y = 0;
    const int Playfieldcolumns = 12;                // Tiles
    const int Playfieldrows = 10;                   // Tiles

    const int Textheight = 10;
    const int Textwidth = 8;

    const int Consoletext_x = 10;
    const int Consoletext_y = 324;

    const int Statustext_x = 387;
    const int Statustext_y = 12;

    const std::string Datafilename = "data/gfx.dat";
    const std::string Indexfilename = "data/gfx.idx";
    const std::string Language = "data/DDD_Language.txt";

    allegro_init();

    Allegro_Output MyOutput(Screenwidth, Screenheight, Screendepth, false);
    Allegro_Input MyInput;
    Allegro_Datafile MyData(Datafilename, Indexfilename);
    UniText Translator(Language);

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Programmstart.")
#endif // DEBUG

    Allegro_Datafile::Index MyIndex;


#ifdef DEBUG
    Log("Index for Datafile created.")
#endif // DEBUG

    Allegro_Output::gfx_Text renderText;
    Allegro_Output::gfx_Object renderTile;

    renderText.Foregroundcolor = MyData.findIndex("[COL_yellow]").Number;
    renderText.Backgroundcolor = MyData.findIndex("[COL_transparent]").Number;
    renderText.Pos_x = 10;
    renderText.Pos_y = Screenheight - 30;
    renderText.Text = Translator.Print("[Loading]");
    renderText.Text = renderText.Text + Datafilename;
    renderText.Text = renderText.Text + ".";
    renderText.toConvert = true;

    MyOutput.writeOnScreen(&renderText);
    MyOutput.renderScreen();

#ifdef DEBUG
    Log(renderText.Text.c_str())
#endif // DEBUG

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Files loaded.")
#endif // DEBUG


    MyOutput.setFont(MyData.getFont("[FNT_Title_big]"));
    MyOutput.setPalette(MyData.getPalette("[PAL_Font_Title_big]"));

    MyOutput.clearScreen(true);

    // Set up the Logo
    renderTile.Sheet = MyData.getBitmap("[SHE_Logo]");
    renderTile.Sheetpos_x = 0;
    renderTile.Sheetpos_y = 0;
    renderTile.Width = Logowidth;                              // starting Height of the Logo
    renderTile.Height = Logoheight;
    renderTile.Destinationpos_y = 0;
    renderTile.Destinationpos_x = (MyOutput.getScreenWidth() / 2) - (renderTile.Width / 2);
    renderTile.transparency = false;

    MyOutput.renderObject(&renderTile);
    MyOutput.writeOnScreen(&renderText);
    MyOutput.renderScreen();
    MyOutput.clearScreen(true);
    renderTile.Height = 0;

    for(int Logomove_y = 0; Logomove_y < 150; ++Logomove_y)
    {
        renderTile.Height = Logomove_y * 10;

        if(renderTile.Height > Logoheight)
        {
            renderTile.Height = Logoheight;

        } // if renderTile.Height

        renderTile.Destinationpos_y = Logomove_y;

        MyOutput.renderObject(&renderTile);                 // and render it
        MyOutput.writeOnScreen(&renderText);                // write the Loading-Screen
        MyOutput.renderScreen();

        MyOutput.clearScreen(true);                         // Clear the vitual Bitmap
        rest(10);

    } // for Logomove_y

    renderText.Foregroundcolor = MyData.findIndex("[COL_transparent]").Number;
    renderText.Text = Translator.Print("[Presskey]");
    MyOutput.renderObject(&renderTile);
    MyOutput.writeOnScreen(&renderText);
    MyOutput.renderScreen();

    MyInput.getKey();

    MyOutput.clearScreen(true);

    MyOutput.setFont(MyData.getFont("[FNT_Game]"));

    renderTile.Sheet = MyData.getBitmap("[SHE_Worldtile]");
    renderTile.Sheetpos_x = MyData.findIndex("[WTI_Gras]").Number;
    renderTile.Sheetpos_y = 0;
    renderTile.transparency = true;
    renderTile.Width = MyData.getTilewidth();
    renderTile.Height = MyData.getTileheight();


    for (int y = Playfield_y; y < Playfieldrows; ++y)
    {
        for(int x = Playfield_x; x < Playfieldcolumns; ++x)
        {
            renderTile.Destinationpos_x = x * MyData.getTilewidth();
            renderTile.Destinationpos_y = y * MyData.getTileheight();
            MyOutput.renderObject(&renderTile);

        } // for x

    } // for y

    renderTile.Sheet = MyData.getBitmap("[SHE_Worldenemy]");
    renderTile.Sheetpos_x = MyData.findIndex("[WEN_Skeleton]").Number;
    renderTile.Destinationpos_x = 7 * MyData.getTilewidth();
    renderTile.Destinationpos_y = 4 * MyData.getTileheight();
    MyOutput.renderObject(&renderTile);

    renderTile.Sheetpos_x = MyData.findIndex("[WEN_Bandit]").Number;
    renderTile.Destinationpos_x = 6 * MyData.getTilewidth();
    MyOutput.renderObject(&renderTile);

    renderTile.Sheetpos_x = MyData.findIndex("[WEN_Zombie]").Number;
    renderTile.Destinationpos_x = 5 * MyData.getTilewidth();
    MyOutput.renderObject(&renderTile);

    renderTile.Sheet = MyData.getBitmap("[SHE_Hero]");
    renderTile.Sheetpos_x = MyData.findIndex("[HER_Sword]").Number;
    renderTile.Destinationpos_x = 6 * MyData.getTilewidth();
    renderTile.Destinationpos_y = 5 * MyData.getTileheight();
    MyOutput.renderObject(&renderTile);

    renderTile.Sheet = MyData.getBitmap("[SHE_Towntile]");
    renderTile.Sheetpos_x = MyData.findIndex("[TWN_Mubrak]").Number;
    renderTile.Destinationpos_x = 3 * MyData.getTilewidth();
    renderTile.Destinationpos_y = 2 * MyData.getTileheight();
    MyOutput.renderObject(&renderTile);

    renderTile.Sheet = MyData.getBitmap("[SHE_Frame]");
    renderTile.Sheetpos_x = 0;
    renderTile.Sheetpos_y = 0;
    renderTile.Destinationpos_x = 0;
    renderTile.Destinationpos_y = 0;
    renderTile.Width = MyOutput.getScreenWidth();
    renderTile.Height = MyOutput.getScreenHeight();
    MyOutput.renderObject(&renderTile);

    renderText.Foregroundcolor = MyData.findIndex("[COL_purple]").Number;
    renderText.Pos_x = Consoletext_x;
    renderText.Text = Translator.Print("[Consoletesttext]");
    renderText.toConvert = true;

    for(int Consoleline = 0; Consoleline < 15; ++Consoleline)
    {
        renderText.Pos_y = Consoletext_y + (Consoleline * Textheight);
        MyOutput.writeOnScreen(&renderText);

    } // for i

    renderText.Text = Translator.Print("[Statustesttext]");
    renderText.Pos_x = Statustext_x;
    renderText.Foregroundcolor = MyData.findIndex("[COL_gold]").Number;

    for(int Statusline = 0; Statusline < 30; ++Statusline)
    {
        renderText.Pos_y = Statustext_y + (Statusline * Textheight);
        MyOutput.writeOnScreen(&renderText);

    } // for i

    MyOutput.renderScreen();

    do
    {
    }
    while(!MyInput.readKey());

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Programm exited.")
#endif // DEBUG

    return 0;
} // main
END_OF_MAIN()


void exit_on_error(const std::string &Errormessage)
{
#ifdef DEBUG
    Log("(AE " << *allegro_errno << ") " << Errormessage.c_str())
#endif // DEBUG

    allegro_message("%d - %s", *allegro_errno, Errormessage.c_str());
    allegro_exit();

} // exit_on_error

