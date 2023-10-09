#include"catch.hpp"
#include<algorithm>
#include"board.h"
#include"color.h"



TEST_CASE("TestSet18","isBorderHexagonsonTop"){

    Board board;
    Position p1(-4,4,0);
    Position p2(-3,4,-1);
    Position p3(-2,4,-2);
    Position p4(-1,4,-3);
    Position p5(0,4,-4);
    REQUIRE(board.isBorder(p1,esi::Direction::NORTHWEST));
    REQUIRE(board.isBorder(p2,esi::Direction::NORTHWEST));
    REQUIRE(board.isBorder(p3,esi::Direction::NORTHWEST));
    REQUIRE(board.isBorder(p4,esi::Direction::NORTHWEST));
    REQUIRE(board.isBorder(p5,esi::Direction::NORTHWEST));
}

TEST_CASE("TestSet19","isBorderHexagonsRightBorder"){

    Board board;
    Position p1(-4,4,0);
    Position p5(0,4,-4);
    REQUIRE(board.isBorder(p1,esi::Direction::WEST));
    REQUIRE(board.isBorder(p5,esi::Direction::EAST));
}



TEST_CASE("TestSet20","removingOneMarbleWhite"){
   Board board;
   Position pos(-4,4,0);
   REQUIRE(board.countMarblesLeft(Color::WHITE)== 14);
   board.getHexagonAt(pos)->marble().reset();
   REQUIRE(board.countMarblesLeft(Color::WHITE)== 13);
 }

   TEST_CASE("TestSet21","removingOneMarbleBlack"){
   Board board;
   Position pos(4,-4,0);
   REQUIRE(board.countMarblesLeft(Color::BLACK)== 14);
   board.getHexagonAt(pos)->marble().reset();
   REQUIRE(board.countMarblesLeft(Color::BLACK)==13);
}


TEST_CASE("TestSet112","removingSeveralMarbles"){
   Board board;
   Position pos(-2,2,0);
   Position pos1(-1,2,-1);
   Position pos2(0,2,-2);
   REQUIRE(board.countMarblesLeft(Color::WHITE)== 14);
   board.getHexagonAt(pos)->marble().reset();
   board.getHexagonAt(pos1)->marble().reset();
   board.getHexagonAt(pos2)->marble().reset();
   REQUIRE(board.countMarblesLeft(Color::WHITE)== 11);
}


TEST_CASE("TestSet24","hexagonsCount") {


    Board board;
    unsigned long long size=(*board.hexagons().get())->size();
    unsigned long long hexagons=61;
    REQUIRE(size== hexagons);


}

TEST_CASE("TestSet33","hexagonsWithMarbles") {

 Board board;

 long long hexWithMarbles= std::count_if((*board.hexagons().get())->begin(),(*board.hexagons().get())->end(),
                                            [](Hexagon hex){ return hex.hasMarble();});
 REQUIRE(hexWithMarbles==28);

}


TEST_CASE("TestSet34","hexagonsWithWhiteMarbles") {

    Board board;
    long long whiteMarbles=14;
    long long hexWithWhiteMarbles= std::count_if((*board.hexagons().get())->begin(),(*board.hexagons().get())->end(),
                                                 [](Hexagon hex){  return hex.marble()&&hex.marble().value().color()==Color::WHITE;});
    REQUIRE(hexWithWhiteMarbles==whiteMarbles);

}


TEST_CASE("TestSet66","hexagonsWithblackMarbles") {

    Board board;
    long long blackMarbles=14;
    long long hexWithBlackMarbles= std::count_if((*board.hexagons().get())->begin(),(*board.hexagons().get())->end(),
                                                 [](Hexagon hex){return hex.marble()&&hex.marble().value().color()==Color::BLACK;});
    REQUIRE(hexWithBlackMarbles==blackMarbles);
}


TEST_CASE("TestSet45","isinside_valid_values") {

    Board board;
    int stopz=0;
    int stopy=4;
    int stopx=-4;
    int x,y,z;
    bool inside;
    for(;(stopx<=0 && stopy>=-4 );stopz++,stopy--){

        if(stopz>=4){stopz=4;}
        if(stopy==-1||stopy==-2||stopy==-3||stopy==-4){++stopx;}

        for( x=stopx,z=stopz,y=stopy; x<=stopz; x++,z--){

            Position p(x,y,z);
            inside=board.isInside(p);
            REQUIRE(inside==true);
        }


    }

}


TEST_CASE("TestSet88","isinside_outside_values"){


        Board board;
        std::vector<Position> positions;
        positions.push_back(Position(-5,2,0));
        positions.push_back(Position(-4,-5,-1));
        positions.push_back(Position(0,2,-5));

        positions.push_back(Position(5,-2,2));
        positions.push_back(Position(1,5,1));
        positions.push_back(Position(2,-2,5));


   for(const auto &p:positions){

    REQUIRE(board.isInside(p)==false);

}

}

TEST_CASE("TestSet87","marblesAtBeginningofGameBlacks"){

    Board board;

    unsigned blacks=14;

    REQUIRE(blacks==board.countMarblesLeft(Color::BLACK));
}


 TEST_CASE("TestSet99","marblesAtBeginningofGameWhites"){

    Board board;

    unsigned whites=14;

    REQUIRE(whites==board.countMarblesLeft(Color::WHITE));
}

