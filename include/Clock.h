#ifndef CLOCK_H
#define CLOCK_H

#include <vector>
#include <time.h>

#include "Clock_Interface.h"

class Clock: public Clock_Interface
{
    public:
        Clock();
        ~Clock();

        void setSeconds(const int &Seconds);
        void setMiliSeconds(const int &Miliseconds);
        bool wait();

    protected:
    private:

};

#endif // CLOCK_H
