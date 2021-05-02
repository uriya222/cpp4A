#include "OperationsExpert.hpp"
#include <iostream>
#include <string>

using namespace std;

namespace pandemic
{
    Player &OperationsExpert::build()
    {
        (*game_board).BuildResearchStation(current_city);
        return *this;
    }
    string OperationsExpert::role()
    {
        return "OperationsExpert";
    }
};