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
    startScreen.consolePos_x = ConsoleText_x;
    startScreen.consolePos_y = ConsoleText_y;
    startScreen.consoleTextheight = ConsoleTextheight;
    startScreen.consoleRows = ConsoleRows;
    startScreen.statusPos_x = StatusText_x;
    startScreen.statusPos_y = StatusText_y;
    startScreen.statusTextheight = StatusTextheight;
    startScreen.statusRows = StatusRows;

    Allegro_Output MyOutput(startScreen);
    Allegro_Datafile MyData(Datafilename, Indexfilename, Inifile);
    Allegro_Input MyInput;
    UniText Translator(Language);

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Programmstart.")
#endif // DEBUG

#ifdef DEBUG
    Log("Index for Datafile created.")
#endif // DEBUG

    Allegro_Output::gfx_Text renderText;
    Allegro_Output::gfx_Object renderTile;

    renderText.Foregroundcolor = MyData.findIndex("[COL_yellow]").Number;
    renderText.Backgroundcolor = MyData.findIndex("[COL_transparent]").Number;
    renderText.Pos_x = 10;
    renderText.Pos_y = (MyData.findIndex("[INI_Screenheight]").Number) - 40; //Screenheight - 30;

#ifdef DEBUG
    Log("Screenheight = " << MyData.findIndex("[INI_Screenheight]").Number)
