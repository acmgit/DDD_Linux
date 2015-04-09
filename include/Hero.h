#ifndef HERO_H
#define HERO_H

#include <string>

#include "Allegro_Datafile.h"
#include "Allegro_Output.h"
#include "Mapinterface.h"
#include "Allegro_Input.h"
#include "UniText.h"

class Hero
{

        public:

        struct Hero_Status
        {
            // Int-Values
            int Live;
            int Maximal_Live;
            int Mana;
            int Maximal_Mana;

            int Level;
            int Experience;
            int Experience_to_next_Level;

            int Strength;
            int Dexterity;
            int Wisdom;
            int Charisma;

            int Attack;
            int Parade;

            int Gold;
            int Food;
            int Poisonfactor;

            int on_Map;
            int on_Vehicle;
            int has_Shield;
            int handle_Weapon;

            // Bool-Values
            bool is_Female;

            bool is_Riding;
            bool is_Flying;

            bool is_Cheating;

        }; // Hero_Status

        enum Stats
        {
            Hero_Live,
            Hero_Live_max,
            Hero_Mana,
            Hero_Mana_max,

            Hero_Level,
            Hero_Experience,
            Hero_Experience_to_next_Level,

            Hero_Strength,
            Hero_Dexterity,
            Hero_Wisdom,
            Hero_Charisma,

            Hero_Attack,
            Hero_Parade,

            Hero_Gold,
            Hero_Food,
            Hero_Poisonfactor,

            Hero_Map,
            Hero_use_Vehicle,

            Hero_use_Shield,

            Hero_use_no_Shield,
            Hero_use_small_Shield,
            Hero_use_big_Shield,

            Hero_use_Weapon,

            Hero_use_one_Hand_Weapon,
            Hero_use_two_Hand_Weapon,

            // Bool-Values
            Hero_is_Female,

            Hero_on_Worldmap,
            Hero_on_Townmap,
            Hero_on_Battlemap,
            Hero_on_Dungeonmap,

            Hero_use_Nothing,
            Hero_use_Horse,
            Hero_use_Unicorn,
            Hero_use_Ship,
            Hero_use_Lizard,

            Hero_is_Riding,
            Hero_is_Flying,

            Hero_is_Cheating

        }; // Stats

        struct Hero_Position
        {
            int Global_x;
            int Global_y;

            int Battle_x;
            int Battle_y;

            int Town_x;
            int Town_y;

            int Dungeon_x;
            int Dungeon_y;

        }; // Hero_Position

        struct Order
        {
            std::string Command;
            Allegro_Input::Key Key;

        }; // Order

        Hero(Allegro_Datafile *curr_Data, Allegro_Output *curr_Output, Mapinterface *curr_Map, UniText *curr_Language, const std::string &HName, const bool &Gender);

        ~Hero();

    void execute_Command(Order &Command);

    void set_Name(const std::string &Name);
    std::string get_Name();

    /*
    Map and Vehicle takes the the second Parameter the Hero_on_ Keys.
    This will stored in Hero_Status.on_Map or Hero_Status.on_Vehicle.
    To check, compare the Map with Hero_on_<Map> or the Vehicle with Hero_on_<Vehicle>
    When the flag change is true, the Value will be added to the Key, else it will be setted directly
    */
    void set_Value(const int &Typ, const int &Value, const bool &change);
    void set_Status(const int &Typ, const bool &Value, const bool &change);
    void set_Position(const int &Pos_x, const int &Pos_y);

    Hero_Status get_Herostatus();
    void set_Herostatus(Hero_Status &HStatus, Hero_Position &HPosition);

    int get_Value(const int &Typ);
    bool get_Status(const int &Typ);
    Hero_Position get_Position();

    void draw_Hero(int Pos_x, int Pos_y);
    std::string find_Treasure();

    bool get_Blocked(const int &Pos_x, const int &Pos_y);

    private:

    int get_Const(const std::string &Ini);
    void enter_Object();

    Allegro_Datafile *DDD_Data;
    Allegro_Output *DDD_Output;
    Mapinterface *DDD_Map;
    UniText *DDD_Translator;

    std::string Hero_Name;

    Hero_Status Status;

    Hero_Position current_Postion;

}; // Hero

#endif // HERO_H
