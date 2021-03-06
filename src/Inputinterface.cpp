#ifndef INPUTINTERFACE_CPP
#define INPUTINTERFACE_CPP

#include "Inputinterface.h"

#include <string>
#include <iostream>

std::string Inputinterface::get_String()
{
    std::string Input;
    Key currentKey;
    currentKey.Scancode = 0;
    bool Done = false;

    do
    {
        if(read_Key())
        {
            currentKey = get_Key();

            if((currentKey.Scancode != SCAN_ESCAPE) && (currentKey.Scancode != SCAN_ENTER))   // Is the Key for the String?
            {
                Input += currentKey.Key;

            }
            else
            {
                Done = true;

            } // if SCAN_ESCAPE && SCAN_ENTER

        } // if readKey

    } // do
    while(!Done);

    return Input;

} // get_String

std::string Inputinterface::get_String(int Len)
{
    std::string Input;
    Key currentKey;
    currentKey.Scancode = 0;
    int charCount = 0;
    bool Done = false;

    if (Len <= 0)
    {
        Len = 1;

    } // if Len

    do
    {
        if(read_Key())
        {
            currentKey = get_Key();
            if((currentKey.Scancode != SCAN_ESCAPE) && (currentKey.Scancode != SCAN_ENTER))   // Is the Key for the String?
            {
                Input += currentKey.Key;
                charCount = Input.length();
                if(charCount >= Len)                                                    // Max. value of Char's readed
                {
                    Done = true;

                } // if charCount

            }
            else
            {
                Done = true;
            } // If SCAN_ESCAPE && SCAN_ENTER

        } // if readKey

    } // do
    while(!Done);

    return Input;

} // get_String(Len)

std::string Inputinterface::input_String()
{
    std::string Input;
    Key currentKey;
    currentKey.Scancode = 0;
    bool Done = false;

    do
    {
        if(read_Key())
        {
            currentKey = get_Key();
            if((currentKey.Scancode != SCAN_ESCAPE) && (currentKey.Scancode != SCAN_ENTER))
            {
                if(currentKey.Scancode == SCAN_BACKSPACE)
                {
                    if(Input.length() >= 1)                                                 // are Char's available to erase?
                    {
                        Input = Input.erase(Input.length()-1, 1);                           // Erase the last Char

                    } // if Input.length

                }
                else
                {
                    Input += currentKey.Key;

                } // If SCAN_BACKSPACE

            }
            else
            {
                Done = true;

            } // If SCAN_ESCAPE || SCAN_ENTER

        } // if readkey()

    } // do
    while(!Done);
    return Input;

} // input_String

std::string Inputinterface::input_String(int Len)
{
    std::string Input;
    Key currentKey;
    currentKey.Scancode = 0;
    int charCount = 0;
    bool Done = false;

    if (Len <= 0) // Set Len to a valid value
    {
        Len = 1;

    } // if Len

    do
    {
        if(read_Key())
        {
            currentKey = get_Key();
            if((currentKey.Scancode != SCAN_ESCAPE) && (currentKey.Scancode != SCAN_ENTER))
            {
                if(currentKey.Scancode == SCAN_BACKSPACE)
                {
                    if(Input.length() >= 1)
                    {
                        Input = Input.erase(Input.length()-1, 1);                           // Erase the last Char
                        charCount = Input.length();

                    } // if Input.length

                }
                else
                {
                    Input += currentKey.Key;
                    charCount = Input.length();
                    if(charCount >= Len)
                    {
                        Done = true;

                    } // If charCount

                } // If SCAN_BACKSPACE

            }
            else
            {
                Done = true;

            } // If SCAN_ESCAPE || SCAN_ENTER

        } // if readkey()

    } // do
    while(!Done);
    return Input;

} // input_String(Len)

#endif // INPUTINTERFACE_CPP

