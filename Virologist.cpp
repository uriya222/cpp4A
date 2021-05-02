#include "Virologist.hpp"
#include <iostream>
#include <string>

using namespace std;

namespace pandemic
{
    Player &Virologist::treat(City c)
    {
        if (c != current_city)
        {
            set<City>::iterator i = cards.find(c);
            if (i != cards.end())
            {
                cards.erase(c);
            }
            else
            {
                throw invalid_argument("the player dosen't have " + (*game_board).getName(c) + " card");
            }
        }
        if ((*game_board)[c] > 0)
        {
            Color city_color = (*game_board).getColor(c);
            if ((*game_board).getCure(city_color))
            {
                (*game_board)[c] = 0;
            }
            else
            {
                (*game_board)[c]--;
            }
            return *this;
        }
        throw invalid_argument("no more cubes remain in " + (*game_board).getName(c));
    }
    string Virologist::role()
    {
        return "Virologist";
    }
};