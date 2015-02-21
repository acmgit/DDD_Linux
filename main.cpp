#include <iostream>
#include <allegro.h>
#include <string>

#include "include/Allegro_Input.h"
#include "include/Allegro_Output.h"
#include "Allegro_Datafile.h"

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

    const int Tilewidth = 32;
    const int Tileheight = 32;
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

    allegro_init();


    //Allegro_Output MyOutput;
    Allegro_Output MyOutput(Screenwidth, Screenheight, Screendepth, false);
    Allegro_Input MyInput;
    Allegro_Datafile MyData(Datafilename);

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Programmstart.")
#endif // DEBUG

    Allegro_Datafile::Index MyIndex;

/* Index for the Sheets in DDD
    -------------------------------------------------
*/
    MyIndex.Name = "Sheet_Font";
    MyIndex.Number = 0;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Sheet_Frame";
    MyIndex.Number = 1;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Sheet_Hero";
    MyIndex.Number = 2;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Sheet_Logo";
    MyIndex.Number = 3;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Sheet_Towntiles";
    MyIndex.Number = 4;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Sheet_Worldtiles";
    MyIndex.Number = 5;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Sheet_Worldenemys";
    MyIndex.Number = 6;
    MyData.addIndex(MyIndex);

/*  Index of Colors in DDD
    -------------------------------------------------
*/
    MyIndex.Name = "Col_red";
    MyIndex.Number = makecol(255,  50,    50);
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Col_orange";
    MyIndex.Number = makecol(255,  100,    0);
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Col_blue";
    MyIndex.Number = makecol(50,   50,   255);
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Col_purple";
    MyIndex.Number = makecol(255,  50,   255);
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Col_green";
    MyIndex.Number = makecol(50,   255,   50);
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Col_cyan";
    MyIndex.Number = makecol(50,   255,  255);
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Col_yellow";
    MyIndex.Number = makecol(255,  255,   50);
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Col_gold";
    MyIndex.Number = makecol(255,  200,   50);
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Col_brown";
    MyIndex.Number = makecol(200,  100,    0);
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Col_white";
    MyIndex.Number = makecol(250,  250,  250);
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Col_lightgrey";
    MyIndex.Number = makecol(200,  200,  200);
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Col_silver";
    MyIndex.Number = makecol(150,  150,  150);
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Col_darkgrey";
    MyIndex.Number = makecol(100,  100,  100);
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Col_black";
    MyIndex.Number = makecol(0,    0,    0);
    MyData.addIndex(MyIndex);

    MyIndex.Name = "Col_transparent";
    MyIndex.Number = -1;
    MyData.addIndex(MyIndex);

