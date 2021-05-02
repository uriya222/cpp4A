#pragma once
#include "Player.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <iostream>
#include <string>

namespace pandemic
{
    class Scientist : public Player
    {
    private:
        unsigned int n;

    public:
        Scientist(Board &b, City c, unsigned int num) : Player(b, c), n((num < 5) ? num : 5) {}
        virtual Player &discover_cure(Color c) override;
        virtual std::string role() override;
    };
}