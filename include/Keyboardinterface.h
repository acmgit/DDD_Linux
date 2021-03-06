#ifndef KEYBOARDINTERFACE_H
#define KEYBOARDINTERFACE_H


class Keyboardinterface
{
    public:
        // Public Struct to get Key's
        struct Key
        {
            char Key;
            int Scancode;
            bool Shift;
            bool Strg;
            bool Alt;
        }; // Key
        virtual ~Keyboardinterface() {};

        virtual bool read_Key() = 0;         // Is a Key pressed?
        virtual Key get_Key() = 0;           // Ok, get the Key

}; // class Keyboardinterface

#endif // KEYBOARDINTERFACE_H
