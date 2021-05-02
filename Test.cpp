#include "doctest.h"

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"

#include <string>
#include <vector>
#include <iostream>

using namespace pandemic;
using namespace std;

void take_cards(Player &p, vector<City> v)
{
    for (const City c : v)
    {
        p.take_card(c);
    }
}

TEST_CASE("check board operation")
{
    Board b;
    b[City::Bogota] = 5;
    b[City::SunFrancisco] = 2;
    b[City::Seoul] = 0;
    CHECK_EQ(b[City::SunFrancisco], 2);
    CHECK_EQ(b[City::Bogota], 5);
    const size_t num_fo_cities = 48;
    for (int CityInt = 0; CityInt < num_fo_cities; CityInt++)
    {
        City c = static_cast<City>(CityInt);
        if ((c != City::SunFrancisco) && (c != City::Bogota))
        {
            CHECK_EQ(b[c], 0);
        }
    }
    CHECK_FALSE(b.is_clean());
}
TEST_CASE("OperationsExpert player")
{
    Board b;
    b[City::Bogota] = 5;
    b[City::SunFrancisco] = 2;
    OperationsExpert o{b, City::Sydney};
    take_cards(o, {City::Sydney, City::LosAngeles, City::Miami});
    CHECK_NOTHROW(o.build().build());               //research station in sydney
    CHECK_NOTHROW(o.fly_charter(City::MexicoCity)); //throw sydney card
    CHECK_THROWS(o.fly_direct(City::Sydney));       //did not have sydney card
    CHECK_NOTHROW(o.build());                       // research station in Mexico City
    CHECK_NOTHROW(o.fly_shuttle(City::Sydney));
    CHECK_THROWS(o.discover_cure(Color::Yellow));
    take_cards(o, {City::Santiago, City::BuenosAires, City::Moscow});
    CHECK_THROWS(o.discover_cure(Color::Yellow)); // 4 yellow card
    o.take_card(City::Lagos);
    CHECK_NOTHROW(o.discover_cure(Color::Yellow)); //in a research station
    o.drive(City::LosAngeles).drive(City::SunFrancisco);
    o.treat(City::SunFrancisco);
    CHECK_EQ(b[City::SunFrancisco], 1);
    o.treat(City::SunFrancisco);
    CHECK_EQ(b[City::SunFrancisco], 0);
    CHECK_FALSE(b.is_clean());
    CHECK_THROWS(o.treat(City::SunFrancisco));
    CHECK_THROWS(o.treat(City::Bogota));     //not in bogota
    CHECK_THROWS(o.fly_direct(City::Miami)); // did not have miami card already used it
    o.take_card(City::Lima);
    o.fly_direct(City::Lima).drive(City::Bogota);
    CHECK_NOTHROW(o.treat(City::Bogota));
    CHECK_EQ(b[City::Bogota], 0);
    CHECK(b.is_clean());
    CHECK(o.role() == "OperationsExpert");
}
TEST_CASE("Dispatcher player")
{
    Board b;
    b[City::Moscow] = 5;
    b[City::HoChiMinhCity] = 2;
    Dispatcher d{b, City::Sydney};
    take_cards(d, {City::Sydney, City::Istanbul, City::Miami});
    CHECK_NOTHROW(d.build().build());              //research station in sydney
    CHECK_THROWS(d.fly_charter(City::MexicoCity)); //did not have sydney card
    CHECK_NOTHROW(d.fly_direct(City::Paris));      //research station in sydney and the player is Dispatcher
    CHECK_THROWS(d.fly_direct(City::Moscow));      // not in a research station nor has moscow card
    CHECK_THROWS(d.build());                       // did not have Paris card
    CHECK_THROWS(d.discover_cure(Color::Black));   // 1 black card
    take_cards(d, {City::Moscow, City::Delhi, City::Kolcata, City::HoChiMinhCity, City::Paris});
    CHECK_THROWS(d.discover_cure(Color::Black)); // 4 black cards
    CHECK_NOTHROW(d.build());                    //research station in paris
    d.take_card(City::Riyadh);
    CHECK_NOTHROW(d.discover_cure(Color::Black)); //in a research station, 5 black cards
    CHECK_THROWS(d.treat(City::Moscow));          //not in moscow
    d.fly_direct(City::Istanbul).drive(City::Moscow);
    CHECK_NOTHROW(d.treat(City::Moscow));
    CHECK_EQ(b[City::Moscow], 0);
    CHECK_FALSE(b.is_clean());
    CHECK_NOTHROW(d.fly_direct(City::HoChiMinhCity));
    CHECK_NOTHROW(d.treat(City::HoChiMinhCity).treat(City::HoChiMinhCity));
    CHECK_EQ(b[City::HoChiMinhCity], 0);
    CHECK(b.is_clean());
    CHECK(d.role() == "Dispatcher");
}

