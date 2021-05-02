#include "GeneSplicer.hpp"
#include <iostream>
#include <string>

using namespace std;

namespace pandemic
{
    Player &GeneSplicer::discover_cure(Color c)
    {
        if ((*game_board).hasResearchStation(current_city))
        {
            const size_t limit = 5;
            if (cards.size() >= limit)
            {
                size_t count = 0;
                (*game_board).discover_cure(c);
                auto itr_fifth = cards.begin();
                while (count < limit)
                {
                    itr_fifth++;
                    count++;
                }
                cards.erase(cards.begin(), itr_fifth);
            }
            else
            {
                throw invalid_argument("you have only " + to_string(cards.size()) + " cards");
            }
            return *this;
        }
        throw invalid_argument((*game_board).getName(current_city) + "city does not a research station");
    }
    string GeneSplicer::role()
    {
        return "GeneSplicer";
    }
};