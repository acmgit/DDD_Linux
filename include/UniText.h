#ifndef UNITEXT_H
#define UNITEXT_H

#include <map>
#include <string>
#include <sstream>

class UniText
{
    private:
        std::map<std::string, std::string> Translate;

    public:
        UniText(const std::string &Textfile);                                                   // Opens a Languagefile, throws an Exception, if file can't open
        ~UniText();

        void LoadNewText(const std::string &Textfile);                                          // Changes the Languagefile
        std::string Print(const std::string &Key);                                              // Translates the Key to Text. Returns the Key, if no Text found.

        template <class X>
        void Replace(std::string &Text, const std::string &Pattern, const X &Value);            // Replace all Patterns to Value

    protected:
    private:
        void ReadFile(const std::string &Textfile);                                             // Read a Languagefile, throws an Exception, if file can't open

};

// Replace all Patterns to Value in the String.
template <class X>
void UniText::Replace(std::string &Text, const std::string &Pattern, const X &Value)
{
    size_t Pos = Text.find(Pattern);
    std::stringstream Par;
    Par << Value;
    std::string SValue = Par.str();

    while(Pos != std::string::npos)
    {
        Text.replace(Pos, Pattern.length(), SValue);
        Pos = Text.find(Pattern, Pos + SValue.length());
    }
} // Replace


#endif // UNITEXT_H
