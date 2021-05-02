#pragma once
#include "City.hpp"
#include "Color.hpp"
#include "Board.hpp"
#include <iostream>
#include <string>
#include <set>

namespace pandemic
{
    class Player
    {
    protected:
        City current_city;
        std::set<City> cards;
        Board *game_board;

    public:
        Player(Board &b, City c) : current_city(c), game_board(&b) {}
        Player &take_card(City c);
        virtual Player &drive(City c);
        virtual Player &fly_direct(City c);
        virtual Player &fly_charter(City c);
        virtual Player &fly_shuttle(City c);
        virtual Player &build();
        virtual Player &discover_cure(Color c);
        virtual Player &treat(City c);
        virtual std::string role() = 0;
        friend std::ostream &operator<<(std::ostream &out, const Player &p);
    };

}