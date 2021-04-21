  
#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>


using namespace ariel;
using namespace std;

ifstream units_file{"units.txt"};


TEST_CASE("ilegal inputs constructor"){

    NumberWithUnits::read_units(units_file);

    CHECK_THROWS(NumberWithUnits(30,"l"));
    CHECK_THROWS(NumberWithUnits(30,"cl"));
    CHECK_THROWS(NumberWithUnits(30,"KM"));
    CHECK_THROWS(NumberWithUnits(30,"Km"));
    CHECK_THROWS(NumberWithUnits(30,"usd"));
    CHECK_THROWS(NumberWithUnits(30,"ils"));

}

TEST_CASE("equal operator!!! before all tests"){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{2, "km"};
    NumberWithUnits b{300, "m"};

    NumberWithUnits _h{30, "hour"};
    NumberWithUnits _min{30, "min"};

    CHECK(a==NumberWithUnits(2,"km"));
    CHECK_EQ(a, NumberWithUnits(2000, "m"));
    CHECK_EQ(a, NumberWithUnits(200000, "cm"));

    CHECK_EQ(_h, NumberWithUnits(30, "hour"));
    CHECK_EQ(_h, NumberWithUnits(30*60, "min"));
    CHECK_EQ(_h, NumberWithUnits(30*60*60, "sec"));
}

TEST_CASE("unary operator"){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{2, "km"};
    NumberWithUnits b{300, "m"};

    NumberWithUnits _h{30, "hour"};
    NumberWithUnits _min{30, "min"};

    CHECK_EQ(+a, a);
    CHECK_EQ(-a, NumberWithUnits(-2, "km"));
    CHECK_EQ(a, NumberWithUnits(-2000, "m"));
    CHECK_EQ(-a, NumberWithUnits(-200000, "cm"));

    CHECK_EQ(_h, +_h);
    CHECK_EQ(-_h, NumberWithUnits(30, "hour"));
    CHECK_EQ(-_h, NumberWithUnits(-30*60, "min"));
    CHECK_EQ(-_h, NumberWithUnits(-30*60*60, "sec"));
}

TEST_CASE("binary operators"){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{2, "km"};
    NumberWithUnits b{300, "m"};

    NumberWithUnits _h{30, "hour"};
    NumberWithUnits _min{30, "min"};

    CHECK_EQ(a+b, NumberWithUnits(2.3,"km"));
    CHECK_EQ(b+a, NumberWithUnits(2300,"m"));

    CHECK_EQ(a+=b, NumberWithUnits(2.3,"km"));
    CHECK_EQ(b+=a, NumberWithUnits(2300,"m"));

    CHECK_EQ(a-b, NumberWithUnits(1.7,"km"));
    CHECK_EQ(b-a, NumberWithUnits(-1700,"m"));
    CHECK_EQ(a-=b, NumberWithUnits(1.7,"km"));
    CHECK_EQ(b-=a, NumberWithUnits(-1700,"m"));

    CHECK_THROWS(a + _h);
    CHECK_THROWS(a - _h);
    CHECK_THROWS(a +=_h);
    CHECK_THROWS(a -=_h);

}
TEST_CASE("prefix increment and discrement"){

    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{2, "km"};

    CHECK_EQ(++a, NumberWithUnits(3,"km"));
    CHECK_EQ(++++++++a, NumberWithUnits(7,"km"));

    CHECK_EQ(--------a, NumberWithUnits(3,"km"));
    CHECK_EQ(--a, NumberWithUnits(2,"km"));    

}
TEST_CASE("sufix increment and discrement"){

    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{2, "km"};

    CHECK_EQ(a++, NumberWithUnits(2,"km"));
    CHECK_EQ(a, NumberWithUnits(3,"km"));

    CHECK_EQ(a--, NumberWithUnits(3,"km"));
    CHECK_EQ(a, NumberWithUnits(2,"km"));    

}
TEST_CASE("bool binary operators"){

    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{2, "km"};
    NumberWithUnits b{300, "m"};

    CHECK_FALSE(a<=b);
    CHECK(a>=b);
    CHECK(a>=a);

    CHECK_LE(b,a);
    CHECK_LT(b,a);

    CHECK_GE(a,b);
    CHECK_GT(a,b);

    CHECK(a!=b);
    CHECK_NE(b,a);
}

TEST_CASE("Multiplication operators"){
    
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{2, "km"};

    CHECK(a*3==NumberWithUnits(6,"km"));
    CHECK(3*a==NumberWithUnits(6,"km"));

    CHECK((a*=3)==NumberWithUnits(6,"km"));
    CHECK((a*=0.5)==NumberWithUnits(3,"km"));
}
