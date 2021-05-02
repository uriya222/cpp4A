#pragma once
#include "Player.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <iostream>
#include <string>

namespace pandemic
{
    class Virologist : public Player
    {
    public:
        Virologist(Board &b, City c) : Player(b, c) {}
        virtual Player &treat(City c) override;
        virtual std::string role() override;
    };
}