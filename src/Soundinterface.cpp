#ifndef SOUNDINTERFACE_CPP
#define SOUNDINTERFACE_CPP

#include "Soundinterface.h"

#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>

#ifdef DEBUG
#include "Logfile.h"
#endif // DEBUG

Soundinterface::Soundinterface(const std::string &Datafile, const std::string &Indexfile)
{
    DDD_Sound = new Sound();
    if(!DDD_Sound)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Couldn't open Soundclass.")
        #endif // DEBUG

        allegro_message("Couldn't open Soundclass.");

    } // if !DDD_Sound


    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Loading Datafile: " << Datafile.c_str())
    #endif // DEBUG

    Sounddata = load_datafile(Datafile.c_str());

    if(!Sounddata)
    {
        #ifdef DEBUG
        Log("Couldn't load Sounddatafile <" << Datafile.c_str() << ">.")
        #endif // DEBUG
        std::string message;
        message = "Couldn't load <" + Datafile + ">.";
        allegro_message(message.c_str());

    } // if !Sounddata

    load_Index(Indexfile);

    Vol = 1.0f;
    streaming = false;

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Soundinterface opened.")
    #endif // DEBUG

} // Soundinterface

Soundinterface::~Soundinterface()
{
    if(DDD_Sound)
    {
        delete DDD_Sound;
        DDD_Sound = nullptr;

    } // if DDD_Sound

    unload_datafile(Sounddata);

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << " Sounddatafile closed.")
    #endif // DEBUG

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << " Soundinterface closed.")
    #endif // DEBUG

} // ~Soundinterface

void Soundinterface::load_Index(const std::string Indexfile)
{
    std::ifstream File(Indexfile.c_str());

    if(File.is_open())
    {
#ifdef DEBUG
    Log("Soundindexfile " << Indexfile.c_str() << " opened.")
#endif // DEBUG
        Index Config;

        while(File.good())
        {
            std::getline(File, Config.Name);

            if((Config.Name.find("[") != Config.Name.npos) && (Config.Name.find("]") != Config.Name.npos))
            {
                std::string Value;
                std::getline(File, Value);
                std::stringstream Str;
                Str << Value;
                Str >> Config.Number;
                Soundindex.insert(std::pair<std::string, int>(Config.Name, Config.Number));
                /*
                #ifdef DEBUG
                Log("Soundname:   " << Config.Name.c_str())
                Log("Soundindex : " << Config.Number)
                #endif // DEBUG
                */

            } // if find

        } // while File.good

        File.close();

#ifdef DEBUG
    Log("Soundindexfile " << Indexfile.c_str() << " closed.")
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

Soundinterface::Index Soundinterface::find_Index(const std::string &Keyname)
{
    std::map<std::string, int>::iterator Entry;
    Entry = Soundindex.find(Keyname);
    Index foundEntry;

    if(Entry != Soundindex.end())
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

void Soundinterface::set_Globalvolume(const float &Volume, const bool &increment)
{
    if(increment)
    {
        Vol = Vol + Volume;
        if(Vol > 1.f)
        {
            Vol = 1.f;

        } // if Vol > 1

    }
    else
    {
        Vol = Vol - Volume;
        if(Vol < 0.f)
        {
            Vol = 0.f;

        } // Vol < 0

    } // if increment

    DDD_Sound->set_Globalvolume(Vol);
    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Global Sound setted to " << Vol)
    #endif // DEBUG

} // set_Globalvolume

void Soundinterface::stream_Music(const std::string &Filename, const float &Volume)
{
    DDD_Sound->stream_Music(Filename, Volume);
    streaming = true;

} // stream_Music(Filname, Volume)

void Soundinterface::stream_Music(const std::string &Filename)
{
    stream_Music(Filename, Vol);

} // stream_Music(Filname)

void Soundinterface::pause_Music()
{
    DDD_Sound->pause_Music();
    streaming = false;

} // pause_Music

void Soundinterface::stop_Music()
{
    DDD_Sound->stop_Music();
    streaming = false;

} // stop_Music

void Soundinterface::play_Music()
{
    DDD_Sound->play_Music();
    streaming = true;

} // play_Music

void Soundinterface::play_Sound(const std::string &Soundname)
{
    play_Sound(Soundname, Vol);

} // play_Sound

void Soundinterface::play_Sound(const std::string &Soundname, const float &Volume)
{

    std::string Keyname = "[SND_" + Soundname + "]";
    Index Entry = find_Index(Keyname);

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Playing Sound: " << Entry.Name.c_str() << " with Index: " << Entry.Number)
    #endif // DEBUG

    DDD_Sound->play_Memorysound(Sounddata, Entry.Number, Volume);

}
#endif // SOUNDINTERFACE_CPP
