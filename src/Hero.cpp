#ifndef HERO_CPP
#define HERO_CPP

#include "Hero.h"
#include "Allegro_Datafile.h"
#include "Allegro_Output.h"
#include "Mapinterface.h"
#include "UniText.h"
#include "Allegro_Input.h"

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

    set_Value(Hero_Live, get_Const("Live"), false);
    set_Value(Hero_Live_max, get_Const("Maxlive"), false);

    set_Value(Hero_Mana, get_Const("Mana"), false);
    set_Value(Hero_Mana_max, get_Const("Maxmana"), false);

    set_Value(Hero_Level, get_Const("Level"), false);
    set_Value(Hero_Experience, get_Const("Experience"), false);
    set_Value(Hero_Experience_to_next_Level, get_Const("Nextlevel"), false);

    set_Value(Hero_Strength, get_Const("Strength"), false);
    set_Value(Hero_Dexterity, get_Const("Dexterity"), false);
    set_Value(Hero_Wisdom, get_Const("Wisdom"), false);
    set_Value(Hero_Charisma, get_Const("Charisma"), false);

    set_Value(Hero_Attack, get_Const("Attack"), false);
    set_Value(Hero_Parade, get_Const("Parade"), false);

    set_Value(Hero_Gold, get_Const("Gold"), false);
    set_Value(Hero_Food, get_Const("Food"), false);
    set_Value(Hero_Poisonfactor, get_Const("Poisonfactor"), false);

    set_Value(Hero_use_Weapon, Hero_use_one_Hand_Weapon, false);
    set_Value(Hero_use_Shield, Hero_use_no_Shield, false);

    set_Value(Hero_use_Vehicle, Hero_use_Nothing, false);

    set_Status(Hero_is_Cheating, false, false);
    set_Status(Hero_is_Female, Gender, false);

    set_Value(Hero_Map, Hero_on_Worldmap, false);

    set_Position(get_Const("Startpos_x"), get_Const("Startpos_y"));

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

std::string Hero::get_Name()
{
    return Hero_Name;

} // get_Name

void Hero::set_Name(const std::string &Name)
{
    Hero_Name = Name;

} // set_Name

