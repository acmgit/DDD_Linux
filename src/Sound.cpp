#ifndef SOUND_CPP
#define SOUND_CPP

#include <allegro/system.h>

#include "Sound.h"
#include "bass.h"
#include <string>

#ifdef DEBUG
#include "Logfile.h"
#endif // DEBUG

Sound::Sound()
{

    if(!BASS_Init(-1, 44100, 0, 0, 0))
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Couldn't initalize Soundsystem.")
        #endif // DEBUG
        allegro_message("Couldn't initalize Soundsystem.");

    } // if !BASS_Init

    music = 0;

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Soundclass opened.")
    #endif // DEBUG

} // Sound

Sound::~Sound()
{

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Samples unloaded.")
    #endif // DEBUG

    BASS_Free();

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Soundclass closed.")
    #endif // DEBUG

} // ~Sound

void Sound::stream_Music(const std::string &Filename, const float &Volume)
{
    BASS_StreamFree(music);

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Streaming File: " << Filename.c_str() << " @ Volume: " << Volume)
    #endif // DEBUG

    music = BASS_StreamCreateFile(false, Filename.c_str(), 0, 0, BASS_SAMPLE_LOOP);

    if(music != 0)
    {
        BASS_ChannelSetAttribute(music, BASS_ATTRIB_VOL, Volume);
        BASS_ChannelPlay(music, true);

    } // if mus != 0

} // play_Music

void Sound::play_Sound(const std::string &Filename)
{
    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Playing Sound: " << Filename.c_str())
    #endif // DEBUG
    sound = BASS_SampleLoad(false, Filename.c_str(), 0L, 0, 1, 0);

    HCHANNEL channel = BASS_SampleGetChannel(sound, false);
    BASS_ChannelPlay(channel, false);

} // play_Sound

void Sound::play_Memorysound(DATAFILE *MemSound, const int &Index, const float &Volume)
{
    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Playing Memorysound.")
    #endif // DEBUG

    HSAMPLE mem_sample;
    mem_sample = BASS_SampleLoad(true, MemSound[Index].dat, 0L, MemSound[Index].size, 1, 0);

    HCHANNEL channel = BASS_SampleGetChannel(mem_sample, false);
    BASS_ChannelSetAttribute(mem_sample, BASS_ATTRIB_VOL, Volume);

    BASS_ChannelPlay(channel, false);

} // play_Memorysound

void Sound::set_Globalvolume(const float &Volume)
{
    BASS_SetVolume(Volume);
    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Global Soundvolume setted to: " << Volume)
    #endif // DEBUG

} // set_Globalvolume

void Sound::stop_Music()
{
    BASS_ChannelStop(music);

} // stop_Music

void Sound::pause_Music()
{
    BASS_ChannelPause(music);

} // pause_Music

void Sound::play_Music()
{
    BASS_ChannelPlay(music, false);

} // play_Music

#endif // SOUND_CPP
