#ifndef HERO_CPP
#define HERO_CPP

#include "Hero.h"
#include "Allegro_Datafile.h"
#include "Allegro_Output.h"
#include "Mapinterface.h"
#include "UniText.h"

#include <string>

#ifdef DEBUG
#include "Logfile.h"
#endif // DEBUG

Hero::Hero(Allegro_Datafile *curr_Data, Allegro_Output *curr_Output, Mapinterface *curr_Map, UniText *curr_Language, const std::string &HName, const bool &Gender)
{
    DDD_Data = curr_Data;
    DDD_Output = curr_Output;
    DDD_Map = curr_Map;
    DDD_Translator = curr_Language;

    Hero_Name = HName;
    Female = Gender;
    Playmode = Hero_Global;

    Live = get_Const("Live");
    Maximal_Live = get_Const("Maxlive");

    Mana = get_Const("Mana");
    Maximal_Mana = get_Const("Maxmana");

    Level = get_Const("Level");
    Experience = get_Const("Experience");
    Experience_to_next_Level = get_Const("Nextlevel");

    Strength = get_Const("Strength");
    Dexterity = get_Const("Dexterity");
    Wisdom = get_Const("Wisdom");
    Charisma = get_Const("Charisma");

    Attack = get_Const("Attack");
    Parade = get_Const("Parade");

    Gold = get_Const("Gold");
    Food = get_Const("Food");

    Poisonfactor = 0;

    current_Postion.Battle_x = 0;
    current_Postion.Battle_y = 0;

    current_Postion.Dungeon_x = 0;
    current_Postion.Dungeon_y = 0;

    current_Postion.Town_x = 0;
    current_Postion.Town_y = 0;

    current_Postion.Global_x = get_Const("Startpos_x");
    current_Postion.Global_y = get_Const("Startpos_y");

    Status.one_Hand = true;
    Status.two_Hand = false;

    Status.big_Shield = false;
    Status.small_Shield = false;

    Status.is_Shipping = false;
    Status.on_Horse = false;
    Status.on_Unicorn = false;
    Status.on_Lizard = false;
    Status.is_Flying = false;

    Status.is_Poisoned = false;
    Status.to_Hunger = false;
    Status.is_Dead = false;

    Poisonfactor = 0;

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Heroclass opened.")
    #endif // DEBUG

} // Hero

Hero::~Hero()
{
    DDD_Data = nullptr;
    DDD_Output = nullptr;
    DDD_Map = nullptr;
    DDD_Translator = nullptr;

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Heroclass closed.")
    #endif // DEBUG

} // ~Hero

int Hero::get_Const(const std::string &Ini)
{
    return DDD_Data->find_Index("[INI_Hero_" + Ini + "]").Number;

} // get_Const

bool Hero::is_Female()
{
    return Female;

} // is_Female

std::string Hero::get_Name()
{
    return Hero_Name;

} // get_Name

void Hero::set_Gender(const bool &set_Female)
{
    Female = set_Female;

} // set_Gender

void Hero::set_Name(const std::string &Name)
{
    Hero_Name = Name;

} // set_Name

void Hero::set_Value(const int &Typ, const int &Value, const bool &Increment)
{
    switch(Typ)
    {
        case Hero_Live:
        {
            change_Value(Live, Value, Increment);
            break;

        } // Hero_Live

        case Herostat_Live_max:
        {
            change_Value(Maximal_Live, Value, Increment);
            break;

        } // Live_max

        case Hero_Mana:
        {
            change_Value(Mana, Value, Increment);
            break;

        } // Mana

        case Herostat_Mana_max:
        {
            change_Value(Maximal_Mana, Value, Increment);
            break;

        } // Mana_max

        case Herostat_Strength:
        {
            change_Value(Strength, Value, Increment);
            break;

        } // Strength

        case Herostat_Dexterity:
        {
            change_Value(Dexterity, Value, Increment);
            break;

        } // Dexterity

        case Herostat_Wisdom:
        {
            change_Value(Wisdom, Value, Increment);
            break;

        } // Wisdom

        case Herostat_Charisma:
        {
            change_Value(Charisma, Value, Increment);
            break;

        } // Charisma

        case Herostat_Attack:
        {
            change_Value(Attack, Value, Increment);
            break;

        } // Attack

        case Herostat_Parade:
        {
            change_Value(Parade, Value, Increment);
            break;

        } // Parade

        case Hero_Gold:
        {
            change_Value(Gold, Value, Increment);
            break;

        } // Gold

        case Hero_Food:
        {
            change_Value(Food, Value, Increment);
            break;

        } // Food

        case Herostat_Level:
        {
            change_Value(Level, Value, Increment);
            break;

        } // Level

        case Herostat_Experience_to_next_Level:
        {
            change_Value(Experience_to_next_Level, Value, Increment);
            break;

        } // Exp to next Level

        case Hero_Experience:
        {
            change_Value(Experience, Value, Increment);
            break;

        } // Experience

        case Hero_Poison:
        {
            change_Value(Poisonfactor, Value, Increment);
            if(Poisonfactor > 0)
            {
                Status.is_Poisoned = true;

            }
            else
            {
                Status.is_Poisoned = false;

            } // if Poisonfactor

            break;

        } // Poisonfactor

        default:
        {
            #ifdef DEBUG
            Log("(" << ErrorLog.ILLEGAL_ACCESS << ") Unknown Herostat: " << Typ)
            #endif // DEBUG
            break;

        } // Unknown

    } // switch Typ

} // set_Value