#endif // DEBUG

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
    renderTile.Width = MyData.findIndex("[INI_Logowidth]").Number;                              // starting Height of the Logo
    renderTile.Height = MyData.findIndex("[INI_Logoheight]").Number;
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

        if(renderTile.Height > MyData.findIndex("[INI_Logoheight]").Number)
        {
            renderTile.Height = MyData.findIndex("[INI_Logoheight]").Number;

        } // if renderTile.Height

        renderTile.Destinationpos_y = Logomove_y;

        MyOutput.renderObject(&renderTile);                 // and render it
        MyOutput.writeOnScreen(&renderText);                // write the Loading-Screen
        MyOutput.renderScreen();

        MyOutput.clearScreen(true);                         // Clear the vitual Bitmap
        MyInput.setMiliSeconds(500);
        while(!MyInput.wait())
        {
            rest(1);
        } // wait 10 Miliseconds

    } // for Logomove_y

    renderText.Foregroundcolor = MyData.findIndex("[COL_transparent]").Number;
    renderText.Text = Translator.Print("[Presskey]");

    MyOutput.renderObject(&renderTile);
    MyOutput.writeOnScreen(&renderText);
    MyOutput.renderScreen();

    MyInput.getKey();

    MyOutput.clearScreen(true);

    // Writes a Testtext on the Console
    for(int i = 0; i < 30; ++i)
    {
        MyOutput.clearScreen(true);             // Here it must be, because this is only a Test with more than max Rows
        if(i%4)
        {
            MyOutput.writeOnConsole(MyData.findIndex("[COL_yellow]").Number, MyData.findIndex("[COL_transparent]").Number, Translator.Print("[Waiting]") + MyData.inttostr(i), true);

        }
        else
        {
            MyOutput.writeOnConsole(MyData.findIndex("[COL_red]").Number, MyData.findIndex("[COL_transparent]").Number, Translator.Print("[Waiting]") + MyData.inttostr(i), false);

        } // if(i%2)

    }

    // Draws the Playwindow
    MyOutput.setFont(MyData.getFont("[FNT_Game]"));

    renderTile.Sheet = MyData.getBitmap("[SHE_Worldtile]");
    renderTile.Sheetpos_x = MyData.findIndex("[WTI_Gras]").Number;
    renderTile.Sheetpos_y = 0;
    renderTile.transparency = true;
    renderTile.Width = MyData.findIndex("[INI_Worldtileswidth]").Number;
    renderTile.Height = MyData.findIndex("[INI_Worldtilesheight]").Number;

    // Draw the Tiles on the Playwindow
    for (int y = MyData.findIndex("[INI_Playfield_y]").Number; y < MyData.findIndex("[INI_Playfieldrows]").Number; ++y)
    {
        for(int x = MyData.findIndex("[INI_Playfield_x]").Number; x < MyData.findIndex("[INI_Playfieldcolumns]").Number; ++x)
        {
            renderTile.Destinationpos_x = x * MyData.findIndex("[INI_Worldtileswidth]").Number;
            renderTile.Destinationpos_y = y * MyData.findIndex("[INI_Worldtilesheight]").Number;
            MyOutput.renderObject(&renderTile);

        } // for x

    } // for y

    // Fill the Playwindow with Enemys, Hero and a Town
    renderTile.Sheet = MyData.getBitmap("[SHE_Worldenemy]");
    renderTile.Sheetpos_x = MyData.findIndex("[WEN_Skeleton]").Number;
    renderTile.Destinationpos_x = 7 * MyData.findIndex("[INI_Worldtileswidth]").Number;
    renderTile.Destinationpos_y = 4 * MyData.findIndex("[INI_Worldtilesheight]").Number;
    MyOutput.renderObject(&renderTile);

    renderTile.Sheetpos_x = MyData.findIndex("[WEN_Bandit]").Number;
    renderTile.Destinationpos_x = 6 * MyData.findIndex("[INI_Worldtileswidth]").Number;
    MyOutput.renderObject(&renderTile);

    renderTile.Sheetpos_x = MyData.findIndex("[WEN_Zombie]").Number;
    renderTile.Destinationpos_x = 5 * MyData.findIndex("[INI_Worldtileswidth]").Number;
    MyOutput.renderObject(&renderTile);

    renderTile.Sheet = MyData.getBitmap("[SHE_Hero]");
    renderTile.Sheetpos_x = MyData.findIndex("[HER_Sword]").Number;
    renderTile.Destinationpos_x = 6 * MyData.findIndex("[INI_Worldtileswidth]").Number;
    renderTile.Destinationpos_y = 5 * MyData.findIndex("[INI_Worldtilesheight]").Number;
    MyOutput.renderObject(&renderTile);

    renderTile.Sheet = MyData.getBitmap("[SHE_Towntile]");
    renderTile.Sheetpos_x = MyData.findIndex("[TWN_Gaht]").Number;
    renderTile.Destinationpos_x = 3 * MyData.findIndex("[INI_Worldtileswidth]").Number;
    renderTile.Destinationpos_y = 2 * MyData.findIndex("[INI_Worldtilesheight]").Number;
    MyOutput.renderObject(&renderTile);

    renderTile.Sheet = MyData.getBitmap("[SHE_Frame]");
    renderTile.Sheetpos_x = 0;
    renderTile.Sheetpos_y = 0;
    renderTile.Destinationpos_x = 0;
    renderTile.Destinationpos_y = 0;
    renderTile.Width = MyOutput.getScreenWidth();
    renderTile.Height = MyOutput.getScreenHeight();
    MyOutput.renderObject(&renderTile);

    MyOutput.setStatuswindow(MyData.findIndex("[INI_Statustext_x]").Number,
                             MyData.findIndex("[INI_Statustext_y]").Number,
                             MyData.findIndex("[INI_Textheight]").Number,
                             MyData.findIndex("[INI_Statusrowsmax]").Number);


    for(int Statusline = 0; Statusline <= MyData.findIndex("[INI_Statusrowsmax]").Number; ++Statusline)
    {
        if(Statusline%2)
        {
            MyOutput.addStatusLine(Statusline, 0, MyData.findIndex("[COL_green]").Number, MyData.findIndex("[COL_transparent]").Number, Translator.Print("[Statustesttext]") + MyData.inttostr(Statusline));

        }
        else
        {
            MyOutput.addStatusLine(Statusline, 0, MyData.findIndex("[COL_cyan]").Number, MyData.findIndex("[COL_transparent]").Number, Translator.Print("[Statustesttext]") + MyData.inttostr(Statusline));

        } // if(Statusline%2)

    } // for(Statusline)

    MyOutput.writeStatus();

    // yeah, draw it Baby, draw it ...
    MyOutput.renderScreen();

    // and wait 10 Seconds for a Key
    MyInput.readKey(10);

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Programm exited.")
#endif // DEBUG

    return 0;
} // main
END_OF_MAIN()
