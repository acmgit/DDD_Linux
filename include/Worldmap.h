#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <string>
#include <vector>

class Worldmap
{
    public:
        Worldmap(const std::string &Worldmapname);
        ~Worldmap();

        char get_Tile(const int Pos_x, const int Pos_y);
        int get_Columns();
        int get_Rows();

        void check_Coord(int &Pos_x, int &Pos_y);

    private:

        void read_Map(const std::string &Mapname);

    std::vector<std::string> Map;

    int Columns;
    int Rows;

}; // Worldmap

#endif // WORLDMAP_H
