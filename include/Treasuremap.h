#ifndef TREASUREMAP_H
#define TREASUREMAP_H

#include <string>
#include <vector>

class Treasuremap
{
    public:
        Treasuremap(const std::string &Filename);
        ~Treasuremap();

    std::string find_Secret(const int &Position_x, const int &Position_y);

    private:

    void load_Map(const std::string &Mapname);

    struct Treasure
    {
        std::string Keyname;
        int Pos_x;
        int Pos_y;
        std::string Treasurename;
        int available;
    };

    std::vector<Treasure> Secret;

};

#endif // TREASUREMAP_H
