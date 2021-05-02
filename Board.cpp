#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
namespace pandemic
{
    void Board::addEdge(const City c, vector<City> v)
    {
        for (size_t i = 0; i < v.size(); i++)
        {
            neighbors[c].insert(v.at(i));
        }
    }
    //initial cure_discovered
    Board::Board() : cure_discovered({false, false, false, false})
    {
        //insert colors
        const size_t num_fo_cities = 48;
        const size_t yellow = 12;
        const size_t black = 24;
        const size_t red = 36;
        for (int CityInt = 0; CityInt < num_fo_cities; CityInt++)
        {
            City c = static_cast<City>(CityInt);
            if (CityInt < yellow)
            {
                color_per_city[c] = Color::Blue;
            }
            else if (CityInt < black)
            {
                color_per_city[c] = Color::Yellow;
            }
            else if (CityInt < red)
            {
                color_per_city[c] = Color::Black;
            }
            else
            {
                color_per_city[c] = Color::Red;
            }
        }
        //insert neighbors
        addEdge(City::NewYork, {City::Madrid, City::London, City::Washington, City::Montreal});
        addEdge(City::Montreal, {City::Washington, City::Chicago, City::NewYork});
        addEdge(City::Chicago, {City::SunFrancisco, City::Atlanta, City::Montreal, City::MexicoCity, City::LosAngeles});
        addEdge(City::SunFrancisco, {City::LosAngeles, City::Chicago, City::Tokyo, City::Manila});
        addEdge(City::Atlanta, {City::Washington, City::Chicago, City::Miami});
        addEdge(City::Washington, {City::NewYork, City::Montreal, City::Atlanta, City::Miami});
        addEdge(City::London, {City::Madrid, City::Paris, City::NewYork, City::Essen});
        addEdge(City::Madrid, {City::London, City::Paris, City::NewYork, City::SaoPaulo, City::Algiers});
        addEdge(City::Paris, {City::Milan, City::Essen, City::London, City::Madrid, City::Algiers});
        addEdge(City::Milan, {City::Istanbul, City::Paris, City::Essen});
        addEdge(City::Essen, {City::Milan, City::Paris, City::London, City::StPetersburg});
        addEdge(City::StPetersburg, {City::Moscow, City::Istanbul, City::Essen});

        addEdge(City::MexicoCity, {City::LosAngeles, City::Miami, City::Bogota, City::Lima, City::Chicago});
        addEdge(City::Miami, {City::MexicoCity, City::Bogota, City::Atlanta, City::Washington});
        addEdge(City::LosAngeles, {City::SunFrancisco, City::Chicago, City::MexicoCity, City::Sydney});
        addEdge(City::Bogota, {City::Miami, City::MexicoCity, City::Lima, City::BuenosAires, City::SaoPaulo});
        addEdge(City::Lima, {City::Bogota, City::MexicoCity, City::Santiago});
        addEdge(City::Santiago, {City::Lima});
        addEdge(City::BuenosAires, {City::Bogota, City::SaoPaulo});
        addEdge(City::SaoPaulo, {City::Madrid, City::Lagos, City::BuenosAires, City::Bogota});
        addEdge(City::Lagos, {City::SaoPaulo, City::Kinshasa, City::Khartoum});
        addEdge(City::Khartoum, {City::Kinshasa, City::Johannesburg, City::Lagos, City::Cairo});
        addEdge(City::Kinshasa, {City::Lagos, City::Khartoum, City::Johannesburg});
        addEdge(City::Johannesburg, {City::Khartoum, City::Kinshasa});

        addEdge(City::Moscow, {City::Tehran, City::StPetersburg, City::Istanbul});
        addEdge(City::Istanbul, {City::Moscow, City::StPetersburg, City::Milan, City::Algiers, City::Cairo, City::Baghdad});
        addEdge(City::Algiers, {City::Madrid, City::Paris, City::Istanbul, City::Cairo});
        addEdge(City::Cairo, {City::Algiers, City::Istanbul, City::Baghdad, City::Riyadh, City::Khartoum});
        addEdge(City::Baghdad, {City::Tehran, City::Istanbul, City::Cairo, City::Riyadh, City::Karachi});
        addEdge(City::Tehran, {City::Moscow, City::Baghdad, City::Karachi, City::Delhi});
        addEdge(City::Riyadh, {City::Karachi, City::Baghdad, City::Cairo});
        addEdge(City::Karachi, {City::Delhi, City::Tehran, City::Baghdad, City::Riyadh, City::Mumbai});
        addEdge(City::Delhi, {City::Kolcata, City::Chennai, City::Mumbai, City::Karachi, City::Tehran});
        addEdge(City::Mumbai, {City::Karachi, City::Delhi, City::Chennai});
        addEdge(City::Kolcata, {City::Delhi, City::Chennai, City::Bangkok, City::HongKong});
        addEdge(City::Chennai, {City::Mumbai, City::Delhi, City::Kolcata, City::Bangkok, City::Jakarta});

        addEdge(City::Beijing, {City::Shanghai, City::Seoul});
        addEdge(City::Seoul, {City::Tokyo, City::Beijing, City::Shanghai});
        addEdge(City::Tokyo, {City::Seoul, City::Shanghai, City::Osaka, City::SunFrancisco});
        addEdge(City::HongKong, {City::Shanghai, City::Taipei, City::Manila, City::HoChiMinhCity, City::Bangkok, City::Kolcata});
        addEdge(City::Shanghai, {City::Beijing, City::Seoul, City::Tokyo, City::Taipei, City::HongKong});
        addEdge(City::Taipei, {City::Osaka, City::Shanghai, City::HongKong, City::Manila});
        addEdge(City::Osaka, {City::Tokyo, City::Taipei});
        addEdge(City::Bangkok, {City::HongKong, City::HoChiMinhCity, City::Jakarta, City::Chennai, City::Kolcata});
        addEdge(City::Jakarta, {City::Chennai, City::Bangkok, City::HoChiMinhCity, City::Sydney});
        addEdge(City::HoChiMinhCity, {City::Jakarta, City::Bangkok, City::HongKong, City::Manila});
        addEdge(City::Manila, {City::HongKong, City::HoChiMinhCity, City::Taipei, City::Sydney, City::SunFrancisco});
        addEdge(City::Sydney, {City::Jakarta, City::Manila, City::LosAngeles});

        //initial disease to 0
        for (int CityInt = 0; CityInt < num_fo_cities; CityInt++)
        {
            City c = static_cast<City>(CityInt);
            disease[c] = 0;
        }
        //initial research station to false
        for (int CityInt = 0; CityInt < num_fo_cities; CityInt++)
        {
            City c = static_cast<City>(CityInt);
            research_station[c] = false;
        }
        //initial cities names
        cities_names = {
            "NewYork", "Montreal", "Chicago", "SunFrancisco", "Atlanta", "Washington", "London", "Madrid", "Paris", "Milan", "Essen", "ST_Petersburg",
            "MexicoCity", "Miami", "LosAngeles", "Bogota", "Lima", "Santiago", "BuenosAires", "SaoPaulo", "Lagos", "Khartoum", "Kinshasa", "Johannesburg",
            "Moscow", "Istanbul", "Algiers", "Cairo", "Baghdad", "Tehran", "Riyadh", "Karachi", "Delhi", "Mumbai", "Kolcata", "Chennai",
            "Beijing", "Seoul", "Tokyo", "HongKong", "Shanghai", "Taipei", "Osaka", "Bangkok", "Jakarta", "HoChiMinhCity", "Manila", "Sydney"};
        //initial colors names
        colors_names = {"Blue", "Yellow", "Black", "Red"};
    }

