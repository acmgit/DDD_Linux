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

        void set_Globalvolume(const float &Volume);

        void stream_Music(const std::string &Filename, const float &Volume);
        void pause_Music();
        void stop_Music();

        void play_Sound(const std::string &Filename);
        void play_Memorysound(DATAFILE *MemSound, const int &Index, const float &Volume);

    protected:
    private:

    HSAMPLE sound;
    HSTREAM music;

};

#endif // SOUND_H
