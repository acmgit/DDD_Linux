#ifndef GAME_H
#define GAME_H

#include "Allegro_Input.h"
#include "Allegro_Output.h"
#include "Allegro_Datafile.h"
#include "UniText.h"
#include "Mapinterface.h"
#include "Clock.h"

#include <string>


class game
{
    public:

        struct Order
        {
            std::string Command;
            Allegro_Input::Key Key;
        };

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

        int get_Color(std::string ColText);

        void generate_Battlemap(const std::string &Typ);
        void draw_Battlemap();
        void delete_Battlemap();

        void draw_Worldmap(const int &Pos_x, const int &Pos_y);
        void draw_Frame();                          // draws the global Frame of the Game
        void render_game();
        void clean_game();                           // deletes all valid Pointer

        void switch_Mode(const int Gamemode);

        Order get_Command(int Len, int Seconds);
        void parse_Command(Order &Command);

        void execute_Worldcommand(Order &Command);

        Allegro_Output *DDD_Output;
        Allegro_Input *DDD_Input;
        Allegro_Datafile *DDD_Datafile;
        UniText *DDD_Translator;
        Mapinterface *DDD_Map;

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

        // Herodata
        int Heropos_x;
        int Heropos_y;

}; // game

#endif // GAME_H