/*  Index of Enemytiles on the Worldenemyspritesheet
    -------------------------------------------------
*/
    // Goblin
    MyIndex.Name = "WE_Goblin";
    MyIndex.Number = 0;
    MyData.addIndex(MyIndex);

    // Zombie
    MyIndex.Name = "WE_Zombie";
    MyIndex.Number = Tilewidth;
    MyData.addIndex(MyIndex);

    // Räuber
    MyIndex.Name = "WE_Bandit";
    MyIndex.Number = 2 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Wassermann
    MyIndex.Name = "WE_Aquarius";
    MyIndex.Number = 3 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Sandviper
    MyIndex.Name = "WE_Sandviper";
    MyIndex.Number = 4 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Ork
    MyIndex.Name = "WE_Orc";
    MyIndex.Number = 5 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Skelett
    MyIndex.Name = "WE_Skeleton";
    MyIndex.Number = 6 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Pirat
    MyIndex.Name = "WE_Pirate";
    MyIndex.Number = 7 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Nesselbaum
    MyIndex.Name = "WE_Hackberry";
    MyIndex.Number = 8 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Wildpferd
    MyIndex.Name = "WE_Wildhorse";
    MyIndex.Number = 9 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Seepferd
    MyIndex.Name = "WE_Seahorse";
    MyIndex.Number = 10 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Ghul
    MyIndex.Name = "WE_Ghoul";
    MyIndex.Number = 11 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Waldschrat
    MyIndex.Name = "WE_Forestdemon";
    MyIndex.Number = 12 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Einhorn
    MyIndex.Name = "WE_Wildunicorn";
    MyIndex.Number = 13 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Oger
    MyIndex.Name = "WE_Ogre";
    MyIndex.Number = 14 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Auerochse
    MyIndex.Name = "WE_Aurochs";
    MyIndex.Number = 15 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Vampir
    MyIndex.Name = "WE_Vampire";
    MyIndex.Number = 16 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Troll (Brückentroll)
    MyIndex.Name = "WE_Troll";
    MyIndex.Number = 17 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Seeschlange
    MyIndex.Name = "WE_Seaserpent";
    MyIndex.Number = 18 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Riesenpython
    MyIndex.Name = "WE_Giantpython";
    MyIndex.Number = 19 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Werwolf
    MyIndex.Name = "WE_Werewolf";
    MyIndex.Number = 20 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Höhlenspinne
    MyIndex.Name = "WE_Raftspider";
    MyIndex.Number = 21 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Mumie
    MyIndex.Name = "WE_Mummy";
    MyIndex.Number = 22 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Riesenkrake
    MyIndex.Name = "WE_Giantoctopus";
    MyIndex.Number = 23 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Höhlenschrat
    MyIndex.Name = "WE_Cavedemon";
    MyIndex.Number = 24 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Feuerechse
    MyIndex.Name = "WE_Firelizard";
    MyIndex.Number = 25 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Zweihaupt
    MyIndex.Name = "WE_Doublehead";
    MyIndex.Number = 26 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Zauberer
    MyIndex.Name = "WE_Wizard";
    MyIndex.Number = 27 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Dämon
    MyIndex.Name = "WE_Demon";
    MyIndex.Number = 28 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Speihkobra
    MyIndex.Name = "WE_Spittincobra";
    MyIndex.Number = 29 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Höhlenspinne
    MyIndex.Name = "WE_Scaffoldwebspider";
    MyIndex.Number = 30 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Riesenaffe
    MyIndex.Name = "WE_Giantape";
    MyIndex.Number = 31 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Jungdrache
    MyIndex.Name = "WE_Youngdragon";
    MyIndex.Number = 32 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Zyklop
    MyIndex.Name = "WE_Cyclops";
    MyIndex.Number = 33 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Balrog
    MyIndex.Name = "WE_Balrog";
    MyIndex.Number = 34 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Hydra
    MyIndex.Name = "WE_Hydra";
    MyIndex.Number = 35 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Riese
    MyIndex.Name = "WE_Giant";
    MyIndex.Number = 36 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Drache
    MyIndex.Name = "WE_Wilddragon";
    MyIndex.Number = 37 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Totes Monster
    MyIndex.Name = "WE_Deadenemy";
    MyIndex.Number = 38 * Tilewidth;
    MyData.addIndex(MyIndex);

/*  Index of Herotiles on the Herospritesheet
    -------------------------------------------------
*/

    // Held nur mit Einhandwaffe
    MyIndex.Name = "HERO_Sword";
    MyIndex.Number = 0;
    MyData.addIndex(MyIndex);

    // Held mit Einhandwaffe und Schild
    MyIndex.Name = "HERO_Shield";
    MyIndex.Number = Tilewidth;
    MyData.addIndex(MyIndex);

    // Held nur mit Einhandwaffe (vergiftet)
    MyIndex.Name = "HERO_Sword_poisoned";
    MyIndex.Number = 2 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Held mit Einhandwaffe und Schild (vergiftet)
    MyIndex.Name = "HERO_Shield_poisoned";
    MyIndex.Number = 3 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Held auf Pferd
    MyIndex.Name = "HERO_on_Horse";
    MyIndex.Number = 4 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Held auf Einhorn
    MyIndex.Name = "HERO_on_Unicorn";
    MyIndex.Number = 5 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Held auf Schiff
    MyIndex.Name = "HERO_on_Ship";
    MyIndex.Number = 6 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Held auf Feuerechse
    MyIndex.Name = "HERO_on_Dragon";
    MyIndex.Number = 7 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Held tot
    MyIndex.Name = "HERO_dead";
    MyIndex.Number = 8 * Tilewidth;
    MyData.addIndex(MyIndex);