void Hero::set_Value(const int &Typ, const int &Value, const bool &change)
{
    switch(Typ)
    {
        case Hero_Live:
        {
            if(change)
            {
                Status.Live = Status.Live + Value;

            }
            else
            {
                Status.Live = Value;

            } // if change

            break;

        } // Hero_Live

        case Hero_Live_max:
        {
            if(change)
            {
                Status.Maximal_Live = Status.Maximal_Live + Value;

            }
            else
            {
                Status.Maximal_Live = Value;

            }// if change

            break;

        } // Live_max

        case Hero_Mana:
        {
            if(change)
            {
                Status.Mana = Status.Mana + Value;

            }
            else
            {
                Status.Mana = Value;

            }// if change

            break;

        } // Mana

        case Hero_Mana_max:
        {
            if(change)
            {
                Status.Maximal_Mana = Status.Mana + Value;

            }
            else
            {
                Status.Maximal_Mana = Value;

            }// if change

            break;

        } // Mana_max

        case Hero_Strength:
        {
            if(change)
            {
                Status.Strength = Status.Strength + Value;

            }
            else
            {
                Status.Strength = Value;

            }// if change

            break;

        } // Strength

        case Hero_Dexterity:
        {
            if(change)
            {
                Status.Dexterity = Status.Dexterity + Value;

            }
            else
            {
                Status.Dexterity = Value;

            } // if change

            break;

        } // Dexterity

        case Hero_Wisdom:
        {
            if(change)
            {
                Status.Wisdom = Status.Wisdom + Value;

            }
            else
            {
                Status.Wisdom = Value;

            }// if change

            break;

        } // Wisdom

        case Hero_Charisma:
        {
            if(change)
            {
                Status.Charisma = Status.Charisma + Value;

            }
            else
            {
                Status.Charisma = Value;

            }// if change

            break;

        } // Charisma

        case Hero_Attack:
        {
            if(change)
            {
                Status.Attack = Status.Attack + Value;

            }
            else
            {
                Status.Attack = Value;

            }// if change

            break;

        } // Attack

        case Hero_Parade:
        {
            if(change)
            {
                Status.Parade = Status.Parade + Value;

            }
            else
            {
                Status.Parade = Value;

            }// if change

            break;

        } // Parade

        case Hero_Gold:
        {
            if(change)
            {
                Status.Gold = Status.Gold + Value;

            }
            else
            {
                Status.Gold = Value;

            }// if change

            break;

        } // Gold

        case Hero_Food:
        {
            if(change)
            {
                Status.Food = Status.Food + Value;

            }
            else
            {
                Status.Food = Value;

            }// if change

            break;

        } // Food

        case Hero_Level:
        {
            if(change)
            {
                Status.Level = Status.Level + Value;

            }
            else
            {
                Status.Level = Value;

            }// if change

            break;

        } // Level

        case Hero_Experience_to_next_Level:
        {
            if(change)
            {
                Status.Experience_to_next_Level = Status.Experience_to_next_Level + Value;

            }
            else
            {
                Status.Experience_to_next_Level = Value;

            }// if change

            break;

        } // Exp to next Level

        case Hero_Experience:
        {
            if(change)
            {
                Status.Experience = Status.Experience + Value;

            }
            else
            {
                Status.Experience = Value;

            }// if change

            break;

        } // Experience

        case Hero_Poisonfactor:
        {
            if(change)
            {
                Status.Poisonfactor = Status.Poisonfactor + Value;

            }
            else
            {
                Status.Poisonfactor = Value;

            }// if change

            break;

        } // Poisonfactor

        case Hero_Map:
        {
            Status.on_Map = Value;
            break;

        } // on Map

        case Hero_use_Vehicle:
        {

            Status.is_Riding = false;
            Status.is_Flying = false;
            Status.on_Vehicle = Value;
            break;

        } // on Vehicle

        case Hero_use_Shield:
        {
            Status.has_Shield = Value;
            break;

        } // use_Shield

        case Hero_use_Weapon:
        {
            // With a two-Hand-Weapon it's impossible to use a Shield
            if(Value == Hero_use_two_Hand_Weapon)
            {
                Status.has_Shield = Hero_use_no_Shield;
            }
            Status.handle_Weapon = Value;
            break;

        } // use_Weapon

        default:
        {
            #ifdef DEBUG
            Log("(" << ErrorLog.ILLEGAL_ACCESS << ") Unknown Herovalue setted: " << Typ)
            #endif // DEBUG
            break;

        } // Unknown

    } // switch Typ

} // set_Value

void Hero::set_Status(const int &Typ, const bool &Value, const bool &change)
{
    switch (Typ)
    {
        case Hero_is_Female:
        {
            if(change)
            {
                Status.is_Female = !Status.is_Female;

            }
            else
            {
                Status.is_Female = Value;

            }// if change

            break;

        } // is_Female

        case Hero_is_Flying:
        {
            if(change)
            {
                Status.is_Flying = !Status.is_Flying;

            }
            else
            {
                Status.is_Flying = Value;

            }// if change

            break;

        } // is_Flying

        case Hero_is_Riding:
        {
            if(change)
            {
                Status.is_Riding = !Status.is_Riding;

            }
            else
            {
                Status.is_Riding = Value;

            }// if change

            break;

        } // is_Riding

        case Hero_is_Cheating:
        {
            if(change)
            {
                Status.is_Cheating = !Status.is_Cheating;

            }
            else
            {
                Status.is_Cheating = Value;

            }// if change

            break;

        } // is_Cheating

        default:
        {
            #ifdef DEBUG
            Log("(" << ErrorLog.ILLEGAL_ACCESS << ") Unknown Herostatus setted: " << Typ)
            #endif // DEBUG
            break;

        } // Unknown

    } // switch Typ

} // set_Status

