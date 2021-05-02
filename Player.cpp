#include "Player.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Board.hpp"
#include <iostream>
#include <string>
#include <map>

using namespace std;

namespace pandemic
{
    Player &Player::take_card(City c)
    {
        cards.insert(c);
        return *this;
    }
    Player &Player::drive(City c)
    {
        bool f = (*game_board).hasNeighbor(current_city, c);
        if (!f)
        {
            string e;
            e.append((*game_board).getName(current_city)).append(" city and ").append((*game_board).getName(c)).append(" city are not neighbors");
            throw invalid_argument(e);
        }
        current_city = c;
        return *this;
    }
    Player &Player::fly_direct(City c)
    {
        set<City>::iterator i = cards.find(c);
        if (i != cards.end())
        {
            current_city = c;
            cards.erase(c);
            return *this;
        }
        throw invalid_argument("the player dosen't have " + (*game_board).getName(c) + " card"); // throw exeption if the player dosen't have this card
    }
    Player &Player::fly_charter(City c)
    {
        set<City>::iterator i = cards.find(current_city);
        if (i != cards.end())
        {
            cards.erase(current_city);
            current_city = c;
            return *this;
        }
        throw invalid_argument("the player dosen't have " + (*game_board).getName(current_city) + " card"); // throw exeption if the player dosen't have this card
    }
    Player &Player::fly_shuttle(City c)
    {
        if ((*game_board).hasResearchStation(current_city))
        {
            if ((*game_board).hasResearchStation(c))
            {
                current_city = c;
            }
            else
            {
                throw invalid_argument((*game_board).getName(c) + " does not have a research station");
            }
            return *this;
        }
        throw invalid_argument((*game_board).getName(current_city) + " does not have a research station");
    }
    Player &Player::build()
    {
        if (!((*game_board).hasResearchStation(current_city)))
        {
            set<City>::iterator i = cards.find(current_city);
            if (i != cards.end())
            {
                (*game_board).BuildResearchStation(current_city);
                cards.erase(current_city);
            }
            else
            {
                throw invalid_argument("the player dosen't have " + (*game_board).getName(current_city) + " card");
            }
        }
        return *this;
    }
    Player &Player::discover_cure(Color c)
    {
        if ((*game_board).hasResearchStation(current_city))
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
        throw invalid_argument((*game_board).getName(current_city) + "city does not a research station");
    }
    Player &Player::treat(City c)
    {
        if (current_city != c)
        {
            throw invalid_argument("you are not in " + (*game_board).getName(c) + " city");
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
    ostream &operator<<(std::ostream &out, const Player &p)
    {
        out << "{";
        for (const auto &card : p.cards)
        {
            out << (*p.game_board).getName(card) << ",";
        }
        out << "}";
        return out;
    }

}