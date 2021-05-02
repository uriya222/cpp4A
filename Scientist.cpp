#include "Scientist.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace pandemic
{
    Player &Scientist::discover_cure(Color c)
    {
        if ((*game_board).hasResearchStation(current_city))
        {
            size_t count = 0;
            vector<City> tmp;
            for (const auto &card : cards)
            {
                if ((*game_board).getColor(card) == c)
                {
                    tmp.push_back(card);
                    count++;
                }
                if (count == n)
                {
                    break;
                }
            }
            if (count == n)
            {
                (*game_board).discover_cure(c);
                for (const City x : tmp)
                {
                    cards.erase(x);
                }
            }
            else
            {
                throw invalid_argument("you have only " + to_string(count) + " " + (*game_board).getColorName(c) + " cards");
            }
            return *this;
        }
        throw invalid_argument((*game_board).getName(current_city) + "city does not a research station");
    }
    string Scientist::role()
    {
        return "Scientist";
    }
};