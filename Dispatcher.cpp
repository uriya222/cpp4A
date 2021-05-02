#include "Dispatcher.hpp"
#include <iostream>
#include <string>

using namespace std;

namespace pandemic
{
    Player &Dispatcher::fly_direct(City c)
    {
        if ((*game_board).hasResearchStation(current_city))
        {
            current_city = c;
            return *this;
        }
        set<City>::iterator i = cards.find(c);
        if (i != cards.end())
        {
            current_city = c;
            cards.erase(c);
            return *this;
        }
        throw invalid_argument("the player dosen't have " + (*game_board).getName(c) + " card and not in research station"); // throw exeption if the player dosen't have this card
    }
    string Dispatcher::role()
    {
        return "Dispatcher";
    }
};