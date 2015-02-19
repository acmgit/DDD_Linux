#include <iostream>
#include <allegro.h>
#include <string>

#include "include/Allegro_Input.h"

using namespace std;

void replace_all(string& text, const string& fnd, const string& rep);
string convertText(string Text);
void exit_on_error(const std::string &Errormessage);

int main()
{
    const int Screenwidth = 640;
    const int Screenheight = 480;
    const int Screendepth = 32;

    const int Tilewidth = 32;
    const int Tileheight = 32;
    const int WorldTilewidth = 416;
    const int HeroTilewidth = 288;
    const int EnemyTilewidth = 1248;
    const int TownTilewidth = 416;

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
        bmp_Enemy,
        bmp_TilesTown,
        bmp_TilesWorld
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

    set_color_depth(Screendepth);
    int screenError = set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, Screenwidth, Screenheight, 0, 0);
    if(screenError)
    {
        allegro_message(allegro_error);
        allegro_exit();

    } // if screenError

    const int DDD_red       = makecol(255,  50,    50);
    const int DDD_orange    = makecol(255,  100,    0);

    const int DDD_blue      = makecol(50,   50,   255);
    const int DDD_purple    = makecol(255,  50,   255);

    const int DDD_green     = makecol(50,   255,   50);
    const int DDD_cyan      = makecol(255,  255,   50);

    const int DDD_yellow    = makecol(255,  255,   50);
    const int DDD_gold      = makecol(255,  200,   50);
    const int DDD_brown     = makecol(200,  100,    0);

    const int DDD_white     = makecol(250,  250,  250);
    const int DDD_lightgrey = makecol(200,  200,  200);
    const int DDD_silver    = makecol(150,  150,  150);
    const int DDD_darkgrey  = makecol(100,  100,  100);

    Allegro_Input MyInput;

    BITMAP* VirtualScreen = create_bitmap(SCREEN_W, SCREEN_H);
    if(!VirtualScreen)
    {
        exit_on_error("Konnte keinen Speicher für Bildschrim reservieren.");

    } // if !VirtualScreen

    DATAFILE* Pictures = load_datafile(Datafilename.c_str());
    if(!Pictures)
    {
        std::string DataError = "Konnte Datei <%s> nicht laden.";
        replace_all(DataError, "%s", Datafilename);
        exit_on_error(DataError);
    } // if !Pictures

    BITMAP* Frame = create_bitmap(SCREEN_W, SCREEN_H);
    Frame = (BITMAP*) Pictures[bmp_Frame].dat;

    BITMAP* Tiles = create_bitmap(WorldTilewidth, Tileheight);
    Tiles = (BITMAP*) Pictures[bmp_TilesWorld].dat;

    BITMAP* Hero = create_bitmap(HeroTilewidth, Tileheight);
    Hero = (BITMAP*) Pictures[bmp_Hero].dat;

    BITMAP* Enemy = create_bitmap(EnemyTilewidth, Tileheight);
    Enemy = (BITMAP*) Pictures[bmp_Enemy].dat;

    BITMAP* Town = create_bitmap(TownTilewidth, Tileheight);
    Town = (BITMAP*) Pictures[bmp_TilesTown].dat;

    font = (FONT*) Pictures[fnt_Font].dat;

    clear_bitmap(VirtualScreen);

    for (int y = Playfield_y; y < Playfieldrows; ++y)
    {
        for(int x = Playfield_x; x < Playfieldcolumns; ++x)
        {
            blit(Tiles, VirtualScreen,  Gras, 0, x * Tilewidth, y * Tilewidth, Tilewidth, Tileheight);

        } // for x

    } // for y

    masked_blit(Enemy,  VirtualScreen, Skeleton,   0, 7 * Tilewidth,   4 * Tileheight, Tilewidth,  Tileheight);
    masked_blit(Enemy,  VirtualScreen, Ghoul,      0, 6 * Tilewidth,   4 * Tileheight, Tilewidth,  Tileheight);
    masked_blit(Enemy,  VirtualScreen, Zombie,     0, 5 * Tilewidth,   4 * Tileheight, Tilewidth,  Tileheight);
    masked_blit(Hero,   VirtualScreen, Sword,      0, 6 * Tilewidth,   5 * Tileheight, Tilewidth,  Tileheight);
    masked_blit(Town,   VirtualScreen, Druidshack, 0, 3 * Tilewidth,   2 * Tileheight, Tilewidth,  Tileheight);
    masked_blit(Frame,  VirtualScreen, 0,          0, 0,               0,              640,        480);

    for(int Consoleline = 0; Consoleline < 15; ++Consoleline)
    {
        textout_ex(VirtualScreen, font, convertText("15 Zeilen: Konsolentext.").c_str(), Consoletext_x, Consoletext_y + (Consoleline * Textheight),DDD_cyan, 0);

    } // for i

    string Text = "30 Zeilen: Statustext.";
    Text = convertText(Text);

    for(int Statusline = 0; Statusline < 30; ++Statusline)
    {
        textout_ex(VirtualScreen, font, Text.c_str(), Statustext_x, Statustext_y + (Statusline * Textheight), DDD_gold, 0);

    } // for i

    blit(VirtualScreen, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    do
    {
    }while(!MyInput.readKey());

    unload_datafile(Pictures);

    destroy_bitmap(VirtualScreen);

    return 0;
} // main
END_OF_MAIN()

void replace_all(std::string& text,const std::string& fnd,const std::string& rep)
{
  size_t pos = text.find(fnd);
  while(pos != std::string::npos)
  {
    text.replace(pos, fnd.length(), rep);
    pos = text.find(fnd, pos+rep.length());

  } // while(pos)
} // replace_all

std::string convertText(std::string Text)
{
    replace_all(Text, "ä", "{");
    replace_all(Text, "ö", "|");
    replace_all(Text, "ü", "}");
    replace_all(Text, "Ä", "<");
    replace_all(Text, "Ö", "=");
    replace_all(Text, "Ü", ">");

    return Text;
} // convertText

void exit_on_error(const std::string &Errormessage)
{
    allegro_message("%d - %s", *allegro_errno, Errormessage.c_str());
    allegro_exit();

} // exit_on_error