TEST_CASE("TestSet4","hexagonIsFreeorNotbasedOnPositionAtStart"){
    Board board;
    int stopz=0;
    int stopy=4;
    int stopx=-4;
    int x,y,z;

    for(;(stopx<=0 && stopy>=-4 );stopz++,stopy--){

        if(stopz>=4){stopz=4;}
        if(stopy==-1||stopy==-2||stopy==-3||stopy==-4){++stopx;}

        for( x=stopx,z=stopz,y=stopy; x<=stopz; x++,z--){

            Position p(x,y,z);

            if(p.y() == 4 || p.y() == 3) {
                Marble m(Color::WHITE);
                Hexagon h(p,m);
                REQUIRE(board.isFree(h)==false);

            }
                else if (p.y() ==2 &&( p.z() == 0 ||  p.z() == -1 ||  p.z() == -2)) {
                Marble m(Color::WHITE);
                Hexagon h(p,m);
                REQUIRE(board.isFree(h)==false);
               } else if (p.y() ==2 &&( p.z() == 0 ||  p.z() == -1 ||  p.z() == -2)) {

                Hexagon h(p);
                REQUIRE(board.isFree(h)==true);
                }

                else if (p.y() == -2 &&( p.z() == 2 || p.z() == 1 || p.z() == 0)) {
                Marble m(Color::BLACK);
                Hexagon h(p,m);
                REQUIRE(board.isFree(h)==false);
            }else if (p.y() ==-2 &&( p.z() != 0 ||  p.z() != -1 ||  p.z() != -2)) {
                Hexagon h(p);
                REQUIRE(board.isFree(h)==true);
            }

            else if (p.y() == -4 || p.y() == -3) {
                Marble m(Color::BLACK);
                Hexagon h(p,m);
                REQUIRE(board.isFree(h)==false);
            }else{
                Hexagon h(p);
                REQUIRE(board.isFree(h)==true);

             }

        }

    }
}

TEST_CASE("TestSet5","CheckgetHexagonat"){
    Board board;
    Position p(0,0,0);
    Position p1(0,2,-2);
    Position p2(1,2,-3);
Hexagon * hex=board.getHexagonAt(p);

Hexagon *hex1=board.getHexagonAt(p1);

Hexagon *hex2=board.getHexagonAt(p2);

 REQUIRE(hex->hasMarble()==false);
 REQUIRE(hex1->hasMarble()==true);
 REQUIRE(hex2->hasMarble()==false);
}





TEST_CASE("TestSet77","TestingneighbourWEST"){
   Board board;
   Position  position(1,2,-3);
   Position positionwest(0,2,-2);
   std::optional<Hexagon>destination=board.neighbour(*(board.getHexagonAt(position)),esi::Direction::WEST);
   REQUIRE(destination.value()==*(board.getHexagonAt(positionwest)));
}


TEST_CASE("TestSet71","TestingneighbourEAST"){

    Board board;
    Position position(0,0,0);
    Position positioneast(1,0,-1);

    std::optional<Hexagon>destination=board.neighbour(*board.getHexagonAt(position),esi::Direction::EAST);

    REQUIRE(destination.value()==*board.getHexagonAt(positioneast));
}

TEST_CASE("TestSet72","TestingneighbourNORTHWEST"){

    Board board;
    Position position(0,0,0);
    Position positionNoWest(-1,1,0);
    Hexagon hexagon1(position);
    Hexagon hexagonnWest(positionNoWest);
    board.neighbour(hexagon1,esi::Direction::NORTHWEST);//optional
    REQUIRE(board.neighbour(hexagon1,esi::Direction::NORTHWEST).value()==hexagonnWest);
}



TEST_CASE("TestSet73","TestingneighbourSOUTHWEST"){

    Board board;
    Position position(0,0,0);
    Position positionSW(0,-1,1);
    Hexagon hexagon1(position);
    Hexagon hexagonSWest(positionSW);
    REQUIRE(board.neighbour(hexagon1,esi::Direction::SOUTHWEST).value()==hexagonSWest);
}


TEST_CASE("TestSet79","TestingneighbourNORTHEAST"){

    Board board;
    Position position(0,0,0);
    Position positioneast(0,1,-1);
    Hexagon hexagon1(position);
    Hexagon hexagoneast(positioneast);
    REQUIRE(board.neighbour(hexagon1,esi::Direction::NORTHEAST).value()==hexagoneast);
}


TEST_CASE("TestSet799","TestingneighbourSOUTHEAST"){

    Board board;
    Position position(0,0,0);
    Position positioneast(1,-1,0);
    Hexagon hexagon1(position);
    Hexagon hexagoseast(positioneast);
    REQUIRE(board.neighbour(hexagon1,esi::Direction::SOUTHEAST).value()==hexagoseast);
}




TEST_CASE("TestSet1000","SwappingMarbles"){

    Board board;
    Position p1(-1,2,-1);
    Position p2(-1,1,0);
    board.getHexagonAt(p1)->marble().swap(board.getHexagonAt(p2)->marble());

    REQUIRE( board.getHexagonAt(p1)->hasMarble()==false);
    REQUIRE( board.getHexagonAt(p2)->hasMarble()==true);
}













