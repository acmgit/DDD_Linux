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

    DDD_Hero = new Hero(DDD_Datafile, DDD_Output, DDD_Map, DDD_Translator, "Tethis", true);
    if(!DDD_Hero)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Can't open Heroclass.")
        #endif // DEBUG
        allegro_message("Can't open Heroclass");
        clean_game();
        allegro_exit();

    } // if !DDD_Hero

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

    //DDD_Map->generate_Battlemap("Gras");    // only to test the Battlemap

    switch_Mode(World);

    DDD_Hero->set_Value(Hero::Hero_Poisonfactor, 2, false);
    //DDD_Hero->set_Value(Hero::Stats::Hero_Cheater, 1, false);

    //DDD_Output->play_Music("mus/zero-project - Moonlight requiem.ogg", 0.2f);
    DDD_Output->play_Musickey("Worldmap", 0.2f);

    //DDD_Hero = get_Position(Hero_Pos);

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") ---===< Game started. >===--- ")
    #endif // DEBUG

} // init()

void game::exit()
{
    running = false;

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") ---===< Game exited. >===--- ")
    #endif // DEBUG

} // exit()

void game::run()
{
    Hero::Order Command;

    Command.Command = "";
    Command.Key.Alt = false;
    Command.Key.Key = ' ';
    Command.Key.Scancode = 0;
    Command.Key.Shift = 0;
    Command.Key.Strg = 0;

/*
    Allegro_Output::tileData Hero;

    Hero.Sheet = DDD_Datafile->get_Bitmap("[SHE_Hero]");
    Hero.Sheetpos_x = DDD_Datafile->find_Index("[HER_Sword]").Number;
    Hero.Sheetpos_y = 0;
    Hero.transparency = true;
    Hero.Column = DDD_Datafile->find_Index("[INI_Playfieldcolumns]").Number / 2;
    Hero.Row = DDD_Datafile->find_Index("[INI_Playfieldrows]").Number / 2;
*/
    //int counting = 0;

    while(running)
    {

        write_Status();
        draw_Worldmap(DDD_Hero->get_Position());

        DDD_Hero->draw_Hero(DDD_Datafile->find_Index("[INI_Playfieldcolumns]").Number / 2,
                            DDD_Datafile->find_Index("[INI_Playfieldrows]").Number / 2);

        if(!DDD_Hero->get_Status(Hero::Hero_is_Cheating))
        {
            draw_World_Fog();

        } // if(is_Cheating)

        draw_Frame();

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

} // run

void game::clean_game()
{

    DDD_Map->destroy_Battlemap();

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

Hero::Order game::get_Command(int Len, int Seconds)
{
    std::string Command = "";
    int command_Count = 0;
    Keyboardinterface::Key currKey;

    DDD_Output->write_OnConsole(DDD_Datafile->get_Color("yellow"), DDD_Datafile->get_Color("transparent"), "", true);
    DDD_Output->write_OnConsole(DDD_Datafile->get_Color("yellow"), DDD_Datafile->get_Color("transparent"), "#", false);
    render_game();

    while(command_Count < Len)
    {
        if(DDD_Input->read_Key(Seconds))
        {
            currKey = DDD_Input->get_Key();
            Command.append(1, currKey.Key);
            ++command_Count;
            DDD_Output->write_OnConsole(DDD_Datafile->get_Color("yellow"), DDD_Datafile->get_Color("transparent"), "#" + Command, false);

        }
        else
        {
            command_Count = Len;
            DDD_Output->write_OnConsole(DDD_Datafile->get_Color("brown"), DDD_Datafile->get_Color("transparent"), DDD_Translator->Print("[Waiting]"), false);
            currKey.Alt = false;
            currKey.Key = ' ';
            currKey.Scancode = 0;
            currKey.Shift = false;
            currKey.Strg = false;
        } // if readKey

    } // while command_Count

    Hero::Order currCommand;
    currCommand.Command = Command;
    currCommand.Key = currKey;

    return currCommand;
} // get_Command

void game::draw_Worldmap(Hero::Hero_Position Pos)
{
    // Calculate and convert the Tile on the Worldmap
    int world_x = Pos.Global_x - (DDD_Datafile->find_Index("[INI_Playfieldcolumns]").Number / 2);
    int world_y = Pos.Global_y - (DDD_Datafile->find_Index("[INI_Playfieldrows]").Number / 2);
    //DDD_Map->convert_WorldmapCoords(world_x, world_y);

    // Set's constant Data for Output
    Allegro_Output::tileData Tile;
    Tile.Sheetpos_y = 0;
    Tile.transparency = false;

    Allegro_Output::tileData Towntile;
    Towntile.Sheetpos_y = 0;
    Towntile.transparency = true;

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

            std::string Town;
            Town = DDD_Map->check_Town(world_x + Tile_Column, world_y + Tile_Row);

            if(Town.size() > 0)
            {
                currTile = DDD_Map->get_Tile(Mapinterface::Townmaptile, world_x + Tile_Column, world_y + Tile_Row);
                Towntile.Sheet =  currTile.Sheet;
                Towntile.Sheetpos_x = currTile.Index;
                Towntile.Column = Tile_Column;
                Towntile.Row = Tile_Row;
                DDD_Output->render_Tile(Towntile);

            } // if Town.size

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
    int Heromode;

    switch(Gamemode)
    {
        case World:
        {
            Heromode = Hero::Hero_on_Worldmap;
            break;

        } // case World

        case Town:
        {
            Heromode = Hero::Hero_on_Townmap;
            break;

        } // case Town

        case Battle:
        {
            Heromode = Hero::Hero_on_Battlemap;
            break;

        } // case Battle

        case Dungeon:
        {
            Heromode = Hero::Hero_on_Dungeonmap;
            break;

        } // case World

        default:
        {
            Heromode = Hero::Hero_on_Worldmap;
            break;

        } // Unknown

    } // switch Gamemode

    DDD_Hero->set_Value(Hero::Hero_Map, Heromode, false);

} // switch_Mode

void game::parse_Command(Hero::Order &Command)
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
            execute_Command(Command);
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

void game::execute_Command(Hero::Order &Command)
{
    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Worldcommand: " << Command.Command.c_str())
    #endif // DEBUG

    switch(Command.Key.Scancode)
    {

        // case *
        case 87:
        {
            DDD_Output->pause_Music();
            DDD_Output->write_OnConsole(DDD_Datafile->get_Color("darkgrey"), DDD_Datafile->get_Color("transparent"), DDD_Translator->Print("[Music_pause]"),true);
            break;

        }

        // case /
        case 86:
        {
            DDD_Output->play_Music();
            DDD_Output->write_OnConsole(DDD_Datafile->get_Color("darkgrey"), DDD_Datafile->get_Color("transparent"), DDD_Translator->Print("[Music_play]"),true);
            break;

        }

        // case -
        case 88:
        {
            DDD_Output->change_Volume(.1f, false);
            DDD_Output->write_OnConsole(DDD_Datafile->get_Color("darkgrey"), DDD_Datafile->get_Color("transparent"), DDD_Translator->Print("[Sound_decrement]"),true);
            break;

        }

        // case +
        case 89:
        {
            DDD_Output->change_Volume(.1f, true);
            DDD_Output->write_OnConsole(DDD_Datafile->get_Color("darkgrey"), DDD_Datafile->get_Color("transparent"), DDD_Translator->Print("[Sound_increment]"),true);
            break;

        }

        // case X
        case 24:
        {
            switch_Mode(Mode::Quit);
            break;

        }

        // case s
        case 19:
        {
            std::string result = DDD_Translator->Print("[Found]");

            DDD_Output->play_Sound("Search");
            DDD_Output->write_OnConsole(DDD_Datafile->get_Color("gold"), DDD_Datafile->get_Color("transparent"), DDD_Translator->Print("[Searching]"), true);

            for(int i = 1; i < 5; ++i)
            {
                DDD_Output->write_OnConsole(DDD_Datafile->get_Color("gold"), DDD_Datafile->get_Color("transparent"), ".", true);
                DDD_Input->set_Seconds(1);
                while(!DDD_Input->wait())
                {
                    render_game();
                } // while(wait)

            } // for i

            result = result + DDD_Hero->find_Treasure();
            DDD_Output->write_OnConsole(DDD_Datafile->get_Color("gold"), DDD_Datafile->get_Color("transparent"), result, true);
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
            DDD_Hero->execute_Command(Command);

            //DDD_Output->write_OnConsole(get_Color("cyan"), get_Color("transparent"), DDD_Translator->Print("[Please]"), true);
            break;

        } // Command unknown

    } // switch(Command)

} // execute_Worldcommand

void game::write_Status()
{

    int startline = 1;
    int pixeltab = 120;
    int linecount = 0;

    // Name + Gender
    std::string Line = DDD_Hero->get_Name();
    DDD_Output->add_StatusLine(startline + linecount, 0, DDD_Datafile->get_Color("white"), DDD_Datafile->get_Color("transparent"), Line);

    if(DDD_Hero->get_Status(Hero::Hero_is_Female))
    {
        Line = DDD_Translator->Print("[Female]");

    }
    else
    {
        Line = DDD_Translator->Print("[Male]");

    } // if is_Female
    DDD_Output->add_StatusLine(startline + linecount, pixeltab, DDD_Datafile->get_Color("red"), DDD_Datafile->get_Color("transparent"), Line);

    // Experience and Level
    ++linecount;
    ++linecount;
    build_Statusline(startline + linecount, 0, "silver", "transparent", "[STA_Experience]", Hero::Hero_Experience, Hero::Hero_Experience_to_next_Level);
    ++linecount;
    build_Statusline(startline + linecount, 0, "lightgrey", "transparent", "[STA_Level]", Hero::Hero_Level);

    // Lifepoints
    ++linecount;
    ++linecount;
    build_Statusline(startline + linecount, 0, "green", "transparent", "[STA_Live]", Hero::Hero_Live, Hero::Hero_Live_max);

    // Manapoints
    ++linecount;
    build_Statusline(startline + linecount, 0, "cyan", "transparent", "[STA_Mana]", Hero::Hero_Mana, Hero::Hero_Mana_max);

    // Attack and Parade
    ++linecount;
    ++linecount;
    build_Statusline(startline + linecount, 0, "brown", "transparent", "[STA_Attack]", Hero::Hero_Attack);
    build_Statusline(startline + linecount, pixeltab, "orange", "transparent", "[STA_Parade]", Hero::Hero_Parade);

    // Strength & Dexterity
    ++linecount;
    build_Statusline(startline + linecount, 0, "yellow", "transparent", "[STA_Strength]", Hero::Hero_Strength);
    build_Statusline(startline + linecount, pixeltab, "brown", "transparent", "[STA_Dexterity]", Hero::Hero_Dexterity);

    // Wisdom & Charisma
    ++linecount;
    build_Statusline(startline + linecount, 0, "cyan", "transparent", "[STA_Wisdom]", Hero::Hero_Wisdom);
    build_Statusline(startline + linecount, pixeltab, "blue", "transparent", "[STA_Charisma]", Hero::Hero_Wisdom);

    // Gold & Food & Poisoned with Factor
    ++linecount;
    ++linecount;
    build_Statusline(startline + linecount, 0, "gold", "transparent", "[STA_Gold]", Hero::Hero_Gold);
    build_Statusline(startline + linecount, pixeltab, "purple", "transparent", "[STA_Food]", Hero::Hero_Food);
    if(DDD_Hero->get_Value(Hero::Hero_Poisonfactor) > 0)
    {
        ++linecount;
        build_Statusline(startline + linecount, 0, "green", "transparent", "[STA_Poison]", Hero::Hero_Poisonfactor);
    }

    // Cheater
    if(DDD_Hero->get_Status(Hero::Hero_is_Cheating))
    {
        ++linecount;
        ++linecount;
        build_Cheaterline(startline + linecount, 0, "white", "transparent", "CHEATERSTATUS [");
    }
    // Statusline
    DDD_Output->write_Status();

} // write_Status

void game::build_Statusline(    const int &Line, const int &Pixeltab,
                                const std::string &Forgroundcolor,
                                const std::string &Backgroundcolor,
                                const std::string &Text,
                                const int &Value, const int &Maxvalue)
{
    int currVal = DDD_Hero->get_Value(Value);
    int currValMax = DDD_Hero->get_Value(Maxvalue);
    std::string StatusLine = DDD_Translator->Print(Text) + " " + DDD_Datafile->valtostr(currVal) + " (" + DDD_Datafile->valtostr(currValMax) + ")";
    DDD_Output->add_StatusLine(Line, Pixeltab, DDD_Datafile->get_Color(Forgroundcolor), DDD_Datafile->get_Color(Backgroundcolor), StatusLine);

} // build_Statusline

void game::build_Statusline(    const int &Line, const int &Pixeltab,
                                const std::string &Forgroundcolor,
                                const std::string &Backgroundcolor,
                                const std::string &Text,
                                const int &Value)
{
    int currVal = DDD_Hero->get_Value(Value);
    std::string StatusLine = DDD_Translator->Print(Text) + " " + DDD_Datafile->valtostr(currVal);
    DDD_Output->add_StatusLine(Line, Pixeltab, DDD_Datafile->get_Color(Forgroundcolor), DDD_Datafile->get_Color(Backgroundcolor), StatusLine);

} // build_Statusline

void game::build_Cheaterline(   const int &Line, const int &Pixeltab,
                                const std::string &Forgroundcolor,
                                const std::string &Backgroundcolor,
                                const std::string &Text)
{
    std::string StatusLine = Text + "true]";
    DDD_Output->add_StatusLine(Line, Pixeltab, DDD_Datafile->get_Color(Forgroundcolor), DDD_Datafile->get_Color(Backgroundcolor), StatusLine);

} // build_Statusline

void game::draw_World_Fog()
{
    std::vector<std::string> Playline;

    // copy the Map to a local Map
    int Play_x = DDD_Hero->get_Position().Global_x;
    int Play_y = DDD_Hero->get_Position().Global_y;

    int start_x = Play_x - (DDD_Datafile->find_Index("[INI_Playfieldcolumns]").Number / 2);
    int start_y = Play_y - (DDD_Datafile->find_Index("[INI_Playfieldrows]").Number / 2);
    DDD_Map->convert_WorldmapCoords(start_x, start_y);

    int end_x = start_x + (DDD_Datafile->find_Index("[INI_Playfieldcolumns]").Number);
    int end_y = start_y + (DDD_Datafile->find_Index("[INI_Playfieldrows]").Number);
    DDD_Map->convert_WorldmapCoords(end_x, end_y);

    for(int y = 0; y <= DDD_Datafile->find_Index("[INI_Playfieldrows]").Number; ++y)
    {
        std::string Line;

        for(int x = 0; x <= DDD_Datafile->find_Index("[INI_Playfieldcolumns]").Number; ++x)
        {
            Line += DDD_Map->get_Tilecheck(Mapinterface::Worldmaptile, start_x + x, start_y + y).Rawtile;

        } // for int x

        Playline.push_back(Line);
        Line.clear();

    } // for int y

    // ok, now draw the Fog-Lines
    start_x = DDD_Datafile->find_Index("[INI_Playfieldcolumns]").Number / 2;
    start_y = DDD_Datafile->find_Index("[INI_Playfieldrows]").Number / 2;

    end_x = DDD_Datafile->find_Index("[INI_Playfieldcolumns]").Number;
    end_y = DDD_Datafile->find_Index("[INI_Playfieldrows]").Number;

    for(int x = 0; x <= end_x; ++x)
    {
        check_Line(Playline, start_x, start_y, x, 0);
        check_Line(Playline, start_x, start_y, x, end_y);

    }

    for(int y = 0; y <= end_y; ++y)
    {
        check_Line(Playline, start_x, start_y, 0, y);
        check_Line(Playline, start_x, start_y, end_x, y);
    }

} // draw_Fog()


void game::check_Line(std::vector<std::string> &Map, int start_x, int start_y, int end_x, int end_y)
{
    Allegro_Output::tileData Fogtile;

    Fogtile.Sheet = DDD_Datafile->get_Bitmap("[SHE_Worldtile]");
    Fogtile.Sheetpos_x = DDD_Datafile->find_Index("[WTI_Fog]").Number;
    Fogtile.Sheetpos_y = 0;
    Fogtile.transparency = false;

    bool draw = false;

    //void line(int x0, int y0, int x1, int y1)

    int dx =  abs(end_x - start_x), sx = start_x < end_x ? 1 : -1;
    int dy = -abs(end_y - start_y), sy = start_y < end_y ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    while(true)
    {  /* loop */
        //setPixel( start_x, start_y );

        if(!draw)
        {
            bool shadow = DDD_Map->convert_Rawtile(Map.at(start_y).at(start_x)).eclipse;
            if(shadow)
            {
                draw = true;

            } // if (shadow)

        }
        else
        {
            Fogtile.Column = start_x;
            Fogtile.Row = start_y;
            if( (Fogtile.Column >= 0) && (Fogtile.Column <= (DDD_Datafile->find_Index("[INI_Playfieldcolumns]").Number-1)) &&
                (Fogtile.Row >= 0) && (Fogtile.Row <= (DDD_Datafile->find_Index("[INI_Playfieldrows]").Number-1))
              )
            {
                DDD_Output->render_Tile(Fogtile);

            } // if(Fogtile)

        } // if(!draw)

        if (start_x == end_x && start_y == end_y)
        {
            break;

        }

        e2 = 2*err;
        if (e2 > dy)
        {
            err += dy;
            start_x += sx;

        } /* e_xy+e_x > 0 */

        if (e2 < dx)
        {
            err += dx;
            start_y += sy;

        } /* e_xy+e_y < 0 */

    } // while(true)

} // check_line

#endif // GAME_CPP
