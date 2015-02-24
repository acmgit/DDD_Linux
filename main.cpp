#include <iostream>
#include <allegro.h>
#include <string>

#include "include/Allegro_Input.h"
#include "include/Allegro_Output.h"
#include "include/Allegro_Datafile.h"
#include "include/UniText.h"

using namespace std;

void exit_on_error(const std::string &Errormessage);

#ifdef DEBUG

#include "include/Logfile.h"

CLog ErrorLog("data/Logfile.txt");

#endif // DEBUG

int main()
{
    const int Screenwidth = 640;
    const int Screenheight = 480;
    const int Screendepth = 16;

    const std::string Datafilename = "data/gfx.dat";
    const std::string Indexfilename = "data/gfx.idx";
    const std::string Language = "data/DDD_Language.txt";
    const std::string Inifile = "data/DDD_Ini.txt";


    allegro_init();

    Allegro_Output MyOutput(Screenwidth, Screenheight, Screendepth, false);
    Allegro_Datafile MyData(Datafilename, Indexfilename, Inifile);
    Allegro_Input MyInput;
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

    MyOutput.setFont(MyData.getFont("[FNT_Game]"));

    renderTile.Sheet = MyData.getBitmap("[SHE_Worldtile]");
    renderTile.Sheetpos_x = MyData.findIndex("[WTI_Gras]").Number;
    renderTile.Sheetpos_y = 0;
    renderTile.transparency = true;
    renderTile.Width = MyData.findIndex("[INI_Worldtileswidth]").Number;
    renderTile.Height = MyData.findIndex("[INI_Worldtilesheight]").Number;


    for (int y = MyData.findIndex("[INI_Playfield_y]").Number; y < MyData.findIndex("[INI_Playfieldrows]").Number; ++y)
    {
        for(int x = MyData.findIndex("[INI_Playfield_x]").Number; x < MyData.findIndex("[INI_Playfieldcolumns]").Number; ++x)
        {
            renderTile.Destinationpos_x = x * MyData.findIndex("[INI_Worldtileswidth]").Number;
            renderTile.Destinationpos_y = y * MyData.findIndex("[INI_Worldtilesheight]").Number;
            MyOutput.renderObject(&renderTile);

        } // for x

    } // for y

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

    renderText.Foregroundcolor = MyData.findIndex("[COL_purple]").Number;
    renderText.Pos_x = MyData.findIndex("[INI_Consoletext_x]").Number;
    renderText.Text = Translator.Print("[Consoletesttext]");
    renderText.toConvert = true;

    for(int Consoleline = 0; Consoleline < 15; ++Consoleline)
    {
        renderText.Pos_y = MyData.findIndex("[INI_Consoletext_y]").Number + (Consoleline * MyData.findIndex("[INI_Textheight]").Number);
        MyOutput.writeOnScreen(&renderText);

    } // for i

    renderText.Text = Translator.Print("[Statustesttext]");
    renderText.Pos_x = MyData.findIndex("[INI_Statustext_x]").Number;
    renderText.Foregroundcolor = MyData.findIndex("[COL_gold]").Number;

    for(int Statusline = 0; Statusline < 30; ++Statusline)
    {
        renderText.Pos_y = MyData.findIndex("[INI_Statustext_y]").Number + (Statusline * MyData.findIndex("[INI_Textheight]").Number);
        MyOutput.writeOnScreen(&renderText);

    } // for i

    MyOutput.renderScreen();

    MyInput.readKey(10);

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

