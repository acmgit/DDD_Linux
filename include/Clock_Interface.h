#ifndef CLOCK_INTERFACE_H
#define CLOCK_INTERFACE_H

#include <time.h>

class Clock_Interface
{
    public:
        Clock_Interface() {}
        virtual ~Clock_Interface() {}

        virtual void setSeconds(const int &Seconds) = 0;
        virtual void setMiliSeconds(const int &Miliseconds) = 0;
        virtual bool wait() = 0;

    protected:

        timeval currTime;
        timeval Timer;

    private:
};

#endif // CLOCK_INTERFACE_H
