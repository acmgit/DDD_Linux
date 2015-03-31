#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <allegro/system.h>
#include <allegro/datafile.h>

#include "bass.h"

class Sound
{
    public:
        Sound();
        ~Sound();

        void play_Music(std::string &Filename);
        void play_Sound(std::string &Filename);
        void play_Memorysound();

    protected:
    private:

    DATAFILE *Samples;

    HSAMPLE sound;
    DWORD sound_channel;

    HSTREAM music;
    DWORD music_channel;

};

#endif // SOUND_H