TEST_CASE("Scientist player 1")
{
    Board b;
    b[City::Madrid] = 5;
    b[City::Milan] = 2;
    Scientist s{b, City::Atlanta, 10}; //non useful Scientist
    take_cards(s, {City::Washington, City::NewYork, City::Chicago, City::Atlanta, City::London});
    CHECK_NOTHROW(s.build().build()); //research station in Atlanta
    CHECK_THROWS(s.fly_shuttle(City::MexicoCity));
    CHECK_THROWS(s.fly_charter(City::Madrid));  //did not have Madrid card
    CHECK_NOTHROW(s.fly_direct(City::NewYork)); //throw new york card
    CHECK_THROWS(s.fly_direct(City::Moscow));   // not in a research station nor has moscow card
    CHECK_THROWS(s.build());                    // did not have NewYork card
    s.drive(City::London);
    CHECK_NOTHROW(s.build()); //research station in London
    CHECK_NOTHROW(s.fly_shuttle(City::Atlanta).fly_shuttle(City::London));
    CHECK_THROWS(s.discover_cure(Color::Blue)); // 2 blue card
    take_cards(s, {City::Montreal, City::StPetersburg, City::Essen});
    CHECK_NOTHROW(s.discover_cure(Color::Blue)); //in London 5 blue cards
    CHECK_THROWS(s.treat(City::Madrid));         //not in madrid
    s.drive(City::Madrid);
    CHECK_NOTHROW(s.treat(City::Madrid));
    CHECK_EQ(b[City::Madrid], 0);
    CHECK_FALSE(b.is_clean());
    s.take_card(City::Madrid);
    s.fly_charter(City::Milan);
    CHECK_NOTHROW(s.treat(City::Milan));
    CHECK_EQ(b[City::Milan], 0);
    CHECK(b.is_clean());
    CHECK(s.role() == "Scientist");
}

TEST_CASE("Scientist player 2")
{
    Board b;
    b[City::Madrid] = 5;
    b[City::Milan] = 2;
    Scientist s{b, City::Atlanta, 3}; // useful Scientist
    take_cards(s, {City::Washington, City::NewYork, City::Chicago, City::Atlanta, City::London});
    CHECK_NOTHROW(s.build().build()); //research station in Atlanta
    CHECK_THROWS(s.fly_shuttle(City::MexicoCity));
    CHECK_THROWS(s.fly_charter(City::Madrid));  //did not have Madrid card
    CHECK_NOTHROW(s.fly_direct(City::NewYork)); //throw new york card
    CHECK_THROWS(s.fly_direct(City::Moscow));   // not in a research station nor has moscow card
    CHECK_THROWS(s.build());                    // did not have NewYork card
    s.drive(City::London);
    CHECK_NOTHROW(s.build()); //research station in London
    CHECK_NOTHROW(s.fly_shuttle(City::Atlanta).fly_shuttle(City::London));
    CHECK_THROWS(s.discover_cure(Color::Blue)); // 2 blue card
    s.drive(City::Essen);
    take_cards(s, {City::Essen});
    CHECK_THROWS(s.discover_cure(Color::Blue)); //not in research station
    s.drive(City::London);
    CHECK_NOTHROW(s.discover_cure(Color::Blue)); //in London 3 blue cards
    CHECK_THROWS(s.treat(City::Madrid));         //not in madrid
    s.drive(City::Madrid);
    CHECK_NOTHROW(s.treat(City::Madrid));
    CHECK_EQ(b[City::Madrid], 0);
    CHECK_FALSE(b.is_clean());
    s.take_card(City::Madrid);
    s.fly_charter(City::Milan);
    CHECK_NOTHROW(s.treat(City::Milan));
    CHECK_EQ(b[City::Milan], 0);
    CHECK(b.is_clean());
}

