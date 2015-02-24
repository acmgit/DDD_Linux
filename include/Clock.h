#ifndef CLOCK_H
#define CLOCK_H

#include <vector>
#include <time.h>


class Clock
{
    public:
        Clock();
        ~Clock();

        void setSeconds(const int Seconds);
        void setMiliSeconds(const int Miliseconds);

        bool wait();                // Returns true, if the time was come ...

    protected:
    private:

    timeval currTime;
    timeval Timer;

};

#endif // CLOCK_H
