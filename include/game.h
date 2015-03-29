#ifndef GAME_H
#define GAME_H

#include "Allegro_Input.h"
#include "Allegro_Output.h"
#include "Allegro_Datafile.h"
#include "UniText.h"
#include "Mapinterface.h"
#include "Clock.h"
#include "Hero.h"

#include <string>


class game
{
    public:


        enum Mode
        {
            Menu = 0,
            World,
            Battle,
            Town,
            Dungeon,
            Quit
        };

        game();
        ~game();

        void init();
        void exit();
        void run();


    private:

        void generate_Battlemap(const std::string &Typ);
        void draw_Battlemap();
        void delete_Battlemap();

        void draw_Worldmap(Hero::Hero_Position Pos);
        void draw_Frame();                          // draws the global Frame of the Game
        void write_Status();

        void render_game();
        void clean_game();                           // deletes all valid Pointer

        void build_Statusline(const int &Line, const int &Pixeltab,
                                     const std::string &Forgroundcolor,
                                     const std::string &Backgroundcolor,
                                     const std::string &Text,
                                     const int &Value, const int &Maxvalue);

        void build_Statusline(const int &Line, const int &Pixeltab,
                                     const std::string &Forgroundcolor,
                                     const std::string &Backgroundcolor,
                                     const std::string &Text,
                                     const int &Value);

        void switch_Mode(const int Gamemode);

        Hero::Order get_Command(int Len, int Seconds);
        void parse_Command(Hero::Order &Command);

        void execute_Command(Hero::Order &Command);

        Allegro_Output *DDD_Output;
        Allegro_Input *DDD_Input;
        Allegro_Datafile *DDD_Datafile;
        UniText *DDD_Translator;
        Mapinterface *DDD_Map;
        Hero *DDD_Hero;

        // Constants

        // Screen
        int Screen_width;
        int Screen_height;
        int Screen_depth;

        // Filenames
        std::string Datafile_name;
        std::string Indexfile_name;
        std::string Languagefile_name;
        std::string Initfile_name;

        // Gamedata
        Allegro_Output::gfx_Object global_Frame;
        bool running;

        int game_Mode;

        //Hero::Hero_Position Hero_Pos;

}; // game

#endif // GAME_H
