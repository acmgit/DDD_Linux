#ifndef SOUND_CPP
#define SOUND_CPP

#include <allegro/system.h>

#include "Sound.h"
#include "bass.h"
#include <string>

#ifdef DEBUG
#include "Logfile.h"
#endif // DEBUG

#define DATA_0 0
#define DATA_1 1
#define DATA_2 2


Sound::Sound()
{

    Samples = load_datafile("snd/sound.dat");

    if(!Samples)
    {
        std::string DataError = "Could not load snd/sound.dat";

        #ifdef DEBUG
        Log("(" << ErrorLog.FILE_NOT_FOUND << ") " << DataError.c_str())
        #endif // DEBUG

        allegro_message(DataError.c_str());
        //allegro_exit();

    } // if !Pictures
    else
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.ALLOK << ") Sounddata loaded.")
        #endif // DEBUG

    } // if !Samples

    if(!BASS_Init(-1, 44100, 0, 0, 0))
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Couldn't initalize Soundsystem.")
        #endif // DEBUG
        allegro_message("Couldn't initalize Soundsystem.");

    }

    music = 0;
    music_channel = 0;

    sound_channel = 0;

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Soundclass opened.")
    #endif // DEBUG

} // Sound

Sound::~Sound()
{

    unload_datafile(Samples);

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Samples unloaded.")
    #endif // DEBUG

    BASS_Free();

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Soundclass closed.")
    #endif // DEBUG

} // ~Sound

void Sound::play_Music(std::string &Filename)
{
    BASS_StreamFree(music);

    if(music = BASS_StreamCreateFile(false, Filename.c_str(), 0, 0, BASS_SAMPLE_LOOP))
    {
        BASS_ChannelSetAttribute(music, BASS_ATTRIB_VOL, .2f);
        BASS_ChannelPlay(music, true);

    } // if mus = CreateStream

} // play_Music

void Sound::play_Sound(std::string &Filename)
{
    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Playing Sound: " << Filename.c_str())
    #endif // DEBUG
    sound = BASS_SampleLoad(false, Filename.c_str(), 0L, 0, 1, 0);
    int channel = BASS_SampleGetChannel(sound, false);
    BASS_ChannelPlay(channel, false);

} // play_Sound

void Sound::play_Memorysound()
{
    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Playing Memorysound.")
    #endif // DEBUG

    HSAMPLE mem_sample;
    mem_sample = BASS_SampleLoad(true, Samples[1].dat, 0L, Samples[1].size, 1, 0);

    int channel = BASS_SampleGetChannel(mem_sample, false);
    BASS_ChannelPlay(channel, false);

}
#endif // SOUND_CPP
