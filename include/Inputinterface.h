#ifndef INPUTINTERFACE_H
#define INPUTINTERFACE_H

#include "Keyboardinterface.h"
#include "Mouseinterface.h"
#include <string>

class Inputinterface: public Keyboardinterface, public Mouseinterface
{
    public:
    virtual std::string get_String();                    // get the whole String, get back if pressed Enter or Escape
    virtual std::string get_String(int Len);             // get the whole String, get back, if pressed Enter, Escape or the Number of Len are entered
    virtual std::string input_String();                  // you can edit the String with Backspace, get back if pressed Enter or Escape
    virtual std::string input_String(int Len);           // you can edit the String with Backspace, get back if pressed Enter, Escape or the number of Len are entered

    protected:
    enum
    {
        SCAN_ESCAPE = 59,
        SCAN_ENTER = 67,
        SCAN_BACKSPACE = 63
    }; // enum SCAN_

}; // class Inputinterface

#endif // INPUTINTERFACE_H
