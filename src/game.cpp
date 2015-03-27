#ifndef GAME_CPP
#define GAME_CPP

#include "game.h"

#ifdef DEBUG
#include "Logfile.h"
#endif // DEBUG


game::game()
{
    Screen_width = 640;
    Screen_height = 480;
    Screen_depth = 16;

    Datafile_name = "data/gfx.dat";
    Indexfile_name = "data/gfx.idx";
    Languagefile_name = "data/DDD_Language.txt";
    Initfile_name = "data/DDD_Ini.txt";

    // Opens the Screen with the Outputinterface
    Allegro_Output::screenData scr;
    scr.Fullscreen = false;
    scr.screenWidth = Screen_width;
    scr.screenHeight = Screen_height;
    scr.screenDepth = Screen_depth;

    DDD_Output = new Allegro_Output(scr);
    if(!DDD_Output)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Can't open Screen")
        #endif // DEBUG
        allegro_message("Cant't open Screen");
        allegro_exit();

    } // if !DDD_Output

    // Opens the Datafile
    DDD_Datafile = new Allegro_Datafile(Datafile_name, Indexfile_name, Initfile_name);
    if(!DDD_Datafile)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Can't open Datafile.")
        #endif // DEBUG
        allegro_message("Can't open Datafile");
        clean_game();
        allegro_exit();

    } // if !Datafile

    DDD_Input = new Allegro_Input();
    if(!DDD_Input)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Can't open Inputclass.")
        #endif // DEBUG
        allegro_message("Can't open Inputclass");
        clean_game();
        allegro_exit();

    } // if !DDD_Input

    DDD_Translator = new UniText(Languagefile_name);
    if(!DDD_Translator)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Can't open Translatorclass.")
        #endif // DEBUG
        allegro_message("Can't open Translatorclass");
        clean_game();
        allegro_exit();

    } // if !DDD_Translator

    DDD_Map = new Mapinterface(DDD_Datafile);
    if(!DDD_Map)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Can't open Mapclass.")
        #endif // DEBUG
        allegro_message("Can't open Mapclass");
        clean_game();
        allegro_exit();

    } // if !DDD_Map

    running = false;

    game_State = Menu;

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Gameclass opened.")
    #endif // DEBUG

} // game

game::~game()
{
    clean_game();

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Gameclass closed.")
    #endif // DEBUG

} // ~game

void game::render_game()
{
    DDD_Output->render_Screen();

} // render_game()

void game::init()
{
    // Set's the Frame
    global_Frame.Sheet = DDD_Datafile->get_Bitmap("[SHE_Frame]");
    global_Frame.Sheetpos_x = 0;
    global_Frame.Sheetpos_y = 0;
    global_Frame.Destinationpos_x = 0;
    global_Frame.Destinationpos_y = 0;
    global_Frame.Height = Screen_height;
    global_Frame.Width = Screen_width;
    global_Frame.transparency = true;

    // Init the Font
    DDD_Output->set_Font(DDD_Datafile->get_Font("[FNT_Game]"));

    // Init the Console
    DDD_Output->set_Console(    DDD_Datafile->find_Index("[INI_Consoletext_x]").Number,
                                DDD_Datafile->find_Index("[INI_Consoletext_y]").Number,
                                DDD_Datafile->find_Index("[INI_Textheight]").Number,
                                DDD_Datafile->find_Index("[INI_Consolerowsmax]").Number
                            );

    // Init the Statuswindows
    DDD_Output->set_Statuswindow(   DDD_Datafile->find_Index("[INI_Statustext_x]").Number,
                                    DDD_Datafile->find_Index("[INI_Statustext_y]").Number,
                                    DDD_Datafile->find_Index("[INI_Textheight]").Number,
                                    DDD_Datafile->find_Index("[INI_Statusrowsmax]").Number
                                 );

    // Init the Playfieldwindow
    DDD_Output->set_Playfieldwindow(    DDD_Datafile->find_Index("[INI_Playfield_x]").Number,
                                        DDD_Datafile->find_Index("[INI_Playfield_y]").Number,
                                        DDD_Datafile->find_Index("[INI_Worldtileswidth]").Number,
                                        DDD_Datafile->find_Index("[INI_Worldtilesheight]").Number,
                                        DDD_Datafile->find_Index("[INI_Playfieldcolumns]").Number,
                                        DDD_Datafile->find_Index("[INI_Playfieldrows]").Number
                                    );

    DDD_Output->clear_Screen(true);

    running = true;
    Heropos_x = 67;
    Heropos_y = 85;

    DDD_Map->generate_Battlemap("Gras");    // only to test the Battlemap

    switch_State(World);

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Game started.")
    #endif // DEBUG

} // init()