    Color Board::getColor(const City a) const
    {
        return color_per_city.at(a);
    }
    string Board::getColorName(const Color a) const
    {
        return colors_names.at(size_t(a));
    }
    void Board::discover_cure(const Color c)
    {
        size_t place = (size_t)(c);
        cure_discovered.at(place) = true;
    }
    void Board::remove_cures(){
        cure_discovered.fill(false);
    }
    bool Board::hasNeighbor(const City orig, const City nei) const
    {
        bool flag = false;
        if (neighbors.at(orig).find(nei) != neighbors.at(orig).end())
        {
            flag = true;
        }
        return flag;
    }
    string Board::getName(City c) const
    {
        size_t place = (size_t)(c);
        return cities_names.at(place);
    }
    void Board::BuildResearchStation(const City c)
    {
        research_station[c] = true;
    }
    unsigned int Board::operator[](const City a) const
    {
        return disease.at(a);
    }
    unsigned int &Board::operator[](const City a)
    {
        return disease[a];
    }
    bool Board::is_clean()
    {
        for (const auto &item : disease)
        {
            if (item.second != 0)
            {
                return false;
            }
        }
        return true;
    }
    ostream &operator<<(ostream &out, const Board &b)
    {
        const size_t num_fo_cities = 48;
        const size_t s = 8;
        out << "  \tCity"
            << "\tlevel of disease"
            << "\tresearch station" << endl;
        out << "----------------------------------------------------------" << endl;
        for (size_t CityInt = 0; CityInt < num_fo_cities; CityInt++)
        {
            City c = static_cast<City>(CityInt);
            out << to_string(CityInt) << ".\t";
            string name = b.getName(c);
            if (name.size() >= s)
            {
                name.append("\t");
            }
            else
            {
                name.append("\t\t");
            }
            out << name << b[c] << "\t\t";
            out << boolalpha << b.hasResearchStation(c) << endl;
        }
        out << endl
            << "----------------------------------------------------------" << endl;
        out << "Cure that discovered:" << endl;
        out << "\tBlue\tYellow\tBlack\tRed" << endl;
        size_t place = 0;
        size_t tmp2 = 0;
        array<string, 2> v = {"no", "yes"};
        for (size_t i = 0; i < b.cure_discovered.size(); i++)
        {
            tmp2 = (size_t)b.cure_discovered.at(place);
            out << "\t" << v.at(tmp2);
            place++;
        }
        out << endl
            << "----------------------------------------------------------" << noboolalpha << endl;
        return out;
    }
}