TEST_CASE("Researcher player")
{
    Board b;
    b[City::Madrid] = 5;
    b[City::Milan] = 2;
    Researcher r{b, City::Atlanta};
    take_cards(r, {City::Washington, City::NewYork, City::Chicago, City::Atlanta, City::London});
    CHECK_NOTHROW(r.build().build()); //research station in Atlanta
    CHECK_THROWS(r.fly_shuttle(City::MexicoCity));
    CHECK_THROWS(r.fly_charter(City::Madrid));  //did not have Madrid card
    CHECK_NOTHROW(r.fly_direct(City::NewYork)); //throw new york card
    CHECK_THROWS(r.fly_direct(City::Moscow));   // not in a research station nor has moscow card
    CHECK_THROWS(r.build());                    // did not have NewYork card
    r.drive(City::London);
    CHECK_NOTHROW(r.build()); //research station in London
    CHECK_NOTHROW(r.fly_shuttle(City::Atlanta).fly_shuttle(City::London));
    CHECK_THROWS(r.discover_cure(Color::Blue)); // 2 blue card
    r.drive(City::Essen);
    take_cards(r, {City::Montreal, City::StPetersburg, City::Essen});
    CHECK_NOTHROW(r.discover_cure(Color::Blue)); //not in research station but ok for Researcher player
    CHECK_THROWS(r.treat(City::Madrid));         //not in madrid
    r.drive(City::Paris).drive(City::Madrid);
    CHECK_NOTHROW(r.treat(City::Madrid));
    CHECK_EQ(b[City::Madrid], 0);
    CHECK_FALSE(b.is_clean());
    r.take_card(City::Madrid);
    r.fly_charter(City::Milan); //throw madrid card
    CHECK_NOTHROW(r.treat(City::Milan));
    CHECK_EQ(b[City::Milan], 0);
    CHECK(b.is_clean());
    CHECK(r.role() == "Researcher");
}

TEST_CASE("GeneSplicer player")
{
    Board b;
    b[City::Madrid] = 5;
    b[City::Milan] = 10;
    GeneSplicer g{b, City::Atlanta};
    take_cards(g, {City::Baghdad, City::NewYork, City::Johannesburg, City::Atlanta, City::London, City::Milan});
    CHECK_NOTHROW(g.build().build()); //research station in Atlanta
    CHECK_THROWS(g.fly_shuttle(City::MexicoCity));
    CHECK_THROWS(g.fly_charter(City::Madrid));  //did not have Madrid card
    CHECK_NOTHROW(g.fly_direct(City::NewYork)); //throw new york card
    CHECK_THROWS(g.fly_direct(City::Moscow));   // not in a research station nor has moscow card
    CHECK_THROWS(g.build());                    // did not have NewYork card
    g.drive(City::London);
    CHECK_NOTHROW(g.build()); //research station in London
    CHECK_NOTHROW(g.fly_shuttle(City::Atlanta).fly_shuttle(City::London).fly_direct(City::Milan));
    CHECK_NOTHROW(g.treat(City::Milan));
    CHECK_EQ(b[City::Milan], 9);
    g.drive(City::Essen).drive(City::London);
    CHECK_THROWS(g.discover_cure(Color::Blue)); // 2 blue card
    take_cards(g, {City::Montreal, City::Kolcata, City::Osaka});
    CHECK_NOTHROW(g.discover_cure(Color::Blue)); //in London 5 blue cards
    CHECK_THROWS(g.treat(City::Madrid));         //not in madrid
    g.drive(City::Madrid);
    CHECK_NOTHROW(g.treat(City::Madrid));
    CHECK_EQ(b[City::Madrid], 0);
    CHECK_FALSE(b.is_clean());
    g.take_card(City::Madrid);
    g.fly_charter(City::Milan);
    CHECK_NOTHROW(g.treat(City::Milan));
    CHECK_EQ(b[City::Milan], 0);
    CHECK(b.is_clean());
    CHECK(g.role() == "GeneSplicer");
}

