#pragma once
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <vector>
#include "City.hpp"
#include "Color.hpp"

namespace pandemic
{
    class Board
    {
    private:
        std::map<City, Color> color_per_city;
        std::map<City, std::set<City>> neighbors; //represent for each city a list of his neighbors with there color
        std::map<City, unsigned int> disease;     // represent for each city it's disease
        std::map<City, bool> research_station;    // represent for each city if it has a research station
        std::array<std::string, 48> cities_names;
        std::array<std::string, 4> colors_names;
        std::array<bool, 4> cure_discovered; // this array contains the cure that was discovered orderd by colors
        void addEdge(const City c, std::vector<City> v);

    public:
        Board();
        Color getColor(const City a) const;
        std::string getColorName(const Color a) const;
        bool hasNeighbor(const City orig, const City nei) const;
        bool hasResearchStation(const City c) const { return research_station.at(c); }
        void BuildResearchStation(const City c);
        void discover_cure(const Color c);
        bool getCure(const Color c) { return cure_discovered.at(size_t(c)); };
        std::string getName(const City c) const;
        unsigned int operator[](const City a) const;
        unsigned int &operator[](const City a);
        bool is_clean();
        void remove_cures();
        friend std::ostream &operator<<(std::ostream &out, const Board &b);
    };
}