#include "FieldDoctor.hpp"
#include <iostream>
#include <string>

using namespace std;

namespace pandemic
{
    Player &FieldDoctor::treat(City c)
    {
        if ((c == current_city) || (*game_board).hasNeighbor(current_city, c))
        {
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
        throw invalid_argument((*game_board).getName(current_city) + " and " + (*game_board).getName(c) + " are not neighbors");
    }
    string FieldDoctor::role()
    {
        return "FieldDoctor";
    }
};