int Hero::get_Value(const int &Typ)
{
    int Value = 0;

    switch(Typ)
    {
        case Hero_Live:
        {
            Value = Live;
            break;

        } // Hero_Live

        case Herostat_Live_max:
        {
            Value = Maximal_Live;
            break;

        } // Live_max

        case Hero_Mana:
        {
            Value = Mana;
            break;

        } // Mana

        case Herostat_Mana_max:
        {
            Value = Maximal_Mana;
            break;

        } // Mana_max

        case Herostat_Strength:
        {
            Value = Strength;
            break;

        } // Strength

        case Herostat_Dexterity:
        {
            Value = Dexterity;
            break;

        } // Dexterity

        case Herostat_Wisdom:
        {
            Value = Wisdom;
            break;

        } // Wisdom

        case Herostat_Charisma:
        {
            Value = Charisma;
            break;

        } // Charisma

        case Herostat_Attack:
        {
            Value = Attack;
            break;

        } // Attack

        case Herostat_Parade:
        {
            Value = Parade;
            break;

        } // Parade

        case Hero_Gold:
        {
            Value = Gold;
            break;

        } // Gold

        case Hero_Food:
        {
            Value = Food;
            break;

        } // Food

        case Herostat_Level:
        {
            Value = Level;
            break;

        } // Level

        case Herostat_Experience_to_next_Level:
        {
            Value = Experience_to_next_Level;
            break;

        } // Exp to next Level

        case Hero_Experience:
        {
            Value = Experience;
            break;

        } // Experience

        case Hero_Poison:
        {
            Value = Poisonfactor;
            break;

        } // Poisonfactor

        default:
        {
            #ifdef DEBUG
            Log("(" << ErrorLog.ILLEGAL_ACCESS << ") Unknown Herostat: " << Typ)
            #endif // DEBUG
            break;

        } // Unknown

    } // switch Typ

    return Value;

} // get_Value
void Hero::change_Value(int &Stat, const int &Val, const bool &Inc)
{
    if(Inc)
    {
        Stat = Stat + Val;
    }
    else
    {
        Stat = Stat - Val;
    } // if Inc

} // change_Value

Hero::Hero_Position Hero::get_Position()
{
    return current_Postion;

} // get_Postion

void Hero::switch_Heromode(const int &Typ)
{
    Playmode = Typ;

} // switch_Heromode

int Hero::get_Heromode()
{
    return Playmode;

} // get_Heromode

void Hero::set_Position(const int &Pos_x, const int &Pos_y)
{
    switch(Playmode)
    {
        case Hero_Global:
        {
            current_Postion.Global_x = Pos_x;
            current_Postion.Global_y = Pos_y;
            break;

        } // Global

        case Hero_Battle:
        {
            current_Postion.Battle_x = Pos_x;
            current_Postion.Battle_y = Pos_y;
            break;

        } // Battle

        case Hero_Town:
        {
            current_Postion.Battle_x = Pos_x;
            current_Postion.Battle_y = Pos_y;
            break;

        } // Battle

        case Hero_Dungeon:
        {
            current_Postion.Dungeon_x = Pos_x;
            current_Postion.Dungeon_y = Pos_y;
            break;

        } // Dungeon

    } // switch Typ

} // set_Position

