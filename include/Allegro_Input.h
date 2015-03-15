#ifndef ALLEGRO_INPUT_H
#define ALLEGRO_INPUT_H

#include "Inputinterface.h"
#include "Clock.h"

class Allegro_Input: public Inputinterface
{
    public:
        Allegro_Input();
        ~Allegro_Input();

    // Keyboard
    bool read_Key();                            // read an Key
    bool read_Key(int Seconds);                 // read an Key until Seconds elapsed, false if no Key was pressed
    Key get_Key();                              // get the readed Key

    // Mouse
    bool hasMousemoved();
    MousePosition get_MousePosition();
    MouseButtonStatus get_MouseButton();

    void set_MilliSeconds(const int &Milliseconds); // set's the MilliSeconds to wait, must called before wait
    void set_Seconds(const int &Seconds);           // set's the Seconds to wait, must called before wait
    bool wait();

    protected:

    private:
    void needPoll();

    bool isMousePositionvalid;
    MousePosition lastMousePosition;

    Clock *inputClock;

}; // class Allegro_Input

#endif // ALLEGRO_INPUT_H
