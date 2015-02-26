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
    loadIndex(Configfile);

    //generateIndex();
    loadIndex(DatafileIndex);

    Tilewidth = findIndex("[INI_Worldtileswidth]").Number;
    Tileheight = findIndex("[INI_Worldtilesheight]").Number;

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

const std::string Allegro_Datafile::getFilename()
{
    return Filename;

} // getFilename

DATAFILE* Allegro_Datafile::getDatafile()
{
    return Data;

} // getDatafile

void Allegro_Datafile::addIndex(Index newEntry)
{
    Dataindex.insert(std::pair<std::string, int>(newEntry.Name, newEntry.Number));

} // addIndex

void Allegro_Datafile::removeIndex(Index Entry)
{
    std::map<std::string, int>::iterator delEntry;
    delEntry = Dataindex.find(Entry.Name);

    if(delEntry != Dataindex.end())
    {
        //*delEntry.erase();

    } // if delEntry != end()

} // removeIndex

Allegro_Datafile::Index Allegro_Datafile::findIndex(const std::string &Keyname)
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

} // findIndex

BITMAP* Allegro_Datafile::getBitmap(const std::string &Bitname)
{
    Index Entry;
    BITMAP *Dataentry = nullptr;

    Entry = findIndex(Bitname);

    if(Entry.Number != -1)
    {
        Dataentry = (BITMAP*) Data[Entry.Number].dat;

    } // if Entry.Number

    return Dataentry;

} // getBitmap

FONT* Allegro_Datafile::getFont(const std::string &Fontname)
{
    Index Entry;
    FONT *Dataentry = nullptr;

    Entry = findIndex(Fontname);

    if(Entry.Number != -1)
    {
        Dataentry = (FONT*) Data[Entry.Number].dat;

    } // if Entry.Number

    return Dataentry;

} // getFont

PALETTE* Allegro_Datafile::getPalette(const std::string &Palettename)
{
    Index Entry;
    PALETTE *Dataentry = nullptr;

    Entry = findIndex(Palettename);

    if(Entry.Number != -1)
    {
        Dataentry = (PALETTE*) Data[Entry.Number].dat;

    } // if Entry.Number

    return Dataentry;

} // getPalette

void Allegro_Datafile::loadIndex(std::string Indexfile)
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
                addIndex(Config);

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

} // loadIndex


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