int Hero::get_Value(const int &Typ)
{
    int Value = -1;

    switch(Typ)
    {
        case Hero_Live:
        {
            Value = Status.Live;
            break;

        } // Hero_Live

        case Hero_Live_max:
        {
            Value = Status.Maximal_Live;
            break;

        } // Live_max

        case Hero_Mana:
        {
            Value = Status.Mana;
            break;

        } // Mana

        case Hero_Mana_max:
        {
            Value = Status.Maximal_Mana;
            break;

        } // Mana_max

        case Hero_Strength:
        {
            Value = Status.Strength;
            break;

        } // Strength

        case Hero_Dexterity:
        {
            Value = Status.Dexterity;
            break;

        } // Dexterity

        case Hero_Wisdom:
        {
            Value = Status.Wisdom;
            break;

        } // Wisdom

        case Hero_Charisma:
        {
            Value = Status.Charisma;
            break;

        } // Charisma

        case Hero_Attack:
        {
            Value = Status.Attack;
            break;

        } // Attack

        case Hero_Parade:
        {
            Value = Status.Parade;
            break;

        } // Parade

        case Hero_Gold:
        {
            Value = Status.Gold;
            break;

        } // Gold

        case Hero_Food:
        {
            Value = Status.Food;
            break;

        } // Food

        case Hero_Level:
        {
            Value = Status.Level;
            break;

        } // Level

        case Hero_Experience_to_next_Level:
        {
            Value = Status.Experience_to_next_Level;
            break;

        } // Exp to next Level

        case Hero_Experience:
        {
            Value = Status.Experience;
            break;

        } // Experience

        case Hero_Poisonfactor:
        {
            Value = Status.Poisonfactor;
            break;

        } // Poisonfactor

        case Hero_Map:
        {
            Value = Status.on_Map;
            break;

        } // on Map

        case Hero_use_Vehicle:
        {
            Value = Status.on_Vehicle;
            break;

        } // on Vehicle

        default:
        {
            #ifdef DEBUG
            Log("(" << ErrorLog.ILLEGAL_ACCESS << ") Unknown Herovalue getted: " << Typ)
            #endif // DEBUG
            break;

        } // Unknown

    } // switch Typ

    return Value;

} // get_Value

bool Hero::get_Status(const int &Typ)
{
    bool Val = false;

    switch(Typ)
    {
        case Hero_is_Female:
        {
            Val = Status.is_Female;
            break;

        } // is_Female

        case Hero_is_Riding:
        {
            Val = Status.is_Riding;
            break;

        } // is_Riding

        case Hero_is_Flying:
        {
            Val = Status.is_Flying;
            break;

        } // is_Flying

        case Hero_is_Cheating:
        {
            Val = Status.is_Cheating;
            break;

        } // is_Cheating

        default:
        {
            #ifdef DEBUG
            Log("(" << ErrorLog.ILLEGAL_ACCESS << ") Unknown Herostatus getted: " << Typ)
            #endif // DEBUG
            break;

        } // Unknown

    } // switch(Typ)

    return Val;

} // get_Status;

Hero::Hero_Position Hero::get_Position()
{
    return current_Postion;

} // get_Postion

