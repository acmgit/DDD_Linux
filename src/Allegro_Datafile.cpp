#include "Allegro_Datafile.h"

#include <allegro/system.h>
#include <allegro/graphics.h>
#include <allegro/gfx.h>
#include <allegro/font.h>
#include <sstream>
#include <iostream>
#include <fstream>

#ifdef DEBUG
#include "Logfile.h"
#include <allegro/system.h>

#endif // DEBUG
#include <string>
#include <map>

Allegro_Datafile::Allegro_Datafile(const std::string &Datafile, const std::string &DatafileIndex, const std::string &Configfile)
{

#ifdef DEBUG
    Log("Loading " << Datafile.c_str() << ".")
#endif // DEBUG

    Data = load_datafile(Datafile.c_str());
    if(!Data)
    {
        std::string DataError = "Could not load <";
        DataError = DataError + Datafile;
        DataError = DataError + ">.";

#ifdef DEBUG
        Log("(" << ErrorLog.FILE_NOT_FOUND << ") " << DataError.c_str())
#endif // DEBUG

        allegro_message(DataError.c_str());
        allegro_exit();

    } // if !Pictures

    Filename = Datafile;

    // Get inital Values
    load_Index(Configfile);

    //generateIndex();
    load_Index(DatafileIndex);

    Tilewidth = find_Index("[INI_Worldtileswidth]").Number;
    Tileheight = find_Index("[INI_Worldtilesheight]").Number;

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Allegro_Datafile opened.")
#endif // DEBUG

} // Datafile

Allegro_Datafile::~Allegro_Datafile()
{
    unload_datafile(Data);

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Datafile destroyed.")
    Log("(" << ErrorLog.ALLOK << ") Allegro_Datafile closed")
#endif // DEBUG

} // ~Datafile

const std::string Allegro_Datafile::get_Filename()
{
    return Filename;

} // get_Filename

DATAFILE* Allegro_Datafile::get_Datafile()
{
    return Data;

} // get_Datafile

void Allegro_Datafile::add_Index(Index newEntry)
{
    Dataindex.insert(std::pair<std::string, int>(newEntry.Name, newEntry.Number));

} // add_Index

void Allegro_Datafile::remove_Index(Index Entry)
{
    std::map<std::string, int>::iterator delEntry;
    delEntry = Dataindex.find(Entry.Name);

    if(delEntry != Dataindex.end())
    {
        //*delEntry.erase();

    } // if delEntry != end()

} // remove_Index

Allegro_Datafile::Index Allegro_Datafile::find_Index(const std::string &Keyname)
{
    std::map<std::string, int>::iterator Entry;
    Entry = Dataindex.find(Keyname);
    Index foundEntry;

    if(Entry != Dataindex.end())
    {
        foundEntry.Name = (*Entry).first;
        foundEntry.Number = (*Entry).second;

    }
    else
    {
        foundEntry.Name = "";
        foundEntry.Number = -1;

    } // if delEntry != end()

    return foundEntry;

} // find_Index

BITMAP* Allegro_Datafile::get_Bitmap(const std::string &Bitname)
{
    Index Entry;
    BITMAP *Dataentry = nullptr;

    Entry = find_Index(Bitname);

    if(Entry.Number != -1)
    {
        Dataentry = (BITMAP*) Data[Entry.Number].dat;

    } // if Entry.Number

    return Dataentry;

} // get_Bitmap

FONT* Allegro_Datafile::get_Font(const std::string &Fontname)
{
    Index Entry;
    FONT *Dataentry = nullptr;

    Entry = find_Index(Fontname);

    if(Entry.Number != -1)
    {
        Dataentry = (FONT*) Data[Entry.Number].dat;

    } // if Entry.Number

    return Dataentry;

} // get_Font

PALETTE* Allegro_Datafile::get_Palette(const std::string &Palettename)
{
    Index Entry;
    PALETTE *Dataentry = nullptr;

    Entry = find_Index(Palettename);

    if(Entry.Number != -1)
    {
        Dataentry = (PALETTE*) Data[Entry.Number].dat;

    } // if Entry.Number

    return Dataentry;

} // get_Palette

void Allegro_Datafile::load_Index(std::string Indexfile)
{
    std::ifstream File(Indexfile.c_str());

    if(File.is_open())
    {
#ifdef DEBUG
    Log("File " << Indexfile.c_str() << " opened.")
#endif // DEBUG
        Index Config;

        while(File.good())
        {
            std::getline(File, Config.Name);

            if((Config.Name.find("[") != Config.Name.npos) && (Config.Name.find("]") != Config.Name.npos))
            {
                std::string Value;
                std::getline(File, Value);
                Config.Number = strtoint(Value);
                add_Index(Config);

            } // if find

        } // while File.good

        File.close();

#ifdef DEBUG
    Log("File " << Indexfile.c_str() << " closed.")
#endif // DEBUG
    } // if File isopen
    else
    {
#ifdef DEBUG
        Log("(" << ErrorLog.FILE_NOT_FOUND << ") " << Indexfile.c_str())
#endif // DEBUG

        std::string Err = "Can't open File: " + Indexfile;
        throw std::runtime_error(Err);
    }

} // load_Index


int Allegro_Datafile::strtoint(std::string Number)
{
    int Num;
    std::stringstream Str;
    Str << Number;
    Str >> Num;

    return Num;

} // strtoint

std::string Allegro_Datafile::inttostr(int Number)
{
    std::ostringstream Str;
    Str << Number;

    return Str.str();

} // inttostr
