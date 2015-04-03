#ifndef TOWNSMAP_H
#define TOWNSMAP_H

#include <string>
#include <vector>

class Townsmap
{
    public:
        Townsmap(const std::string &Filename);
        virtual ~Townsmap();

        std::string find_Town(const int &Position_x, const int &Position_y);

    private:

    void load_Map(const std::string &Mapname);

    struct Enter
    {
        std::string Keyname;
        int Pos_x;
        int Pos_y;
        std::string Name;
    };

    std::vector<Enter> Citys;

};

#endif // TOWNSMAP_H