void Hero::execute_Command(Order &Command)
{
    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Worldcommand: " << Command.Command.c_str())
    #endif // DEBUG

    switch(Command.Key.Scancode)
    {
        // North
        case 84:
        {
            DDD_Output->write_OnConsole(DDD_Data->get_Color("gold"), DDD_Data->get_Color("transparent"), DDD_Translator->Print("[North]"), true);
            --current_Postion.Global_y;
            DDD_Map->convert_WorldmapCoords(current_Postion.Global_x, current_Postion.Global_y);
            break;

        } // case N

        // South
        case 85:
        {
            DDD_Output->write_OnConsole(DDD_Data->get_Color("gold"), DDD_Data->get_Color("transparent"), DDD_Translator->Print("[South]"), true);
            ++current_Postion.Global_y;
            DDD_Map->convert_WorldmapCoords(current_Postion.Global_x, current_Postion.Global_y);
            break;

        } // case S

        // West
        case 82:
        {
            DDD_Output->write_OnConsole(DDD_Data->get_Color("gold"), DDD_Data->get_Color("transparent"), DDD_Translator->Print("[West]"), true);
            --current_Postion.Global_x;
            DDD_Map->convert_WorldmapCoords(current_Postion.Global_x, current_Postion.Global_y);
            break;

        } // case W

        // East
        case 83:
        {
            DDD_Output->write_OnConsole(DDD_Data->get_Color("gold"), DDD_Data->get_Color("transparent"), DDD_Translator->Print("[East]"), true);
            ++current_Postion.Global_x;
            DDD_Map->convert_WorldmapCoords(current_Postion.Global_x, current_Postion.Global_y);
            break;

        } // case W

        default:
        {
            #ifdef DEBUG
            Log("(" << ErrorLog.ALLOK << ") Unknown Herocommand.")
            #endif // DEBUG

            DDD_Output->write_OnConsole(DDD_Data->get_Color("cyan"), DDD_Data->get_Color("transparent"), DDD_Translator->Print("[Please]"), true);
            break;

        } // Command unknown

    } // switch(Command)

} // execute_Command

void Hero::draw_Hero(int Pos_x, int Pos_y)
{
    Allegro_Output::tileData Hero;

    Hero.Sheet = DDD_Data->get_Bitmap("[SHE_Hero]");
    //Hero.Sheetpos_x = DDD_Data->find_Index("[HER_Sword]").Number;
    Hero.Sheetpos_y = 0;
    Hero.transparency = true;
    Hero.Column = Pos_x;
    Hero.Row = Pos_y;

    //Hero.Column = DDD_Data->find_Index("[INI_Playfieldcolumns]").Number / 2;
    //Hero.Row = DDD_Data->find_Index("[INI_Playfieldrows]").Number / 2;

    if(Status.is_Dead)
    {
        Hero.Sheetpos_x = DDD_Data->find_Index("[HER_dead]").Number;

    }
    else
    {
        if(!Status.is_Shipping)
        {
            if(Status.on_Horse)
            {
                Hero.Sheetpos_x = DDD_Data->find_Index("[HER_on_Horse]").Number;

            }
            else
            {
                if(Status.on_Unicorn)
                {
                    Hero.Sheetpos_x = DDD_Data->find_Index("[HER_on_Unicorn]").Number;

                }
                else
                {
                    if(Status.on_Lizard)
                    {
                        Hero.Sheetpos_x = DDD_Data->find_Index("[HER_on_Dragon]").Number;

                    }
                    else
                    {
                        if(Status.is_Poisoned)
                        {
                            if((Status.small_Shield) || (Status.big_Shield))
                            {
                                Hero.Sheetpos_x = DDD_Data->find_Index("[HER_Shield_poisoned]").Number;
                            }
                            else
                            {
                                Hero.Sheetpos_x = DDD_Data->find_Index("[HER_Sword_poisoned]").Number;
                            } // has Shield and is Poisoned
                        }
                        else
                        {
                            if((Status.small_Shield) || (Status.big_Shield))
                            {
                                Hero.Sheetpos_x = DDD_Data->find_Index("[HER_Shield]").Number;

                            }
                            else
                            {
                                Hero.Sheetpos_x = DDD_Data->find_Index("[HER_Sword]").Number;

                            } // has Shield and isn't poisoned

                        } // is_Poisoned

                    } // on_Lizard

                } // on_Unicorn

            } // on_Horse

        }
        else  // Hero is on Ship
        {
            Hero.Sheetpos_x = DDD_Data->find_Index("[HER_on_Ship]").Number;

        } // is_Shipping

    } // if is_Dead

    DDD_Output->render_Tile(Hero);

} // draw_Hero
#endif // HERO_CPP
