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
        game();
        ~game();

        void init();
        void exit();
        void run();


    private:

        int get_Color(std::string ColText);

        void draw_Frame();                          // draws the global Frame of the Game
        void render_game();
        void clean_game();                           // deletes all valid Pointer

        std::string get_Command(int Len, int Seconds);

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

        // Herodata
        int Heropos_x;
        int Heropos_y;

}; // game

#endif // GAME_H
