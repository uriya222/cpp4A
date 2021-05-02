#pragma once
#include "Player.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <iostream>
#include <string>

namespace pandemic
{
    class OperationsExpert : public Player
    {
    public:
        OperationsExpert(Board &b, City c) : Player(b, c) {}
        virtual Player &build() override;
        virtual std::string role() override;
    };
}