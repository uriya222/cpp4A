#pragma once
#include "Player.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <iostream>
#include <string>

namespace pandemic
{
    class Researcher : public Player
    {
    public:
        Researcher(Board &b, City c) : Player(b, c) {}
        virtual Player &discover_cure(Color c) override;
        virtual std::string role() override;
    };
}