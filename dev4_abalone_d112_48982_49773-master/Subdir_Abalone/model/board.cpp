#include "board.h"
#include <algorithm>

Board::Board() {

    createHexagons();
}

void Board::createHexagons() {
    std::vector<Hexagon> hexagons;
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
                 hexagons.push_back(Hexagon(p,std::optional<Marble>(Color::WHITE)));
               }
                else if (p.y() ==2 &&( p.z() == 0 ||  p.z() == -1 ||  p.z() == -2)) {
                 hexagons.push_back(Hexagon(p,std::optional<Marble>(Color::WHITE)));

               } else if (p.y() ==2 &&( p.z() == 0 ||  p.z() == -1 ||  p.z() == -2)) {
                  Hexagon h(p);
                  hexagons.push_back(h);
                }
                else if (p.y() == -2 &&( p.z() == 2 || p.z() == 1 || p.z() == 0)) {
                Hexagon h(p,std::optional<Marble>(Color::BLACK));
                hexagons.push_back(h);
            }else if (p.y() ==-2 &&( p.z() != 0 ||  p.z() != -1 ||  p.z() != -2)) {
                Hexagon h (p);
                hexagons.push_back(h);
            }
             else if (p.y() == -4 || p.y() == -3) {
                 Hexagon h(p,std::optional<Marble>(Color::BLACK));
                 hexagons.push_back(h);
            }else{
               Hexagon h(p);
               hexagons.push_back(h);

             }

        }

    }

    m_hexagons=std::make_shared<vector<Hexagon>*>(new std::vector<Hexagon>(hexagons.begin(),hexagons.end()));

}


unsigned Board::countMarblesLeft(Color color) {
unsigned cpt = 0;
        for(auto e : *(*m_hexagons.get())) {
        if(e.hasMarble() && e.marble().value().color() == color) {
            ++cpt;
        }
    }
    return cpt;
 }

bool Board::isFree(const Hexagon & hexagon) {
    return !hexagon.hasMarble();
}





bool Board::isInside(const Position position) {
    return (( position.x() >= - 4 && position.x() <= 4)
                                  &&
            (position.y() >= - 4 && position.y() <=  4)
                                 &&
            (position.z() >= - 4 && position.z() <= 4));
}

bool Board::isBorder(const Position position, esi::Direction direction)
{
    Hexagon *any=getHexagonAt(position);
    return  !neighbour(*any,direction).has_value();
}

 Hexagon* Board::getHexagonAt(Position position)
{
    Hexagon* result=nullptr;
     if(!isInside(position)){

        return nullptr;
    }else{
    std::vector<Hexagon>* myHexagons=*m_hexagons.get();
    for (auto hex=myHexagons->begin();hex!=myHexagons->end();hex++) {
      if (hex->coordinates()==position) {
               result=&(*hex);
               break;
           }

       }
        return result;
    }
}

 Position Board::backTo3Dcoordinates(Square square) {

     int z= (square.getX() + square.getY())*(-1);
     return Position(square.getX(),square.getY(),z);

 }

    Square Board::translateInto2D(Alphabet lettre, int val)
 {
     switch (lettre) {
     case A:
         return Square(val-1,lettre);
     case B:
         return Square(val-2,lettre);
     case C:
         return Square(val-3,lettre);
     case D:
         return Square(val-4,lettre);

     case E:
         return Square(val-5,lettre);
     case F:
         return Square(val-6,lettre);
     case G:
         return Square(val-7,lettre);
     case H:
         return Square(val-8,lettre);
     case I:
         return Square(val-9,lettre);
     }
 }


std::optional<Hexagon> Board::neighbour( Hexagon & hexagon, esi::Direction direction) {

    int valX = 0;
    int valY = 0;
    int valZ = 0;

    switch (direction) {
    case esi::Direction::EAST:

        valX = hexagon.coordinates().x() + 1;
        valY = hexagon.coordinates().y();
        valZ = hexagon.coordinates().z() - 1;

        break;
    case esi::Direction::WEST:

        valX = hexagon.coordinates().x() - 1;
        valY = hexagon.coordinates().y();
        valZ = hexagon.coordinates().z() + 1;

        break;
    case esi::Direction::NORTHEAST:

        valX = hexagon.coordinates().x();
        valY = hexagon.coordinates().y() + 1;
        valZ = hexagon.coordinates().z() - 1 ;

        break;
    case esi::Direction::NORTHWEST:

        valX = hexagon.coordinates().x() - 1;
        valY = hexagon.coordinates().y() + 1;
        valZ = hexagon.coordinates().z();

        break;
    case esi::Direction::SOUTHEAST:

        valX = hexagon.coordinates().x() + 1;
        valY = hexagon.coordinates().y() - 1;
        valZ = hexagon.coordinates().z();

        break;
    case esi::Direction::SOUTHWEST:
        valX = hexagon.coordinates().x();
        valY = hexagon.coordinates().y() - 1;
        valZ = hexagon.coordinates().z() + 1;

        break;
    }
    Position destination(valX,valY,valZ);
    auto temp=*m_hexagons.get();

    if (isInside(destination)) {
        Hexagon * neighbour=getHexagonAt(destination);
        auto iter=find(temp->begin(),temp->end(),*neighbour);
        return std::optional<Hexagon>(*iter);

    } else {

        return std::nullopt;
    }
}

Board::~Board() {
}