TEST_CASE("Medic player")
{
    Board b;
    b[City::Madrid] = 5;
    b[City::LosAngeles] = 2;
    b[City::Cairo] = 100;
    b[City::Montreal] = 20;
    b[City::Chicago] = 7;
    b[City::Sydney] = 12;
    b[City::Shanghai] = 13;
    b[City::Tokyo] = 18;
    Medic m{b, City::Atlanta};
    take_cards(m, {City::Chicago, City::Istanbul, City::Milan, City::Paris, City::London, City::Essen});
    CHECK_THROWS(m.discover_cure(Color::Blue)); //not in research station
    m.drive(City::Chicago);
    CHECK_NOTHROW(m.build());                   //throw chicago card
    CHECK_THROWS(m.discover_cure(Color::Blue)); //4 blue cards
    m.take_card(City::StPetersburg);
    CHECK_NOTHROW(m.discover_cure(Color::Blue));
    m.take_card(City::Madrid);
    CHECK_NOTHROW(m.fly_direct(City::Madrid));
    CHECK_EQ(b[City::Madrid], 0);
    take_cards(m, {City::SaoPaulo, City::LosAngeles, City::Baghdad});
    m.drive(City::SaoPaulo);
    CHECK_NOTHROW(m.fly_charter(City::LosAngeles));
    CHECK_NOTHROW(m.treat(City::LosAngeles));
    CHECK_EQ(b[City::LosAngeles], 0);
    CHECK_NOTHROW(m.fly_charter(City::Khartoum));
    CHECK_THROWS(m.treat(City::Cairo)); //not in cairo
    m.drive(City::Cairo);
    CHECK_NOTHROW(m.treat(City::Cairo));
    CHECK_EQ(b[City::Cairo], 0);
    m.drive(City::Baghdad);
    CHECK_NOTHROW(m.build()); //research station in baghdad
    CHECK_NOTHROW(m.fly_shuttle(City::Chicago));
    CHECK_EQ(b[City::Chicago], 0);
    m.drive(City::Montreal);
    CHECK_EQ(b[City::Montreal], 0);
    take_cards(m, {City::Manila, City::Sydney, City::HoChiMinhCity, City::Jakarta, City::Bangkok, City::Osaka, City::Montreal});
    CHECK_NOTHROW(m.fly_charter(City::Sydney).build().discover_cure(Color::Red));
    CHECK_EQ(b[City::Sydney], 0);
    m.drive(City::Manila).drive(City::HongKong);
    take_cards(m, {City::HongKong, City::Tokyo});
    m.fly_charter(City::Shanghai);
    CHECK_EQ(b[City::Shanghai], 0);
    m.fly_direct(City::Tokyo);
    CHECK_EQ(b[City::Tokyo], 0);
    CHECK(b.is_clean());
    CHECK(m.role() == "Medic");
}

TEST_CASE("Scientist player 1")
{
    Board b;
    b[City::Madrid] = 5;
    b[City::Milan] = 2;
    Scientist s{b, City::Atlanta, 10}; //non useful Scientist
    take_cards(s, {City::Washington, City::NewYork, City::Chicago, City::Atlanta, City::London});
    CHECK_NOTHROW(s.build().build()); //research station in Atlanta
    CHECK_THROWS(s.fly_shuttle(City::MexicoCity));
    CHECK_THROWS(s.fly_charter(City::Madrid));  //did not have Madrid card
    CHECK_NOTHROW(s.fly_direct(City::NewYork)); //throw new york card
    CHECK_THROWS(s.fly_direct(City::Moscow));   // not in a research station nor has moscow card
    CHECK_THROWS(s.build());                    // did not have NewYork card
    s.drive(City::London);
    CHECK_NOTHROW(s.build()); //research station in London
    CHECK_NOTHROW(s.fly_shuttle(City::Atlanta).fly_shuttle(City::London));
    CHECK_THROWS(s.discover_cure(Color::Blue)); // 2 blue card
    take_cards(s, {City::Montreal, City::StPetersburg, City::Essen});
    CHECK_NOTHROW(s.discover_cure(Color::Blue)); //in London 5 blue cards
    CHECK_THROWS(s.treat(City::Madrid));         //not in madrid
    s.drive(City::Madrid);
    CHECK_NOTHROW(s.treat(City::Madrid));
    CHECK_EQ(b[City::Madrid], 0);
    CHECK_FALSE(b.is_clean());
    s.take_card(City::Madrid);
    s.fly_charter(City::Milan);
    CHECK_NOTHROW(s.treat(City::Milan));
    CHECK_EQ(b[City::Milan], 0);
    CHECK(b.is_clean());
    CHECK(s.role() == "Scientist");
}

