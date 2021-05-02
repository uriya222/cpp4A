#pragma once
#include "Player.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <iostream>
#include <string>

namespace pandemic
{
    class Dispatcher : public Player
    {
    public:
        Dispatcher(Board &b, City c) : Player(b, c) {}
        virtual Player &fly_direct(City c) override;
        virtual std::string role() override;
    };
}