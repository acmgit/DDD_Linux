#include "include/UniText.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#ifdef DEBUG

#include "include/Logfile.h"

#endif // DEBUG
// Opens the Languagefile and initalise the Map
UniText::UniText(const std::string &Textfile)
{

    ReadFile(Textfile);

    //ctor
}

UniText::~UniText()
{
    //dtor
}

// Opens a new Languagefile and initalise the Map new
void UniText::LoadNewText(const std::string &Textfile)
{

    Translate.clear();
    ReadFile(Textfile);

} // LoadNewText()


// Returns the Languagestring below [Key]. Returns the Key, if no Key found.
std::string UniText::Print(const std::string &Key)
{
    std::map<std::string, std::string>::iterator i;

    i = Translate.begin();

#ifdef DEBUG
    Log("Print " << Key.c_str())
#endif // DEBUG

    i = Translate.find(Key.c_str());

    if(i != Translate.end())
    {
        return i->second;
    }
    else
    {
        return Key;
    }

} // Print(Key)


// Opens the Languagefile, read it and fills the Map.
void UniText::ReadFile(const std::string &Textfile)
{
    std::ifstream File(Textfile.c_str());

    if(File.is_open())
    {
        std::string TransText;
        std::string KeyText;

        while(File.good())
        {
            std::getline(File, KeyText);

            if((KeyText.find("[") != KeyText.npos) && (KeyText.find("]") != KeyText.npos))
            {
                std::getline(File, TransText);
                Translate.insert(std::pair<std::string, std::string>(KeyText, TransText));

#ifdef DEBUG
                Log("Add Key:")
                Log(KeyText.c_str())
                Log(TransText.c_str())
#endif // DEBUG
            }
        }

        File.close();
    }
    else
    {
        std::string Err = "Can't open File: " + Textfile;
        throw std::runtime_error(Err);
    }
} // ReadFile(Textfile)

