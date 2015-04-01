#ifndef SOUNDINTERFACE_H
#define SOUNDINTERFACE_H

#include <allegro/system.h>
#include <allegro/datafile.h>

#include <map>
#include <string>

#include "Sound.h"

class Soundinterface
{
    public:
        Soundinterface(const std::string &Datafile, const std::string &Indexfile);
        ~Soundinterface();

        void set_Globalvolume(const float &Volume, const bool &increment);

        void stream_Music(const std::string &Filename);
        void stream_Music(const std::string &Filename, const float &Volume);
        void pause_Music();
        void stop_Music();

        void play_Sound(const std::string &Soundname);
        void play_Sound(const std::string &Soundname, const float &Volume);

    private:

    struct Index                        // Entry of an Index
    {
        std::string Name;
        int Number;
    };

        void load_Index(const std::string Indexfile);

        void add_Index(Index newEntry);                                 // Build an Indexentry
        Index find_Index(const std::string &Keyname);                   // Find an Indexentry


    float Vol;
    Sound *DDD_Sound;
    DATAFILE *Sounddata;

    std::map<std::string, int> Soundindex;


};

#endif // SOUNDINTERFACE_H