void Hero::set_Position(const int &Pos_x, const int &Pos_y)
{
    switch(Status.on_Map)
    {
        case Hero_on_Worldmap:
        {
            current_Postion.Global_x = Pos_x;
            current_Postion.Global_y = Pos_y;
            break;

        } // Global

        case Hero_on_Battlemap:
        {
            current_Postion.Battle_x = Pos_x;
            current_Postion.Battle_y = Pos_y;
            break;

        } // Battle

        case Hero_on_Townmap:
        {
            current_Postion.Battle_x = Pos_x;
            current_Postion.Battle_y = Pos_y;
            break;

        } // Battle

        case Hero_on_Dungeonmap:
        {
            current_Postion.Dungeon_x = Pos_x;
            current_Postion.Dungeon_y = Pos_y;
            break;

        } // Dungeon

        default:
        {
            #ifdef DEBUG
            Log("(" << ErrorLog.ILLEGAL_ACCESS << ") Unknown Position setted: " << Status.on_Map)
            #endif // DEBUG
            break;

        } // Unknown

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
            if(!get_Blocked(current_Postion.Global_x, current_Postion.Global_y))
            {
                ++current_Postion.Global_y;
                DDD_Output->write_OnConsole(DDD_Data->get_Color("red"), DDD_Data->get_Color("transparent"), DDD_Translator->Print("[Blocked]"), true);
            }

            DDD_Output->play_Sound("Step");

            break;

        } // case N

        // South
        case 85:
        {
            DDD_Output->write_OnConsole(DDD_Data->get_Color("gold"), DDD_Data->get_Color("transparent"), DDD_Translator->Print("[South]"), true);
            ++current_Postion.Global_y;
            DDD_Map->convert_WorldmapCoords(current_Postion.Global_x, current_Postion.Global_y);
            if(!get_Blocked(current_Postion.Global_x, current_Postion.Global_y))
            {
                --current_Postion.Global_y;
                DDD_Output->write_OnConsole(DDD_Data->get_Color("red"), DDD_Data->get_Color("transparent"), DDD_Translator->Print("[Blocked]"), true);
            }

            DDD_Output->play_Sound("Step");

            break;

        } // case S

        // West
        case 82:
        {
            DDD_Output->write_OnConsole(DDD_Data->get_Color("gold"), DDD_Data->get_Color("transparent"), DDD_Translator->Print("[West]"), true);
            --current_Postion.Global_x;
            DDD_Map->convert_WorldmapCoords(current_Postion.Global_x, current_Postion.Global_y);
            if(!get_Blocked(current_Postion.Global_x, current_Postion.Global_y))
            {
                ++current_Postion.Global_x;
                DDD_Output->write_OnConsole(DDD_Data->get_Color("red"), DDD_Data->get_Color("transparent"), DDD_Translator->Print("[Blocked]"), true);
            }

            DDD_Output->play_Sound("Step");

            break;

        } // case W

        // East
        case 83:
        {
            DDD_Output->write_OnConsole(DDD_Data->get_Color("gold"), DDD_Data->get_Color("transparent"), DDD_Translator->Print("[East]"), true);
            ++current_Postion.Global_x;
            DDD_Map->convert_WorldmapCoords(current_Postion.Global_x, current_Postion.Global_y);
            if(!get_Blocked(current_Postion.Global_x, current_Postion.Global_y))
            {
                --current_Postion.Global_x;
                DDD_Output->write_OnConsole(DDD_Data->get_Color("red"), DDD_Data->get_Color("transparent"), DDD_Translator->Print("[Blocked]"), true);
            }

            DDD_Output->play_Sound("Step");

            break;

        } // case W

        // cheating
        case 58:
        {
            set_Status(Hero_is_Cheating, true, true);
            break;

        } // case F12

        // F4
        case 50:
        {
            if(Status.is_Cheating)
            {
                Status.is_Female = !Status.is_Female;

            } // if is_Cheating

            break;

        } // case F4

        // F5
        case 51:
        {
            if(Status.is_Cheating)
            {
                if(Status.on_Vehicle == Hero_use_Ship)
                {
                    Status.on_Vehicle = Hero_use_Nothing;

                }
                else
                {
                    Status.on_Vehicle = Hero_use_Ship;

                } // if on_Vehicle = Ship

            } // if is_Cheating
            break;

        } // case F5

        // F6
        case 52:
        {
            if(Status.is_Cheating)
            {
                if(Status.on_Vehicle == Hero_use_Horse)
                {
                    Status.on_Vehicle = Hero_use_Nothing;

                }
                else
                {
                    Status.on_Vehicle = Hero_use_Horse;

                } // if on_Vehicle = Horse

            } // if is_Cheating
            break;

        } // case F6

        // case F7
        case 53:
        {
            if(Status.is_Cheating)
            {
                if(Status.on_Vehicle == Hero_use_Unicorn)
                {
                    Status.on_Vehicle = Hero_use_Nothing;

                }
                else
                {
                    Status.on_Vehicle = Hero_use_Unicorn;

                } // if on_Vehicle = Horse

            } // if is_Cheating
            break;

        } // case F7

        // F8
        case 54:
        {
            if(Status.is_Cheating)
            {
                if(Status.on_Vehicle == Hero_use_Lizard)
                {
                    Status.on_Vehicle = Hero_use_Nothing;

                }
                else
                {
                    Status.on_Vehicle = Hero_use_Lizard;

                } // if on_Vehicle = Horse

            } // if is_Cheating
            break;

        } // case F8

        // e (enter)
        case 5:
        {
            DDD_Output->write_OnConsole(DDD_Data->get_Color("gold"), DDD_Data->get_Color("transparent"), DDD_Translator->Print("[Enter]"), false);
            enter_Object();
            break;

        } // case E

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

    if(Status.Live <= 0)
    {
        Hero.Sheetpos_x = DDD_Data->find_Index("[HER_dead]").Number;

    }
    else
    {
        switch(Status.on_Vehicle)
        {
            case Hero_use_Ship:
            {
                Hero.Sheetpos_x = DDD_Data->find_Index("[HER_on_Ship]").Number;
                break;

            } // on Ship

            case Hero_use_Horse:
            {
                Hero.Sheetpos_x = DDD_Data->find_Index("[HER_on_Horse]").Number;
                break;

            } // on Horse

            case Hero_use_Unicorn:
            {
                Hero.Sheetpos_x = DDD_Data->find_Index("[HER_on_Unicorn]").Number;
                break;

            } // on Unicorn

            case Hero_use_Lizard:
            {
                Hero.Sheetpos_x = DDD_Data->find_Index("[HER_on_Dragon]").Number;
                break;

            } // on Dragon

            case Hero_use_Nothing:
            {
                if(Status.Poisonfactor <= 0) // Hero is healty
                {
                    switch(Status.has_Shield)
                    {
                        case Hero_use_no_Shield:
                        {
                            if(!get_Status(Hero_is_Female))
                            {
                                Hero.Sheetpos_x = DDD_Data->find_Index("[HER_Sword]").Number;

                            }
                            else
                            {
                                Hero.Sheetpos_x = DDD_Data->find_Index("[HER_Sword_female]").Number;

                            } // if Hero_is_Female

                            break;

                        } // no Shield and healty

                        case Hero_use_big_Shield:
                        case Hero_use_small_Shield:
                        {
                            if(!get_Status(Hero_is_Female))
                            {
                                Hero.Sheetpos_x = DDD_Data->find_Index("[HER_Shield]").Number;

                            }
                            else
                            {
                                Hero.Sheetpos_x = DDD_Data->find_Index("[HER_Shield_female]").Number;

                            } // if Hero_is_Female

                            break;

                        } // with Shield and healty

                    } // switch (has_Shield)

                }
                else
                {

                    switch(Status.has_Shield)
                    {
                        case Hero_use_no_Shield:
                        {
                            if(!get_Status(Hero_is_Female))
                            {
                                Hero.Sheetpos_x = DDD_Data->find_Index("[HER_Sword_poisoned]").Number;

                            }
                            else
                            {
                                Hero.Sheetpos_x = DDD_Data->find_Index("[HER_Sword_poisoned_female]").Number;

                            } // if Hero_is_Female

                            break;

                        } // no Shield and poisoned

                        case Hero_use_big_Shield:
                        case Hero_use_small_Shield:
                        {
                            if(!get_Status(Hero_is_Female))
                            {
                                Hero.Sheetpos_x = DDD_Data->find_Index("[HER_Shield_poisoned]").Number;

                            }
                            else
                            {
                                Hero.Sheetpos_x = DDD_Data->find_Index("[HER_Shield_poisoned_female]").Number;

                            } // if Hero_is_Female

                            break;

                        } // with Shield and poisoned

                    } // switch (has_Shield)

                } // if Hero is Poisoned

            } // Hero is on no Vehicle

        } // switch (Vehicle)

    } // if is_Dead

    DDD_Output->render_Tile(Hero);

} // draw_Hero

