#include <string>
#include <iostream>
#include <sstream>

#include "catch.hpp"
#include "Time.h"

using namespace std;

// här lägger ni era testfall.
// Jobba enligt TDD;
//  1. Lägg till testfall
//  2. Testa
//  3. Lägg till (minsta möjliga) implementation
//  4. Testa alla testfall
//  5. Refaktorera (skriv om) så att allt ser bra ut

TEST_CASE ("Default constructor")
{
    Time t;

    CHECK(t.hour() == 0);
    CHECK(t.minute() == 0);
    CHECK(t.second() == 0);
}

// the following line will halt the compilation process. Move it
// one test case at the time and then start creating your own test
// cases

TEST_CASE ( "Constructor with numeric arguments" )
{
    Time t{12,13,14};
    CHECK(t.hour() == 12);
    CHECK(t.minute() == 13);
    CHECK(t.second() == 14);
}

TEST_CASE ("Constructor with faulty argument")
{
    CHECK_THROWS( Time{41,0,0} );
    CHECK_THROWS( Time{0,99,0} );
    CHECK_THROWS( Time{0,0,99} );
}

TEST_CASE ("String constructor")
{
    Time t{"12:23:12"};
    CHECK(t.hour() == 12);
    CHECK(t.minute() == 23);
    CHECK(t.second() == 12);

    SECTION ("Throws as well")
    {
        CHECK_THROWS( Time{"02:11:74"} );
    }

}

TEST_CASE ("am or pm")
{
    Time t{12,12,31};
    CHECK_FALSE(t.is_am());
    Time t2{1,2,3};
    CHECK(t2.is_am());
}


TEST_CASE ("Convert to string" )
{
    CHECK( Time{12,12,12}.to_string()     ==    "12:12:12" );
    CHECK( Time{12, 1, 2}.to_string()     ==    "12:01:02" );
    CHECK( Time{14,33,12}.to_string(true) == "02:33:12 pm" );
}

TEST_CASE ("Conversion to string" )
{
    CHECK( string(Time{2,4,1}) == "02:04:01" );
}



TEST_CASE ("Output operator" )
{
    stringstream ss;
    SECTION("Simple output")
    {
        ss << Time{2,5,1};
        CHECK(ss.str() == "02:05:01");
    }

    SECTION("Chained output")
    {
        ss << Time{23,10,32} << "---";
        CHECK(ss.str() == "23:10:32---");
    }


    SECTION("Const time")
    {
        Time const t{23,23,23};
        ss << t;
        CHECK(ss.str() == "23:23:23");
    }

}

TEST_CASE ("Custom TEST")
{
//TEST FOR + OPERATOR
  Time T2{0,0,0};
  Time Ti {12, 0, 0};
/*
SECTION("TEST"){
  REQUIRE((T2+90).second() == 30);
}
*/

SECTION("+ OPERATOR"){
    Ti = (Ti+3600*24)+30;

    CHECK( Ti.hour() == 12);
    CHECK( Ti.minute() == 0);
    CHECK( Ti.second() == 30);

}

//TEST FOR - OPERATOR
SECTION("- OPERATOR"){
  Ti = {23, 55, 0};
  Ti = Ti - 125;

  CHECK( Ti.hour() == 23);
  CHECK( Ti.minute() == 52);
  CHECK( Ti.second() == 55);
}


SECTION("++ pre OPERATOR"){
  Ti = {23, 59, 59};
  ++Ti;

  CHECK( Ti.hour() == 0);
  CHECK( Ti.minute() == 0);
  CHECK( Ti.second() == 0);
}

SECTION("-- pre OPERATOR"){
  Ti = {00, 00, 00};
  --Ti;

  CHECK( Ti.hour() == 23);
  CHECK( Ti.minute() == 59);
  CHECK( Ti.second() == 59);

}

SECTION("++ post OPERATOR"){

    Ti = {23, 59, 59};
    T2 = Ti++;

    CHECK( T2.hour() == 23);
    CHECK( T2.minute() == 59);
    CHECK( T2.second() == 59);

    CHECK( Ti.hour() == 0);
    CHECK( Ti.minute() == 0);
    CHECK( Ti.second() == 0);

}


SECTION("-- post OPERATOR"){
  Ti = {0, 0, 0};
  T2=Ti--;

  CHECK( T2.hour() == 0);
  CHECK( T2.minute() == 0);
  CHECK( T2.second() == 0);

  CHECK( Ti.hour() == 23);
  CHECK( Ti.minute() == 59);
  CHECK( Ti.second() == 59);

}
SECTION("== OPERATOR"){
  Ti = {0, 0, 0};
  Time Tii{0, 0, 0};
  Time wrong{1,1,1};

  CHECK((Ti == Tii));
  CHECK((Ti == wrong)==false);
}

SECTION("< > OPERATOR"){
  Ti = {12, 30, 10};
  Time Tii{11, 23, 57};

  CHECK((Tii < Ti)==true);
  CHECK((Tii > Ti)!=true);

}

SECTION("!= OPERATOR"){
  Ti = {12, 30, 10};
  Time Tii{11, 23, 57};

  CHECK((Tii != Ti)==true);

}

SECTION("<= >= OPERATOR"){
  Ti = {12, 30, 10};
  Time Tii{11, 23, 57};

  CHECK((Tii <= Ti)==true);
  CHECK((Tii >= Ti)==!true);

}


SECTION("Inmatning"){

    Ti = {12, 30, 10};
    stringstream test;

    test << "23:10:10";
    test >> Ti;
    CHECK(Ti.to_string() == "23:10:10");
    CHECK(test.fail() == false);

    test << "60:32:10";
    test >> Ti;
    CHECK(test.fail() == true);
    CHECK(Ti.to_string() == "23:10:10");

}


}

#if 0
#endif
