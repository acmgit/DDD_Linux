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

        void set_Seconds(const int &Seconds);                   // this Function or the set_MilliSeconds must be called before wait
        void set_MilliSeconds(const int &Milliseconds);
        bool wait();

    protected:
    private:

};

#endif // CLOCK_H
