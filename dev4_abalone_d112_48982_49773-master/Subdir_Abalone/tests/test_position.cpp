#include"catch.hpp"
#include"position.h"
#include<stdexcept>



TEST_CASE("Testing samePositions"){


    Position p1(0,0,0);
    Position p2(0,0,0);
    REQUIRE(p1== p2);
}

TEST_CASE("Testing axialCoordinates"){


    Position p(0,0,0);
    Position p1(-1,-3,4);
    REQUIRE( p.axialCoordinates().first==0);
    REQUIRE( p.axialCoordinates().second==0);
    REQUIRE( p1.axialCoordinates().first==-1);
    REQUIRE( p1.axialCoordinates().second==-3);
}


TEST_CASE("Testing getPositionTo EastWards"){

    Position p1(0,0,0);
    Position p(1,0,-1);
    p1.getPositionTo(esi::Direction::EAST);
    REQUIRE(p==p1.getPositionTo(esi::Direction::EAST));
}



TEST_CASE("Testing comparingdifferentPositions"){

    Position p1(0,0,0);
    Position p(1,0,-1);

    REQUIRE(p!=p1);
}




