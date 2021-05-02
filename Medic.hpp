#pragma once
#include "Player.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <iostream>
#include <string>

namespace pandemic
{
    class Medic : public Player
    {
    public:
        Medic(Board &b, City c);
        virtual Player &drive(City c) override;
        virtual Player &fly_direct(City c) override;
        virtual Player &fly_charter(City c) override;
        virtual Player &fly_shuttle(City c) override;
        virtual Player &discover_cure(Color c) override;
        virtual Player &treat(City c) override;
        virtual std::string role() override;
    };
}