void Hero::enter_Object()
{
    std::string Entering;
    Entering = DDD_Map->check_Town(current_Postion.Global_x, current_Postion.Global_y);

    if(Entering.size() > 0)
    {
        DDD_Output->write_OnConsole(DDD_Data->get_Color("gold"), DDD_Data->get_Color("transparent"), DDD_Translator->Print("[POI_" + Entering + "]"), true);

    }
    else
    {
        DDD_Output->write_OnConsole(DDD_Data->get_Color("gold"), DDD_Data->get_Color("transparent"), "", true);
        DDD_Output->write_OnConsole(DDD_Data->get_Color("cyan"), DDD_Data->get_Color("transparent"), DDD_Translator->Print("[Please]"), true);

    } // Town was entered

} // Enter_Object

std::string Hero::find_Treasure()
{
    std::string Result;

    switch(Status.on_Map)
    {
        case Hero_on_Worldmap:
        {
            Result = DDD_Map->find_Treasure(current_Postion.Global_x, current_Postion.Global_y);
            break;

        } // case Global

        case Hero_on_Battlemap:
        {
            Result = DDD_Map->find_Treasure(current_Postion.Battle_x, current_Postion.Battle_y);
            break;

        } // case Battle

        case Hero_on_Townmap:
        {
            Result = DDD_Map->find_Treasure(current_Postion.Town_x, current_Postion.Town_y);
            break;

        } // case Town

        case Hero_on_Dungeonmap:
        {
            Result = DDD_Map->find_Treasure(current_Postion.Dungeon_x, current_Postion.Dungeon_y);
            break;

        } // case Dungeon

    } // switch(Playmode)

    if(Result.size() > 0)
    {
        Result = DDD_Translator->Print("[POI_" + Result + "]");
        return Result;

    }
    else
    {
        Result = DDD_Translator->Print("[Nothing]");
        return Result;

    } // if Result > 0

} // find_Treasure