void game::exit()
{
    running = false;

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Game exited.")
    #endif // DEBUG

} // exit()

void game::run()
{
    std::string Command;
    int counting = 0;

    while(running)
    {
        switch(game_State)
        {
            case Menu:
            {
                #ifdef DEBUG
                Log("(" << ErrorLog.ALLOK << ") Gamestate Menu")
                #endif // DEBUG
                break;

            } // case Menu

            case World:
            {
                #ifdef DEBUG
                Log("(" << ErrorLog.ALLOK << ") Gamestate Worldmap")
                #endif // DEBUG

                draw_Worldmap(Heropos_x, Heropos_y);
                break;

            } // case World

            case Battle:
            {
                #ifdef DEBUG
                Log("(" << ErrorLog.ALLOK << ") Gamestate Battle")
                #endif // DEBUG

                draw_Battlemap();
                break;

            } // case Battle

            case Town:
            {
                #ifdef DEBUG
                Log("(" << ErrorLog.ALLOK << ") Gamestate Town")
                #endif // DEBUG

                break;

            } // case Town

            case Dungeon:
            {
                #ifdef DEBUG
                Log("(" << ErrorLog.ALLOK << ") Gamestate Dungeon")
                #endif // DEBUG

                break;

            } // case Dungeon

            default:
            {
                #ifdef DEBUG
                Log("(" << ErrorLog.ALLOK << ") Gamestate Unknown")
                #endif // DEBUG

                break;

            } // case Unknown

        } // switch game_State

        draw_Frame();
        render_game();

        Command = get_Command(1, 10);                   // 1 Char and 10 Seconds to wait ...
        ++counting;

        if(counting > 15)
        {
            running = false;

        } // if counting

    } // while running

    DDD_Map->destroy_Battlemap();

} // run

void game::clean_game()
{

    if(DDD_Map)
    {
        delete DDD_Map;
        DDD_Map = nullptr;

    } // if DDD_Map

    if(DDD_Translator)
    {
        delete DDD_Translator;
        DDD_Translator = nullptr;

    } // if DDD_Translator

    if(DDD_Input)
    {
        delete DDD_Input;
        DDD_Input = nullptr;

    } // if DDD_Input

    if(DDD_Datafile)
    {
        delete DDD_Datafile;
        DDD_Datafile = nullptr;

    } // if DDD_Datafile

    if(DDD_Output)
    {
        delete DDD_Output;
        DDD_Output = nullptr;

    } // if DDD_Output

}

void game::draw_Frame()
{
    DDD_Output->render_Object(&global_Frame);

} // draw_Frame

int game::get_Color(std::string Text)
{
    int Color = DDD_Datafile->find_Index("[COL_" + Text + "]").Number;
    return Color;

} // get_Color

