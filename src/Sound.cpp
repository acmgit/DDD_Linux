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
    BASS_ChannelSlideAttribute(music, BASS_ATTRIB_VOL, Volume, 50);

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
    std::string Err;
    Err = "BASS_Error: ";

    switch(Error)
    {
        case BASS_ERROR_MEM:
        {
            Log(Err.c_str() << " Memory error.")
            break;

        } // Memoryfailure

        case BASS_ERROR_FILEOPEN:
        {
            Log(Err.c_str() << " Can't open the file.")
            break;

        } // Fileopen

        case BASS_ERROR_DRIVER:
        {
            Log(Err.c_str() << " Can't find a free/valid driver.")
            break;

        } // Driver

        case BASS_ERROR_BUFLOST:
        {
            Log(Err.c_str() << " The sample buffer was lost.")
            break;

        } // Bufflost

        case BASS_ERROR_HANDLE:
        {
            Log(Err.c_str() << " Invalid handle.")
            break;

        } // Handle

        case BASS_ERROR_FORMAT:
        {
            Log(Err.c_str() << " Unsupported sample format.")
            break;

        } // Format

        case BASS_ERROR_POSITION:
        {
            Log(Err.c_str() << " Invalid playback position.")
            break;

        } // Position

        case BASS_ERROR_INIT:
        {
            Log(Err.c_str() << " BASS_Init has not been successfully called.")
            break;

        } // Init

        case BASS_ERROR_START:
        {
            Log(Err.c_str() << " BASS_Start has not been successfully called.")
            break;

        } // Start

        case BASS_ERROR_ALREADY:
        {
            Log(Err.c_str() << " Already initialized/paused/whatever.")
            break;

        } // Already

        case BASS_ERROR_NOCHAN:
        {
            Log(Err.c_str() << " Can't get a free channel.")
            break;

        } // Nochan

        case BASS_ERROR_ILLTYPE:
        {
            Log(Err.c_str() << " An illegal type was specified.")
            break;

        } // Illtype

        case BASS_ERROR_ILLPARAM:
        {
            Log(Err.c_str() << " An illegal parameter was specified.")
            break;

        } // Illparam

        case BASS_ERROR_NO3D:
        {
            Log(Err.c_str() << " No 3D support.")
            break;

        } // No3d

        case BASS_ERROR_NOEAX:
        {
            Log(Err.c_str() << " No EAX support.")
            break;

        } // Noeax

        case BASS_ERROR_DEVICE:
        {
            Log(Err.c_str() << " Illegal device number.")
            break;

        } // Device

        case BASS_ERROR_NOPLAY:
        {
            Log(Err.c_str() << " Not playing.")
            break;

        } // Noplay

        case BASS_ERROR_FREQ:
        {
            Log(Err.c_str() << " Illegal sample rate.")
            break;

        } // Freq

        case BASS_ERROR_NOTFILE:
        {
            Log(Err.c_str() << " The stream is not a file stream.")
            break;

        } // Notfile

        case BASS_ERROR_NOHW:
        {
            Log(Err.c_str() << " No hardware voices available.")
            break;

        } // Nohw

        case BASS_ERROR_EMPTY:
        {
            Log(Err.c_str() << " The MOD music has no sequence data.")
            break;

        } // Empty

        case BASS_ERROR_NONET:
        {
            Log(Err.c_str() << " No internet connection could be opened.")
            break;

        } // Nonet

        case BASS_ERROR_CREATE:
        {
            Log(Err.c_str() << " Couldn't create the file.")
            break;

        } // Create

        case BASS_ERROR_NOFX:
        {
            Log(Err.c_str() << " Effects are not available.")
            break;

        } // Nofx

        case BASS_ERROR_NOTAVAIL:
        {
            Log(Err.c_str() << " Requested data is not available.")
            break;

        } // Notavail

        case BASS_ERROR_DECODE:
        {
            Log(Err.c_str() << " The channel is a 'decoding channel'.")
            break;

        } // Decode

        case BASS_ERROR_DX:
        {
            Log(Err.c_str() << " A sufficient DirectX version is not installed.")
            break;

        } // Dx

        case BASS_ERROR_TIMEOUT:
        {
            Log(Err.c_str() << "Connection timedout.")
            break;

        } // Timeout

        case BASS_ERROR_FILEFORM:
        {
            Log(Err.c_str() << " Unsupported file format.")
            break;

        } // Fileform

        case BASS_ERROR_SPEAKER:
        {
            Log(Err.c_str() << " Unavailable speaker.")
            break;

        } // Speaker

        case BASS_ERROR_VERSION:
        {
            Log(Err.c_str() << " Invalid BASS version (used by add-ons).")
            break;

        } // Version

        case BASS_ERROR_CODEC:
        {
            Log(Err.c_str() << " Codec is not available/supported.")
            break;

        } // Codec

        case BASS_ERROR_ENDED:
        {
            Log(Err.c_str() << " The channel/file has ended.")
            break;

        } // Ended

        case BASS_ERROR_BUSY:
        {
            Log(Err.c_str() << " The device is busy (eg. in \"exclusive\" use by another process) .")
            break;

        } // Busy


        case BASS_ERROR_UNKNOWN:
        {
            Log(Err.c_str() << " Some other mystery error.")
            break;

        } // Unknown

        case 0:
        {
                break;
        }

        default:
        {
            Log(Err.c_str() << " " << Error)
            break;
        } // default

    } // switch Error
}
#endif // DEBUG

#endif // SOUND_CPP
