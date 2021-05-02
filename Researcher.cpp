#include "Researcher.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace pandemic
{
    Player &Researcher::discover_cure(Color c)
    {
        size_t count = 0;
        const size_t limit = 5;
        array<City, limit> tmp = {};
        for (const auto &card : cards)
        {
            if ((*game_board).getColor(card) == c)
            {
                tmp.at(count) = card;
                count++;
            }
            if (count == limit)
            {
                break;
            }
        }
        if (count == limit)
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
    string Researcher::role()
    {
        return "Researcher";
    }
};