TEST_CASE("Virologist player")
{
    Board b;
    b[City::Madrid] = 5;
    b[City::Milan] = 2;
    Virologist s{b, City::Atlanta};
    take_cards(s, {City::Washington, City::NewYork, City::Chicago, City::Atlanta, City::London});
    CHECK_NOTHROW(s.build().build()); //research station in Atlanta
    CHECK_THROWS(s.fly_shuttle(City::MexicoCity));
    CHECK_THROWS(s.fly_charter(City::Madrid));  //did not have Madrid card
    CHECK_NOTHROW(s.fly_direct(City::NewYork)); //throw new york card
    CHECK_THROWS(s.fly_direct(City::Moscow));   // not in a research station nor has moscow card
    CHECK_THROWS(s.build());                    // did not have NewYork card
    s.drive(City::London);
    CHECK_NOTHROW(s.build()); //research station in London
    CHECK_NOTHROW(s.fly_shuttle(City::Atlanta).fly_shuttle(City::London));
    CHECK_THROWS(s.discover_cure(Color::Blue)); // 2 blue card
    take_cards(s, {City::Montreal, City::StPetersburg, City::Essen});
    CHECK_NOTHROW(s.discover_cure(Color::Blue)); //in London 5 blue cards
    s.take_card(City::Madrid);
    CHECK_NOTHROW(s.treat(City::Madrid)); //not in madrid but Virologist
    CHECK_EQ(b[City::Madrid], 0);
    CHECK_FALSE(b.is_clean());
    s.take_card(City::Algiers).drive(City::Paris).drive(City::Algiers);
    s.fly_charter(City::Milan);
    CHECK_NOTHROW(s.treat(City::Milan));
    CHECK_EQ(b[City::Milan], 0);
    CHECK(b.is_clean());
    CHECK(s.role() == "Virologist");
}

TEST_CASE("FieldDoctor player")
{
    Board b;
    b[City::Madrid] = 5;
    b[City::Milan] = 10;
    b[City::Istanbul] = 2;
    FieldDoctor s{b, City::Atlanta};
    take_cards(s, {City::Washington, City::NewYork, City::Chicago, City::Atlanta, City::London});
    CHECK_NOTHROW(s.build().build()); //research station in Atlanta
    CHECK_THROWS(s.fly_shuttle(City::MexicoCity));
    CHECK_THROWS(s.fly_charter(City::Madrid));  //did not have Madrid card
    CHECK_NOTHROW(s.fly_direct(City::NewYork)); //throw new york card
    CHECK_THROWS(s.fly_direct(City::Moscow));   // not in a research station nor has moscow card
    CHECK_THROWS(s.build());                    // did not have NewYork card
    s.drive(City::London);
    CHECK_NOTHROW(s.build()); //research station in London
    CHECK_NOTHROW(s.fly_shuttle(City::Atlanta).fly_shuttle(City::London));
    CHECK_THROWS(s.discover_cure(Color::Blue)); // 2 blue card
    take_cards(s, {City::Montreal, City::StPetersburg, City::Essen});
    CHECK_NOTHROW(s.discover_cure(Color::Blue)); //in London 5 blue cards
    s.take_card(City::Madrid);
    CHECK_NOTHROW(s.treat(City::Madrid)); //not in madrid but FieldDoctor
    CHECK_EQ(b[City::Madrid], 0);
    CHECK_NOTHROW(s.fly_direct(City::Madrid)); // should have Madrid card
    s.take_card(City::Milan);
    CHECK_FALSE(b.is_clean());
    s.fly_direct(City::Milan);
    CHECK_NOTHROW(s.treat(City::Milan));
    CHECK_EQ(b[City::Milan], 0);
    CHECK_NOTHROW(s.treat(City::Istanbul)); //not in Istanbul but FieldDoctor
    CHECK_EQ(b[City::Istanbul], 1);
    CHECK_NOTHROW(s.treat(City::Istanbul)); //not in Istanbul but FieldDoctor
    CHECK_EQ(b[City::Istanbul], 0);
    CHECK(b.is_clean());
    CHECK(s.role() == "FieldDoctor");
}