bool Hero::get_Blocked(const int &Pos_x, const int &Pos_y)
{
    bool blocked = false;
    Mapinterface::Tile checkTile;

    switch(Status.on_Map)
    {
        case Hero_on_Worldmap:
        {
            checkTile = DDD_Map->get_Tilecheck(Mapinterface::Worldmaptile, Pos_x, Pos_y);
            if(!Status.is_Cheating)
            {
                switch(Status.on_Vehicle)
                {
                    case(Hero_use_Ship):
                    {
                        if(checkTile.shipable)
                        {
                            return true;

                        } // if shipable

                        break;

                    } // Hero on Ship

                    case(Hero_use_Nothing):
                    case(Hero_use_Horse):
                    case(Hero_use_Unicorn):
                    {
                        if(checkTile.walkable)
                        {
                            return true;

                        } // if walkable

                        break;

                    } // Hero on Nothing, Horse or Unicorn

                    case(Hero_use_Lizard):
                    {
                        if(Status.is_Flying)
                        {
                            if(checkTile.flyable)
                            {
                                return true;

                            } // if flyable (Hero want landing on Tile)
                        }
                        else
                        {
                            if(checkTile.walkable)
                            {
                                return true;

                            } // if walkable (Hero is only going with the Dragon)

                        } // if is_Flying
                        break;

                    } // Hero use Lizard

                } // switch(on_Vehicle)

            } // if is_Cheating
            else
            {
                return true;

            } // if is_Cheating

            break;

        } // on_Worldmap

        case Hero_on_Battlemap:
        {
            break;

        } // on_Battlemap

        case Hero_on_Townmap:
        {
            break;

        } // on_Townmap

        case Hero_on_Dungeonmap:
        {
            break;

        } // on_Dungeonmap

    } // switch(on_Map)

    return blocked;

} // get_Blocked

Hero::Hero_Status Hero::get_Herostatus()
{
    return Status;

} // get_Herostatus

void Hero::set_Herostatus(Hero_Status &HStatus, Hero_Position &HPosition)
{
    Status = HStatus;
    current_Postion = HPosition;

} // set_Herostatus

#endif // HERO_CPP