std::string game::get_Command(int Len, int Seconds)
{
    std::string Command = "";
    int command_Count = 0;
    Keyboardinterface::Key currKey;

    DDD_Output->write_OnConsole(get_Color("yellow"), get_Color("transparent"), "#", false);
    render_game();

    while(command_Count < Len)
    {
        if(DDD_Input->read_Key(Seconds))
        {
            currKey = DDD_Input->get_Key();
            Command.append(1, currKey.Key);
            ++command_Count;
            DDD_Output->write_OnConsole(get_Color("yellow"), get_Color("transparent"), "#" + Command, false);
            //DDD_Input->flush_Keyboard();

        }
        else
        {
            command_Count = Len;
            DDD_Output->write_OnConsole(get_Color("orange"), get_Color("transparent"), DDD_Translator->Print("[Waiting]"), true);

        } // if readKey

        if(command_Count >= Len)
        {
            DDD_Output->write_OnConsole(get_Color("yellow"), get_Color("transparent"), "", true);

        } // if command_Count

        render_game();
    } // while command_Count

    #ifdef DEBUG
    Log("Command: " << Command.c_str())
    #endif // DEBUG

    return Command;
} // get_Command

void game::draw_Worldmap(const int &Pos_x, const int &Pos_y)
{
    // Calculate and convert the Tile on the Worldmap
    int world_x = Pos_x - (DDD_Datafile->find_Index("[INI_Playfieldcolumns]").Number / 2);
    int world_y = Pos_y - (DDD_Datafile->find_Index("[INI_Playfieldrows]").Number / 2);
    //DDD_Map->convert_WorldmapCoords(world_x, world_y);

    // Set's constant Data for Output
    Allegro_Output::tileData Tile;
    Tile.Sheetpos_y = 0;
    Tile.transparency = false;

    // Worldmaptile
    Mapinterface::Tiledata currTile;

    // Calculatecounter
    int draw_x = 0;
    int draw_y = 0;

    for(int Tile_Row = 0; Tile_Row < DDD_Datafile->find_Index("[INI_Playfieldrows]").Number; ++Tile_Row)
    {
        for(int Tile_Column = 0; Tile_Column < DDD_Datafile->find_Index("[INI_Playfieldcolumns]").Number; ++Tile_Column)
        {
            // Calculate and convert new Tile on the Worldmap
            draw_x = world_x + Tile_Column;
            draw_y = world_y + Tile_Row;
            //DDD_Map->convert_WorldmapCoords(draw_x, draw_y);

            // draw now the Tile on the Playfieldscreen
            currTile = DDD_Map->get_Tile(Mapinterface::Worldmaptile, draw_x, draw_y);
            Tile.Sheet = currTile.Sheet;
            Tile.Sheetpos_x = currTile.Index;
            Tile.Column = Tile_Column;
            Tile.Row = Tile_Row;
            DDD_Output->render_Tile(Tile);

        } // for Column

    } // for Row

} // draw_Worldmap

void game::draw_Battlemap()
{

    Allegro_Output::tileData Tile;
    Tile.Sheetpos_y = 0;
    Tile.transparency = false;

    Mapinterface::Tiledata currTile;

    // Draw the Battlemap
    for(int Tile_Row = 0; Tile_Row < DDD_Datafile->find_Index("[INI_Playfieldrows]").Number; ++Tile_Row)
    {
        for(int Tile_Column = 0; Tile_Column < DDD_Datafile->find_Index("[INI_Playfieldcolumns]").Number; ++Tile_Column)
        {
            currTile = DDD_Map->get_Tile(Mapinterface::Battlemaptile, Tile_Column, Tile_Row);
            Tile.Sheet = currTile.Sheet;
            Tile.Sheetpos_x = currTile.Index;
            Tile.Column = Tile_Column;
            Tile.Row = Tile_Row;
            DDD_Output->render_Tile(Tile);

        } // for Column

    } // for Row

} // draw_Battlemap

void game::generate_Battlemap(const std::string &Typ)
{
    DDD_Map->generate_Battlemap(Typ);

} // generate_Battlemap

void game::delete_Battlemap()
{
    DDD_Map->destroy_Battlemap();

} // delete_Battlemap

void game::switch_State(const int Gamestate)
{
    game_State = Gamestate;
}
#endif // GAME_CPP
