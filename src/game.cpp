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

    game_Mode = Menu;

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

    switch_Mode(World);

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
    Order Command;

    Command.Command = "";
    Command.Key.Alt = false;
    Command.Key.Key = ' ';
    Command.Key.Scancode = 0;
    Command.Key.Shift = 0;
    Command.Key.Strg = 0;

    Allegro_Output::tileData Hero;

    Hero.Sheet = DDD_Datafile->get_Bitmap("[SHE_Hero]");
    Hero.Sheetpos_x = DDD_Datafile->find_Index("[HER_Sword]").Number;
    Hero.Sheetpos_y = 0;
    Hero.transparency = true;
    Hero.Column = DDD_Datafile->find_Index("[INI_Playfieldcolumns]").Number / 2;
    Hero.Row = DDD_Datafile->find_Index("[INI_Playfieldrows]").Number / 2;

    //int counting = 0;

    while(running)
    {

        switch(game_Mode)
        {
            case Menu:
            {
                #ifdef DEBUG
                Log("(" << ErrorLog.ALLOK << ") Gamemode Menu")
                #endif // DEBUG
                break;

            } // case Menu

            case World:
            {
                #ifdef DEBUG
                Log("(" << ErrorLog.ALLOK << ") Gamemode Worldmap")
                #endif // DEBUG

                draw_Worldmap(Heropos_x, Heropos_y);
                DDD_Output->render_Tile(Hero);
                draw_Frame();

                Command = get_Command(1, 10);                   // 1 Char and 10 Seconds to wait ...
                parse_Command(Command);


                break;

            } // case World

            case Battle:
            {
                #ifdef DEBUG
                Log("(" << ErrorLog.ALLOK << ") Gamemode Battle")
                #endif // DEBUG

                draw_Battlemap();
                break;

            } // case Battle

            case Town:
            {
                #ifdef DEBUG
                Log("(" << ErrorLog.ALLOK << ") Gamemode Town")
                #endif // DEBUG

                break;

            } // case Town

            case Dungeon:
            {
                #ifdef DEBUG
                Log("(" << ErrorLog.ALLOK << ") Gamemode Dungeon")
                #endif // DEBUG

                break;

            } // case Dungeon

            case Quit:
            {
                #ifdef DEBUG
                Log("(" << ErrorLog.ALLOK << ") Gamemode Quit")
                #endif // DEBUG

                running = false;
                break;

            } // case Quit

            default:
            {
                #ifdef DEBUG
                Log("(" << ErrorLog.ALLOK << ") Gamemode Unknown")
                #endif // DEBUG

                break;

            } // case Unknown

        } // switch game_Mode

        //draw_Frame();
        render_game();

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

game::Order game::get_Command(int Len, int Seconds)
{
    std::string Command = "";
    int command_Count = 0;
    Keyboardinterface::Key currKey;

    DDD_Output->write_OnConsole(get_Color("yellow"), get_Color("transparent"), "", true);
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

        }
        else
        {
            command_Count = Len;
            DDD_Output->write_OnConsole(get_Color("brown"), get_Color("transparent"), DDD_Translator->Print("[Waiting]"), false);
            currKey.Alt = false;
            currKey.Key = ' ';
            currKey.Scancode = 0;
            currKey.Shift = false;
            currKey.Strg = false;
        } // if readKey

        /*
        if(command_Count >= Len)
        {
            DDD_Output->write_OnConsole(get_Color("yellow"), get_Color("transparent"), "", true);

        } // if command_Count
        */
        //render_game();
    } // while command_Count

    /*
    #ifdef DEBUG
    Log("Command: " << Command.c_str())
    #endif // DEBUG
    */
    Order currCommand;
    currCommand.Command = Command;
    currCommand.Key = currKey;

    return currCommand;
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

void game::switch_Mode(const int Gamemode)
{
    game_Mode = Gamemode;

} // switch_Mode

void game::parse_Command(Order &Command)
{
    switch(game_Mode)
    {
        case Menu:
        {
         break;

        } // case Menu

        case Battle:
        {
            break;

        } // case Battle

        case World:
        {
            execute_Worldcommand(Command);
            break;

        } // case World

        case Town:
        {
            break;

        } // case Town

        case Dungeon:
        {
            break;

        } // case Dungeon

        case Quit:
        {
            break;
        } // case Quit

        default:
        {
            #ifdef DEBUG
            Log("(" << ErrorLog.ILLEGAL_ACCESS << ") Unknown Command: " << Command.Command.c_str())
            #endif // DEBUG
            break;
        }

    } // switch game_Mode

} // parse_Command

void game::execute_Worldcommand(Order &Command)
{
    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Worldcommand: " << Command.Command.c_str())
    #endif // DEBUG

    switch(Command.Key.Scancode)
    {
        // North
        case 84:
        {
            /*
            #ifdef DEBUG
            Log("(" << ErrorLog.ALLOK << ") Go North.")
            #endif // DEBUG
            */
            DDD_Output->write_OnConsole(get_Color("gold"), get_Color("transparent"), DDD_Translator->Print("[North]"), true);
            --Heropos_y;
            DDD_Map->convert_WorldmapCoords(Heropos_x, Heropos_y);
            break;

        } // case N

        // South
        case 85:
        {
            DDD_Output->write_OnConsole(get_Color("gold"), get_Color("transparent"), DDD_Translator->Print("[South]"), true);
            ++Heropos_y;
            DDD_Map->convert_WorldmapCoords(Heropos_x, Heropos_y);
            break;

        } // case S

        // West
        case 82:
        {
            DDD_Output->write_OnConsole(get_Color("gold"), get_Color("transparent"), DDD_Translator->Print("[West]"), true);
            --Heropos_x;
            DDD_Map->convert_WorldmapCoords(Heropos_x, Heropos_y);
            break;

        } // case W

        // East
        case 83:
        {
            DDD_Output->write_OnConsole(get_Color("gold"), get_Color("transparent"), DDD_Translator->Print("[East]"), true);
            ++Heropos_x;
            DDD_Map->convert_WorldmapCoords(Heropos_x, Heropos_y);
            break;

        } // case W

        // case X
        case 24:
        {
            switch_Mode(Mode::Quit);
            break;

        }

        // no Key, only wait
        case 0:
        {
            break;

        } // case 0

        default:
        {
            /*
            #ifdef DEBUG
            Log("(" << ErrorLog.ALLOK << ") Unknown Command.")
            #endif // DEBUG
            */
            DDD_Output->write_OnConsole(get_Color("cyan"), get_Color("transparent"), DDD_Translator->Print("[Please]"), true);
            break;

        } // Command unknown

    } // switch(Command)

    //render_game();

} // execute_Worldcommand

#endif // GAME_CPP
