#ifndef HERO_CPP
#define HERO_CPP

#include "Hero.h"
#include "Allegro_Datafile.h"

#include <string>

#ifdef DEBUG
#include "Logfile.h"
#endif // DEBUG

Hero::Hero(Allegro_Datafile *curr_Data, const std::string &HName, const bool &Gender)
{
    Data = curr_Data;
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

    current_Postion.Battle_x = 0;
    current_Postion.Battle_y = 0;

    current_Postion.Dungeon_x = 0;
    current_Postion.Dungeon_y = 0;

    current_Postion.Town_x = 0;
    current_Postion.Town_y = 0;

    current_Postion.Global_x = get_Const("Startpos_x");
    current_Postion.Global_y = get_Const("Startpos_y");

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Heroclass opened.")
    #endif // DEBUG

} // Hero

Hero::~Hero()
{
    Data = nullptr;

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Heroclass closed.")
    #endif // DEBUG

} // ~Hero

int Hero::get_Const(const std::string &Ini)
{
    return Data->find_Index("[INI_Hero_" + Ini + "]").Number;

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

        case Herostat_Strengt:
        {
            change_Value(Strength, Value, Increment);
            break;

        } // Strength

        case Herostat_Dexterity:
        {
            change_Value(Dexterity, Value, Increment);
            break;

        } // Dexterity

        case Herostat_Widsom:
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

        case Herostat_Strengt:
        {
            Value = Strength;
            break;

        } // Strength

        case Herostat_Dexterity:
        {
            Value = Dexterity;
            break;

        } // Dexterity

        case Herostat_Widsom:
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
            Gold = Gold;
            break;

        } // Gold

        case Hero_Food:
        {
            Food = Food;
            break;

        } // Food

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

void Hero::get_Position(Hero_Position &Position)
{
    Position.Battle_x = current_Postion.Battle_x;
    Position.Battle_y = current_Postion.Battle_y;

    Position.Dungeon_x = current_Postion.Dungeon_x;
    Position.Dungeon_y = current_Postion.Dungeon_y;

    Position.Global_x = current_Postion.Global_x;
    Position.Global_y = current_Postion.Global_y;

    Position.Town_x = current_Postion.Town_x;
    Position.Town_y = current_Postion.Town_y;

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

#endif // HERO_CPP
