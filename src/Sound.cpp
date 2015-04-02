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

    BASS_ChannelPlay(music, true);
    BASS_ChannelSetAttribute(music, BASS_ATTRIB_VOL, Volume);

#ifdef DEBUG
    LogError();
#endif // DEBUG

} // play_Music

void Sound::play_Sound(const std::string &Filename)
{
    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Playing Sound: " << Filename.c_str())
    #endif // DEBUG
    sound = BASS_SampleLoad(false, Filename.c_str(), 0L, 0, 1, 0);

    HCHANNEL channel = BASS_SampleGetChannel(sound, false);
    BASS_ChannelPlay(channel, false);

#ifdef DEBUG
    LogError();
#endif // DEBUG

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

#ifdef DEBUG
    LogError();
#endif // DEBUG

} // play_Memorysound

void Sound::set_Globalvolume(const float &Volume)
{
    BASS_SetVolume(Volume);
    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Global Soundvolume setted to: " << Volume)
    #endif // DEBUG

#ifdef DEBUG
    LogError();
#endif // DEBUG

} // set_Globalvolume

void Sound::stop_Music()
{
    BASS_ChannelStop(music);

#ifdef DEBUG
    LogError();
#endif // DEBUG

} // stop_Music

void Sound::pause_Music()
{
    BASS_ChannelPause(music);

#ifdef DEBUG
    LogError();
#endif // DEBUG

} // pause_Music

void Sound::play_Music()
{
    BASS_ChannelPlay(music, false);

#ifdef DEBUG
    LogError();
#endif // DEBUG

} // play_Music

#ifdef DEBUG
void Sound::LogError()
{
    int Error = BASS_ErrorGetCode();
    switch(Error)
    {
        case BASS_ERROR_UNKNOWN:
        {
            Log("BASS_Error: unknown.")
            break;

        } // unknown

        case BASS_ERROR_MEM:
        {
            Log("BASS_Error: Memoryfailure.")
            break;

        } // Memoryfailure

        case BASS_ERROR_BUSY:
        {
            Log("BASS_Error: Busy.")
            break;

        } // Busy

        case BASS_ERROR_CREATE:
        {
            Log("BASS_Error: Fail to create.")
            break;

        } // Createfailure

        case BASS_ERROR_DEVICE:
        {
            Log("BASS_Error: Devicefailure.")
            break;

        } // Memoryfailure

        case BASS_ERROR_FORMAT:
        {
            Log("BASS_Error: Formatfailure.")
            break;

        } // Memoryfailure

        case BASS_ERROR_FILEFORM:
        {
            Log("BASS_Error: Fileformat.")
            break;

        }

        case BASS_ERROR_EMPTY:
        {
            Log("BASS_Error: Empty buffer.")
            break;

        }

        case BASS_ERROR_ENDED:
        {
            Log("BASS_Error: Ended.")
            break;

        }

        case BASS_ERROR_HANDLE:
        {
            Log("BASS_Error: Handle")
            break;

        }

        case BASS_ERROR_FILEOPEN:
        {
            Log("BASS_Error: File open")
            break;

        }

        case BASS_ERROR_ALREADY:
        {
            Log("BASS_Error: Already.")
            break;

        }

        case BASS_ERROR_BUFLOST:
        {
            Log("BASS_Error: Buffer lost.")
            break;

        }

        case BASS_ERROR_CODEC:
        {
            Log("BASS_Error: Codec.")
            break;

        }

        case BASS_ERROR_DECODE:
        {
            Log("BASS_Error: Decode.")
            break;

        }

        case BASS_ERROR_FREQ:
        {
            Log("BASS_Error: Frequency.")
            break;
        }

        case BASS_ERROR_ILLPARAM:
        {
            Log("BASS_Error: Illegal Parameter.")
            break;

        }

        case BASS_ERROR_ILLTYPE:
        {
            Log("BASS_Error: Illegal Typ.")
            break;

        }

        case BASS_ERROR_VERSION:
        {
            Log("BASS_Error: Version")
            break;

        }

        case BASS_ERROR_NOCHAN:
        {
            Log("BASS_Error: No Channel")
            break;

        }

        case 0:
        {
                break;
        }
        default:
        {
            Log("BASS_Error: " << Error)
            break;
        } // default

    } // switch Error
}
#endif // DEBUG

#endif // SOUND_CPP
