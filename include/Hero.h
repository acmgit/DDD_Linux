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
        enum Stats
        {
            Hero_Live,
            Herostat_Live_max,
            Hero_Mana,
            Herostat_Mana_max,

            Hero_Experience,
            Herostat_Experience_to_next_Level,
            Herostat_Level,

            Herostat_Strength,
            Herostat_Dexterity,
            Herostat_Wisdom,
            Herostat_Charisma,

            Herostat_Attack,
            Herostat_Parade,

            Hero_Gold,
            Hero_Food,
            Hero_Poison,

            Hero_Cheater
        };

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
        };

        enum Hero_Mode
        {
            Hero_Global,
            Hero_Battle,
            Hero_Town,
            Hero_Dungeon,
            Hero_Horse,
            Hero_Unicorn,
            Hero_Shipping,
            Hero_Flying,
        };

        struct Order
        {
            std::string Command;
            Allegro_Input::Key Key;
        };

        struct Hero_Status
        {
            bool one_Hand;
            bool small_Shield;
            bool big_Shield;
            bool two_Hand;
            bool is_Poisoned;
            bool is_Shipping;
            bool on_Horse;
            bool on_Unicorn;
            bool on_Lizard;
            bool is_Flying;
            bool to_Hunger;
            bool is_Dead;
            bool cheater;
        };

        Hero(Allegro_Datafile *curr_Data, Allegro_Output *curr_Output, Mapinterface *curr_Map, UniText *curr_Language, const std::string &HName, const bool &Gender);

        ~Hero();

    void execute_Command(Order &Command);

    void set_Gender(const bool &set_Female);
    bool is_Female();

    void set_Name(const std::string &Name);
    std::string get_Name();

    void set_Value(const int &Typ, const int &Value, const bool &Increment);
    int get_Value(const int &Typ);

    void set_Position(const int &Pos_x, const int &Pos_y);
    Hero_Position get_Position();

    void switch_Heromode(const int &Hero_Mode);
    int get_Heromode();

    void draw_Hero(int Pos_x, int Pos_y);

    private:

    int get_Const(const std::string &Ini);
    void change_Value(int &Stat, const int &Val, const bool &Inc);

    void Enter_Object();

    Allegro_Datafile *DDD_Data;
    Allegro_Output *DDD_Output;
    Mapinterface *DDD_Map;
    UniText *DDD_Translator;

    std::string Hero_Name;
    bool Female;

    Hero_Status Status;

    int Playmode;
    Hero_Position current_Postion;

    int Poisonfactor;
    int Maximal_Live;
    int Live;
    int Maximal_Mana;
    int Mana;

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

}; // Hero

#endif // HERO_H