/*  Index of Towntiles on the Townsheet
    -------------------------------------------------
*/
    MyIndex.Name = "TWN_Secretcave";
    MyIndex.Number = 0;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "TWN_Druidshack";
    MyIndex.Number = Tilewidth;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "TWN_Ackbah";
    MyIndex.Number = 2 * Tilewidth;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "TWN_Worthal";
    MyIndex.Number = 3 * Tilewidth;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "TWN_Trisdisk";
    MyIndex.Number = 4 * Tilewidth;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "TWN_Gaht";
    MyIndex.Number = 5 * Tilewidth;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "TWN_Mubrak";
    MyIndex.Number = 6 * Tilewidth;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "TWN_Muspel";
    MyIndex.Number = 7 * Tilewidth;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "TWN_Madraskan";
    MyIndex.Number = 8 * Tilewidth;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "TWN_Royalpalace";
    MyIndex.Number = 9 * Tilewidth;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "TWN_Blacktower";
    MyIndex.Number = 10 * Tilewidth;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "TWN_Whitetower";
    MyIndex.Number = 11 * Tilewidth;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "TWN_Fulgarpalace";
    MyIndex.Number = 12 * Tilewidth;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "TWN_Dragoncave";
    MyIndex.Number = 13 * Tilewidth;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "TWN_Swampdungeon";
    MyIndex.Number = 14 * Tilewidth;
    MyData.addIndex(MyIndex);

    MyIndex.Name = "TWN_Crystaldungeon";
    MyIndex.Number = 15 * Tilewidth;
    MyData.addIndex(MyIndex);

/*  Index of Worldtiles on the Worldtilesheet
    -------------------------------------------------
*/

    // Meer
    MyIndex.Name = "WT_Sea";
    MyIndex.Number = 0;
    MyData.addIndex(MyIndex);

    // Fluss, seichtes Meer
    MyIndex.Name = "WT_River";
    MyIndex.Number = Tilewidth;
    MyData.addIndex(MyIndex);

    // Wald
    MyIndex.Name = "WT_Forest";
    MyIndex.Number = 2 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Gestrüpp
    MyIndex.Name = "WT_Shrubbery";
    MyIndex.Number = 3 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Grasland
    MyIndex.Name = "WT_Gras";
    MyIndex.Number = 4 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Wüste
    MyIndex.Name = "WT_Dessert";
    MyIndex.Number = 5 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Sumpf
    MyIndex.Name = "WT_Swamp";
    MyIndex.Number = 6 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Berge
    MyIndex.Name = "WT_Mountain";
    MyIndex.Number = 7 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Geröll
    MyIndex.Name = "WT_Boulders";
    MyIndex.Number = 8 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Lava
    MyIndex.Name = "WT_Lava";
    MyIndex.Number = 9 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Brücke horizontal
    MyIndex.Name = "WT_Bridge_horizontal";
    MyIndex.Number = 10 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Brücke vertikal
    MyIndex.Name = "WT_Bridge_vertical";
    MyIndex.Number = 11 * Tilewidth;
    MyData.addIndex(MyIndex);

    // Nebel des Krieges
    MyIndex.Name = "WT_Fog";
    MyIndex.Number = 12 * Tilewidth;
    MyData.addIndex(MyIndex);
/*
    -------------------------------------------------
*/

#ifdef DEBUG
    Log("Index for Datafile created.")
#endif // DEBUG

    Allegro_Output::gfx_Text renderText;
    Allegro_Output::gfx_Object renderTile;

    renderText.Foregroundcolor = MyData.findIndex("Col_yellow").Number;
    renderText.Backgroundcolor = MyData.findIndex("Col_black").Number;
    renderText.Pos_x = 10;
    renderText.Pos_y = Screenheight / 2;
    renderText.Text = "Loading ";
    renderText.Text = renderText.Text + Datafilename;
    renderText.Text = renderText.Text + ".";
    renderText.toConvert = false;

    MyOutput.writeOnScreen(&renderText);
    MyOutput.renderScreen();

#ifdef DEBUG
    Log(renderText.Text.c_str())
