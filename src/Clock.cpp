#ifndef CLOCK_CPP
#define CLOCK_CPP
#include "Clock.h"

#include <sys/time.h>

#ifdef DEBUG

#include "Logfile.h"

#endif // DEBUG

Clock::Clock()
{
    gettimeofday(&currTime, 0);
    gettimeofday(&Timer, 0);

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Clock opened.")
#endif // DEBUG

} // Clock

Clock::~Clock()
{

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Clock closed.")
#endif // DEBUG

} // ~Clock()

void Clock::setSeconds(const int &Seconds)
{
    gettimeofday(&currTime, 0);
    gettimeofday(&Timer, 0);

#ifdef DEBUG
    Log(Timer.tv_sec << " : Current Second")
#endif // DEBUG

    Timer.tv_sec = Timer.tv_sec + Seconds;

#ifdef DEBUG
    Log(Timer.tv_sec << " : to Second")
#endif

} // setSeconds

void Clock::setMiliSeconds(const int &Miliseconds)
{
    gettimeofday(&Timer, 0);
    Timer.tv_usec = Timer.tv_usec + Miliseconds;

} // setMiliseconds

bool Clock::wait()
{
    gettimeofday(&currTime, 0);                 // Set the time

    if((currTime.tv_usec >= Timer.tv_usec) && (currTime.tv_sec >= Timer.tv_sec))
    {
        return true;

    } // if Miliseconds && Seconds

    return false;
} // wait

#endif // CLOOCK_CPP
