#include <iostream>
#include <allegro.h>
#include <string>

#include "include/Allegro_Input.h"
#include "include/Allegro_Output.h"

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
    const int Screendepth = 32;

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

    enum Datafileindex
    {
        fnt_Font = 0,
        bmp_Frame,
        bmp_Hero,
        bmp_Logo,
        bmp_TilesTown,
        bmp_TilesWorld,
        bmp_Enemy
    }; // Datafileindex

    enum Worldtile
    {
        Sea                 = 0,                    // Meer
        River               = Tilewidth,            // Fluss, seichtes Meer
        Forest              = 2 * Tilewidth,        // Wald
        Shrubbery           = 3 * Tilewidth,        // Gestrüpp
        Gras                = 4 * Tilewidth,        // Grasland
        Dessert             = 5 * Tilewidth,        // Wüste
        Swamp               = 6 * Tilewidth,        // Sumpf
        Mountain            = 7 * Tilewidth,        // Berge
        Boulders            = 8 * Tilewidth,        // Geröll
        Lava                = 9 * Tilewidth,        // Lava
        Bridge_horizontal   = 10 * Tilewidth,       // Brücke horizontal
        Bridge_vertical     = 11 * Tilewidth,       // Brücke vertikal
        Fog                 = 12 * Tilewidth        // Nebel des Krieges
    }; // Worldtile

    enum Herotile
    {
        Sword           = 0,                        // Held nur mit Einhandwaffe
        Shield          = Tilewidth,                // Held mit Einhandwaffe und Schild
        Sword_poisoned  = 2 * Tilewidth,            // Held nur mit Einhandwaffe (vergiftet)
        Shield_poisoned = 3 * Tilewidth,            // Held mit Einhandwaffe und Schild (vergiftet)
        Horse           = 4 * Tilewidth,            // Held auf Pferd
        Unicorn         = 5 * Tilewidth,            // Held auf Einhorn
        Ship            = 6 * Tilewidth,            // Held auf Schiff
        Dragon          = 7 * Tilewidth,            // Held auf Feuerechse
        Dead            = 8 * Tilewidth             // Held tot
    }; // Herotile

    enum Enemytile
    {
        Goblin              = 0,                    // Goblin
        Zombie              = Tilewidth,            // Zombie
        Bandit              = 2 * Tilewidth,        // Räuber
        Aquarius            = 3 * Tilewidth,        // Wassermann
        Sandviper           = 4 * Tilewidth,        // Sandviper
        Orc                 = 5 * Tilewidth,        // Ork
        Skeleton            = 6 * Tilewidth,        // Skelett
        Pirate              = 7 * Tilewidth,        // Pirat
        Hackberry           = 8 * Tilewidth,        // Nesselbaum
        Wildhorse           = 9 * Tilewidth,        // Wildpferd
        Seahorse            = 10 * Tilewidth,       // Seepferd
        Ghoul               = 11 * Tilewidth,       // Ghul
        Forestdemon         = 12 * Tilewidth,       // Waldschrat
        Wildunicorn         = 13 * Tilewidth,       // Einhorn
        Ogre                = 14 * Tilewidth,       // Oger
        Aurochs             = 15 * Tilewidth,       // Auerochse
        Vampire             = 16 * Tilewidth,       // Vampir
        Troll               = 17 * Tilewidth,       // Troll (Brückentroll)
        Seaserpent          = 18 * Tilewidth,       // Seeschlange
        Giantpython         = 19 * Tilewidth,       // Riesenpython
        Werewolf            = 20 * Tilewidth,       // Werwolf
        Raftspider          = 21 * Tilewidth,       // Höhlenspinne
        Mummy               = 22 * Tilewidth,       // Mumie
        Giantoktopus        = 23 * Tilewidth,       // Riesenkrake
        Cavedemon           = 24 * Tilewidth,       // Höhlenschrat
        Firelizard          = 25 * Tilewidth,       // Feuerechse
        Doublehead          = 26 * Tilewidth,       // Zweihaupt
        Wizard              = 27 * Tilewidth,       // Zauberer
        Demon               = 28 * Tilewidth,       // Dämon
        Spittingcobra       = 29 * Tilewidth,       // Speihkobra
        Scaffoldwebspider   = 30 * Tilewidth,       // Höhlenspinne
        Giantape            = 31 * Tilewidth,       // Riesenaffe
        Youngdragon         = 32 * Tilewidth,       // Jungdrache
        Cyclops             = 33 * Tilewidth,       // Zyklop
        Balrog              = 34 * Tilewidth,       // Balrog
        Hydra               = 35 * Tilewidth,       // Hydra
        Giant               = 36 * Tilewidth,       // Riese
        Wilddragon          = 37 * Tilewidth,       // Drache
        Deadenemy           = 38 * Tilewidth        // Totes Monster
    }; // Enemyavatar

    enum Towntile
    {
        Secretcave      = 0,
        Druidshack      = Tilewidth,
        Ackbah          = 2 * Tilewidth,
        Worthal         = 3 * Tilewidth,
        Trisdisk        = 4 * Tilewidth,
        Gaht            = 5 * Tilewidth,
        Mubrak          = 6 * Tilewidth,
        Muspel          = 7 * Tilewidth,
        Madraskan       = 8 * Tilewidth,
        Royalpalace     = 9 * Tilewidth,
        Blacktower      = 10 * Tilewidth,
        Whitetower      = 11 * Tilewidth,
        Fulgarpalace    = 12 * Tilewidth,
        Dragoncave      = 13 * Tilewidth,
        Swampdungeon    = 14 * Tilewidth,
        Crystaldungeon  = 15 * Tilewidth
    }; // Towntile

    allegro_init();

    Allegro_Output MyOutput(Screenwidth, Screenheight, Screendepth, false);
    Allegro_Input MyInput;

    const int DDD_red           = makecol(255,  50,    50);
    const int DDD_orange        = makecol(255,  100,    0);

    const int DDD_blue          = makecol(50,   50,   255);
    const int DDD_purple        = makecol(255,  50,   255);

    const int DDD_green         = makecol(50,   255,   50);
    const int DDD_cyan          = makecol(50,   255,  255);

    const int DDD_yellow        = makecol(255,  255,   50);
    const int DDD_gold          = makecol(255,  200,   50);
    const int DDD_brown         = makecol(200,  100,    0);

    const int DDD_white         = makecol(250,  250,  250);
    const int DDD_lightgrey     = makecol(200,  200,  200);
    const int DDD_silver        = makecol(150,  150,  150);
    const int DDD_darkgrey      = makecol(100,  100,  100);
    const int DDD_black         = makecol(  0,    0,    0);
    const int DDD_transparent   = -1;

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Programmstart.")
#endif // DEBUG

    Allegro_Output::gfx_Text renderText;
    Allegro_Output::gfx_Object renderTile;

    renderText.Foregroundcolor = DDD_white;
    renderText.Backgroundcolor = DDD_black;
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

    DATAFILE* Pictures = load_datafile(Datafilename.c_str());
    if(!Pictures)
    {
        std::string DataError = "Konnte Datei ";
        DataError = DataError + Datafilename + " nicht laden.";

#ifdef DEBUG
        Log("(" << ErrorLog.FILE_NOT_FOUND << ") " << DataError.c_str())
#endif // DEBUG

        exit_on_error(DataError);
    } // if !Pictures

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Files loaded.")
#endif // DEBUG

    BITMAP *Frame = (BITMAP*) Pictures[bmp_Frame].dat;
    BITMAP *Tiles = (BITMAP*) Pictures[bmp_TilesWorld].dat;
    BITMAP *Hero = (BITMAP*) Pictures[bmp_Hero].dat;
    BITMAP *Enemy = (BITMAP*) Pictures[bmp_Enemy].dat;
    BITMAP *Town = (BITMAP*) Pictures[bmp_TilesTown].dat;
    BITMAP *Logo = (BITMAP*) Pictures[bmp_Logo].dat;

    font = (FONT*) Pictures[fnt_Font].dat;
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

    renderText.Backgroundcolor = DDD_transparent;
    renderText.Text = "Hit any Key to continue ....";
    MyOutput.renderObject(&renderTile);
    MyOutput.writeOnScreen(&renderText);
    MyOutput.renderScreen();

    MyInput.getKey();

    MyOutput.clearScreen(true);

    renderTile.Sheet = Tiles;
    renderTile.Sheetpos_x = Shrubbery;
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
    renderTile.Sheetpos_x = Skeleton;
    renderTile.Destinationpos_x = 7 * Tilewidth;
    renderTile.Destinationpos_y = 4 * Tileheight;
    MyOutput.renderObject(&renderTile);

    renderTile.Sheetpos_x = Ghoul;
    renderTile.Destinationpos_x = 6 * Tilewidth;
    MyOutput.renderObject(&renderTile);

    renderTile.Sheetpos_x = Zombie;
    renderTile.Destinationpos_x = 5 * Tilewidth;
    MyOutput.renderObject(&renderTile);

    renderTile.Sheet = Hero;
    renderTile.Sheetpos_x = Sword;
    renderTile.Destinationpos_x = 6 * Tilewidth;
    renderTile.Destinationpos_y = 5 * Tileheight;
    MyOutput.renderObject(&renderTile);

    renderTile.Sheet = Town;
    renderTile.Sheetpos_x = Druidshack;
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

    renderText.Foregroundcolor = DDD_cyan;
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
    renderText.Foregroundcolor = DDD_gold;

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

    unload_datafile(Pictures);

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