#endif // DEBUG

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Files loaded.")
#endif // DEBUG

    DATAFILE* Pictures = MyData.getDatafile();


    BITMAP *Frame = (BITMAP*) Pictures[MyData.findIndex("Sheet_Frame").Number].dat;
    BITMAP *Tiles = (BITMAP*) Pictures[MyData.findIndex("Sheet_Worldtiles").Number].dat;
    BITMAP *Hero = (BITMAP*) Pictures[MyData.findIndex("Sheet_Hero").Number].dat;
    BITMAP *Enemy = (BITMAP*) Pictures[MyData.findIndex("Sheet_Worldenemys").Number].dat;
    BITMAP *Town = (BITMAP*) Pictures[MyData.findIndex("Sheet_Towntiles").Number].dat;
    BITMAP *Logo = (BITMAP*) Pictures[MyData.findIndex("Sheet_Logo").Number].dat;

    font = (FONT*) Pictures[MyData.findIndex("Sheet_Font").Number].dat;
    MyOutput.setFont(font);

    MyOutput.clearScreen(true);

    // Set up the Logo
    renderTile.Sheet = Logo;
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

    renderText.Backgroundcolor = MyData.findIndex("Col_transparent").Number;
    renderText.Text = "Hit any Key to continue ....";
    MyOutput.renderObject(&renderTile);
    MyOutput.writeOnScreen(&renderText);
    MyOutput.renderScreen();

    MyInput.getKey();

    MyOutput.clearScreen(true);

    renderTile.Sheet = Tiles;
    renderTile.Sheetpos_x = MyData.findIndex("WT_Gras").Number;
    renderTile.Sheetpos_y = 0;
    renderTile.transparency = true;
    renderTile.Width = Tilewidth;
    renderTile.Height = Tileheight;


    for (int y = Playfield_y; y < Playfieldrows; ++y)
    {
        for(int x = Playfield_x; x < Playfieldcolumns; ++x)
        {
            renderTile.Destinationpos_x = x * Tilewidth;
            renderTile.Destinationpos_y = y * Tileheight;
            MyOutput.renderObject(&renderTile);

        } // for x

    } // for y

    renderTile.Sheet = Enemy;
    renderTile.Sheetpos_x = MyData.findIndex("WE_Skeleton").Number;
    renderTile.Destinationpos_x = 7 * Tilewidth;
    renderTile.Destinationpos_y = 4 * Tileheight;
    MyOutput.renderObject(&renderTile);

    renderTile.Sheetpos_x = MyData.findIndex("WE_Ghoul").Number;
    renderTile.Destinationpos_x = 6 * Tilewidth;
    MyOutput.renderObject(&renderTile);

    renderTile.Sheetpos_x = MyData.findIndex("WE_Zombie").Number;
    renderTile.Destinationpos_x = 5 * Tilewidth;
    MyOutput.renderObject(&renderTile);

    renderTile.Sheet = Hero;
    renderTile.Sheetpos_x = MyData.findIndex("HERO_Sword").Number;
    renderTile.Destinationpos_x = 6 * Tilewidth;
    renderTile.Destinationpos_y = 5 * Tileheight;
    MyOutput.renderObject(&renderTile);

    renderTile.Sheet = Town;
    renderTile.Sheetpos_x = MyData.findIndex("TWN_Mubrak").Number;
    renderTile.Destinationpos_x = 3 * Tilewidth;
    renderTile.Destinationpos_y = 2 * Tileheight;
    MyOutput.renderObject(&renderTile);

    renderTile.Sheet = Frame;
    renderTile.Sheetpos_x = 0;
    renderTile.Sheetpos_y = 0;
    renderTile.Destinationpos_x = 0;
    renderTile.Destinationpos_y = 0;
    renderTile.Width = MyOutput.getScreenWidth();
    renderTile.Height = MyOutput.getScreenHeight();
    MyOutput.renderObject(&renderTile);

    renderText.Foregroundcolor = MyData.findIndex("Col_purple").Number;
    renderText.Pos_x = Consoletext_x;
    renderText.Text = "15 Zeilen. Konsolentext äöü ÄÖÜ";
    renderText.toConvert = true;

    for(int Consoleline = 0; Consoleline < 15; ++Consoleline)
    {
        renderText.Pos_y = Consoletext_y + (Consoleline * Textheight);
        MyOutput.writeOnScreen(&renderText);

    } // for i

    renderText.Text = "30 Zeilen: Statustext.";
    renderText.Pos_x = Statustext_x;
    renderText.Foregroundcolor = MyData.findIndex("Col_gold").Number;

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

