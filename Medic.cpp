#include "Medic.hpp"
#include <iostream>
#include <string>

using namespace std;

namespace pandemic
{
    Medic::Medic(Board &b, City c) : Player(b, c)
    {
        Color city_color = (*game_board).getColor(c);
        if ((*game_board).getCure(city_color))
        {
            (*game_board)[c] = 0;
        }
    }
    Player &Medic::drive(City c)
    {
        Player::drive(c);
        Color city_color = (*game_board).getColor(c);
        if ((*game_board).getCure(city_color))
        {
            (*game_board)[c] = 0;
        }
        return *this;
    }
    Player &Medic::fly_direct(City c)
    {
        Player::fly_direct(c);
        Color city_color = (*game_board).getColor(c);
        if ((*game_board).getCure(city_color))
        {
            (*game_board)[c] = 0;
        }
        return *this;
    }
    Player &Medic::fly_charter(City c)
    {
        Player::fly_charter(c);
        Color city_color = (*game_board).getColor(c);
        if ((*game_board).getCure(city_color))
        {
            (*game_board)[c] = 0;
        }
        return *this;
    }
    Player &Medic::fly_shuttle(City c)
    {
        Player::fly_shuttle(c);
        Color city_color = (*game_board).getColor(c);
        if ((*game_board).getCure(city_color))
        {
            (*game_board)[c] = 0;
        }
        return *this;
    }
    Player &Medic::discover_cure(Color c)
    {
        Player::discover_cure(c);
        if ((*game_board)[current_city] > 0)
        {
            (*game_board)[current_city] = 0;
        }
        return *this;
    }
    Player &Medic::treat(City c)
    {
        if (current_city != c)
        {
            throw invalid_argument("you are not in " + (*game_board).getName(c) + " city");
        }
        if ((*game_board)[c] > 0)
        {
            (*game_board)[c] = 0;
            return *this;
        }
        throw invalid_argument("no more cubes remain in " + (*game_board).getName(c));
    }
    string Medic::role()
    {
        return "Medic";
    }
};